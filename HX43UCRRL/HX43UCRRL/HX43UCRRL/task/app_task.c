#include "app_task.h"
#include "pushrod_task.h"
#include "msge_task.h"
#include "heat_cool_task.h"
#include "hal_init.h"
#include "sys_config.h"

#include "OSAL.h"
#include "osal_timer.h"

#include <string.h>
#include <stdlib.h>

static unsigned char App_TaskID;
static XDATA App_Obj_t App_Obj;

#define SET_KEY_LED(X)						(App_Obj.led_sta |= ((INT16U)X))
#define CLR_KEY_LED(X)						(App_Obj.led_sta &= ~((INT16U)X))

static int App_SentMsg(unsigned int cont){ 
	static unsigned char send_buf[BUF_SIZE];
	memset((void*)send_buf,0,BUF_SIZE);
	send_buf[0] = START_FIELD;
	send_buf[1] = MSG_ID;
	send_buf[2] = Get_High(cont); 
	send_buf[3] = Get_Low(cont); 
	send_buf[4] = (INT8U)(START_FIELD + MSG_ID + cont/256 + cont%256);
	send_buf[5] = Get_High(STOP_MESSAGE);
	send_buf[6]  = Get_Low(STOP_MESSAGE);
	Hal_UartSendBuf(UART0_ID, send_buf, BUF_SIZE);
	return 0; 
}

static void App_UartRxHandle(void)
{
	App_Obj.rev_buf.buf[App_Obj.rev_buf.len ++] = SBUF;

	if(App_Obj.rev_buf.buf[0] != START_FIELD){
		memset((void*)&App_Obj.rev_buf,0,sizeof(Rev_Buf_t));
		App_Obj.get_key = 0;
		return ;
	}
	
	if(App_Obj.rev_buf.len >= BUF_SIZE){
		if(App_Obj.rev_buf.buf[1] != MSG_ID){
			memset((void*)&App_Obj.rev_buf,0,sizeof(Rev_Buf_t));
			App_Obj.get_key = 0;
			return ;
		}

		if(App_Obj.rev_buf.buf[BUF_SIZE - 2] != 0x0d || App_Obj.rev_buf.buf[BUF_SIZE - 1] != 0x0a){
			memset((void*)&App_Obj.rev_buf,0,sizeof(Rev_Buf_t));
			App_Obj.get_key = 0;
			return ;
		}
		
		if(App_Obj.rev_buf.buf[4] != (App_Obj.rev_buf.buf[0] + App_Obj.rev_buf.buf[1] + App_Obj.rev_buf.buf[2] + App_Obj.rev_buf.buf[3])){
			memset((void*)&App_Obj.rev_buf,0,sizeof(Rev_Buf_t));
			App_Obj.get_key = 0;
			return ;
		}
		
		App_Obj.get_key = (INT16U)App_Obj.rev_buf.buf[2] << 8 |App_Obj.rev_buf.buf[3];	
		osal_set_event(App_TaskID, EVENT_REV_MSG);
		memset((void*)&App_Obj.rev_buf,0,sizeof(Rev_Buf_t));
	}
}

static void TimeHandle(void)
{
	OSAL_TimerUpdata();
	Hal_MsgeTimeHdl(MSGE_SUM);
}

/**
	@brief:Key function area
*/
static void Light_Handle(void)
{
	#ifdef LED_FUNC_ENABLE
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.foot_led_sta){
			App_Obj.foot_led_sta = False;
			LED1_PIN = OFF;
			F_LED_PIN = OFF;
			CLR_KEY_LED(LIGHT_LED_MAP);
			CLR_KEY_LED(BACK_LIGHT);
		}else{
			App_Obj.foot_led_sta = True;
			LED1_PIN = ON;
			F_LED_PIN = ON;
			SET_KEY_LED(BACK_LIGHT);
			SET_KEY_LED(LIGHT_LED_MAP);
		}
	}
	#endif
}

static void Warn_Handle(void)
{
	#ifdef WARN_FUNC_ENABLE	
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.warn_sta){
			App_Obj.warn_sta = False;
			WARN1_PIN = OFF;			
			OSAL_StopTimer(App_TaskID, EVENT_WARN_AUTO_CLS_MSG);
			CLR_KEY_LED(WARN_LED_MAP);
		}else{
			App_Obj.warn_sta = True;
			WARN1_PIN = ON;
			SET_KEY_LED(WARN_LED_MAP);			
			OSAL_StartTimer(App_TaskID, EVENT_WARN_AUTO_CLS_MSG,WARN_AUTO_CLOSE);
		}
	}
	#endif
}

static void Msge_Handle(void)
{
	#ifdef MSGE_FUNC_ENABLE	
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.moto_sta){
			App_Obj.moto_sta = FALSE;
			osal_clear_event(Msge_TaskGetID(), EVENT_MSGE_A_OPEN);
			osal_set_event(Msge_TaskGetID(), EVENT_MSGE_A_CLOSE);			
			OSAL_StopTimer(App_TaskID, EVENT_MSGE_AUTO_CLS_MSG);
			CLR_KEY_LED(MSGE_LED_MAP);
		}else{
			App_Obj.moto_sta = TRUE;
			osal_clear_event(Msge_TaskGetID(), EVENT_MSGE_A_CLOSE);
			osal_set_event(Msge_TaskGetID(), EVENT_MSGE_A_OPEN);			
			OSAL_StartTimer(App_TaskID, EVENT_MSGE_AUTO_CLS_MSG, MASS_AUTO_CLOSE);
			SET_KEY_LED(MSGE_LED_MAP);
		}
	}
	#endif
}

static void Cool_Handle(void)
{
	#ifdef COOL_FUNC_ENABLE
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			App_Obj.cool_flag = FALSE;
			osal_clear_event(HeatCool_TaskGetID(),EVENT_COOL_A_OPEN);
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_CLOSE);			
			OSAL_StopTimer(App_TaskID, EVENT_COOL_AUTO_CLS_MSG);
			CLR_KEY_LED(COOL_LED_MAP);
		}else{
			App_Obj.cool_flag = TRUE;
			osal_clear_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_CLOSE);
			osal_set_event(HeatCool_TaskGetID(),EVENT_COOL_A_OPEN);	
			OSAL_StartTimer(App_TaskID, EVENT_COOL_AUTO_CLS_MSG,COOL_AUTO_CLOSE);
			SET_KEY_LED(COOL_LED_MAP);
		}
	}
	#endif
}

static void Heat_Handle(void)
{
	#ifdef HEAT_FUNC_ENABLE

	#endif
}

static void Pushrod_HeadCloseHandle(void)
{
	#ifdef PUSHROD_HEAD_FUNC_ENABLE
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_SUPEND);
		}
		osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_A_CLOSE);
	}
	#endif
}

static void Pushrod_HeadOpenHandle(void)
{
	#ifdef PUSHROD_HEAD_FUNC_ENABLE
	if(!App_Obj.lock_flag){			
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_SUPEND);
		}		
		osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_A_OPEN);
	}
	#endif
}

static void Pushrod_LumbarCloseHandle(void)
{	
	#ifdef PUSHROD_LUMBAR_FUNC_ENABLE
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_SUPEND);
		}
		osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_B_CLOSE);		
	}
	#endif
}

static void Pushrod_LumbarOpenHandle(void)
{	
	#ifdef PUSHROD_LUMBAR_FUNC_ENABLE
	if(!App_Obj.lock_flag){		
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_SUPEND);
		}
		osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_B_OPEN);	
	}
	#endif
}

static void Pushrod_ResetHandle(void)
{
	#ifdef PUSHROD_RESET_FUNC_ENABLE
	if(!App_Obj.lock_flag){				
		OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
		if(App_Obj.cool_flag){
			osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_SUPEND);
		}
		OSAL_StopTimer(App_TaskID,EVENT_RESET_MSG);
		OSAL_StartTimer(App_TaskID,EVENT_RESET_MSG,LONG_PRESS_VALUE);
		App_Obj.reset_det_flag = TRUE;
	}
	#endif
}

static void LockKey_Handle(void)
{
	OSAL_StopTimer(App_TaskID,EVENT_KEY_LOCK_MSG);
	OSAL_StartTimer(App_TaskID,EVENT_KEY_LOCK_MSG,LONG_PRESS_VALUE);
	App_Obj.lock_det_flag = TRUE;
}

static void Key_Handle(void){
	switch(App_Obj.get_key){
		case KEY0_VALUE:{
			if(App_Obj.cur_key != KEY0_VALUE){
				App_Obj.cur_key = KEY0_VALUE;
				/*key handle*/
			}
			break;
		}
		case KEY1_VALUE:{
			if(App_Obj.cur_key != KEY1_VALUE){
				App_Obj.cur_key = KEY1_VALUE;
				/*key handle*/
				Pushrod_LumbarCloseHandle();	
			}
			break;
		} 
		case KEY2_VALUE:{
			if(App_Obj.cur_key != KEY2_VALUE){
				App_Obj.cur_key = KEY2_VALUE;
				/*key handle*/
				Pushrod_LumbarOpenHandle();	
			}
			break;
		}
		case KEY3_VALUE:{
			if(App_Obj.cur_key != KEY3_VALUE){
				App_Obj.cur_key = KEY3_VALUE;
				/*key handle*/
				Pushrod_HeadCloseHandle();		
			}
			break;
		}
		case KEY4_VALUE:{
			if(App_Obj.cur_key != KEY4_VALUE){
				App_Obj.cur_key = KEY4_VALUE;
				/*key handle*/
				Pushrod_HeadOpenHandle();		
			}
			break;
		}
		case KEY5_VALUE:{
			if(App_Obj.cur_key != KEY5_VALUE){
				App_Obj.cur_key = KEY5_VALUE;
				/*key handle*/
				Pushrod_ResetHandle();
			}
			break;
		}
		case KEY6_VALUE:{
			if(App_Obj.cur_key != KEY6_VALUE){
				App_Obj.cur_key = KEY6_VALUE;
				/*key handle*/
				LockKey_Handle();
			}
			break;
		}
		case KEY7_VALUE:{
			if(App_Obj.cur_key != KEY7_VALUE){
				App_Obj.cur_key = KEY7_VALUE;
				/*key handle*/
				
			}
			break;
		}
		default:{
			if(App_Obj.cur_key){
				unsigned char sup_flag = 0;
				App_Obj.cur_key = 0;
				#ifdef PUSHROD_FUNC_ENABLE
				osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_STOP);
				#endif
				if(App_Obj.lock_det_flag){
					App_Obj.lock_det_flag = FALSE;
					OSAL_StopTimer(App_TaskID,EVENT_KEY_LOCK_MSG);	
					#ifdef LED_FUNC_ENABLE
					Light_Handle();
					#endif
				}
				if(App_Obj.reset_det_flag){
					App_Obj.reset_det_flag = FALSE;
					OSAL_StopTimer(App_TaskID,EVENT_RESET_MSG);
					#ifdef COOL_FUNC_ENABLE
					Cool_Handle();
					#endif
				}
				Hal_HeatCoolControl(0, HC_CMD_GET_SUPED_STA, (void*)&sup_flag);
				if(sup_flag){
					osal_set_event(HeatCool_TaskGetID(),EVENT_HEAT_COOL_A_RESUME);
				}
			}
			break;
		}
	}
}

unsigned char App_TaskInit(unsigned char task_id)
{
	App_TaskID = task_id;
	#ifdef LED_FUNC_ENABLE
		/*<½ÅµÆ>*/
		SET_OUTPUT(P0,0);
		SET_OUTPUT(P0,1);
		/*<¸½±­½ÅµÆ>*/
		SET_OUTPUT(P2,5);
	#endif

	#ifdef WARN_FUNC_ENABLE
		SET_OUTPUT(P0,4);
		SET_OUTPUT(P0,5);
	#endif
	Hal_RegUartRxHdl(UART0_ID,App_UartRxHandle);
	memset(&App_Obj,0,sizeof(App_Obj_t));
	SET_KEY_LED(HEAD_OPEN_LED_MAP);
	SET_KEY_LED(HEAD_CLOSE_LED_MAP);
	SET_KEY_LED(LUMBAR_OPEN_LED_MAP);
	SET_KEY_LED(LUMBAR_CLOSE_LED_MAP);
	Hal_RegTimeHdl(TimeHandle);
	
	OSAL_StartTimer(App_TaskID, EVENT_SYS_AUTO_CLS_MSG, SYSTEM_AUTO_CLOSE);
	return SUCCEED;
}

unsigned int App_TaskProcessEvent(unsigned char task_id,unsigned int events)
{	
	(void)task_id;
	if(events & EVENT_REV_MSG){	
		Key_Handle();		
		App_SentMsg(App_Obj.led_sta);
		return (events ^ EVENT_REV_MSG);
	}
	
	if(events & EVENT_KEY_LOCK_MSG){
		App_Obj.lock_det_flag= False;		
		if(App_Obj.lock_flag){			
			App_Obj.lock_flag = FALSE;
			if(App_Obj.sys_auto_cls_flag){
				App_Obj.sys_auto_cls_flag = False;
				OSAL_StartTimer(App_TaskID, EVENT_SYS_AUTO_CLS_MSG,SYSTEM_AUTO_CLOSE);
			}
			CLR_KEY_LED(LOCK_LED_MAP);
			#if PUSHROD_SUM == 1
				SET_KEY_LED(HEAD_OPEN_LED_MAP);
				SET_KEY_LED(HEAD_CLOSE_LED_MAP);
			#endif
			#if PUSHROD_SUM == 2
				SET_KEY_LED(HEAD_OPEN_LED_MAP);
				SET_KEY_LED(HEAD_CLOSE_LED_MAP);
				SET_KEY_LED(LUMBAR_OPEN_LED_MAP);
				SET_KEY_LED(LUMBAR_CLOSE_LED_MAP);
			#endif
			#ifdef WARN_FUNC_ENABLE
				if(App_Obj.warn_sta){
					SET_KEY_LED(WARN_LED_MAP);
				}
			#endif
			#ifdef MSGE_FUNC_ENABLE
				if(App_Obj.moto_sta){
					SET_KEY_LED(MSGE_LED_MAP);
				}
			#endif
			#ifdef LED_FUNC_ENABLE
				if(App_Obj.foot_led_sta){
					SET_KEY_LED(LIGHT_LED_MAP);
				}
			#endif
			#ifdef COOL_FUNC_ENABLE
				if(App_Obj.cool_flag){
					SET_KEY_LED(COOL_LED_MAP);
				}
			#endif
			#ifdef HEAT_FUNC_ENABLE
				if(App_Obj.heat_flag){
					SET_KEY_LED(HEAT_LED_MAP);
				}
			#endif
		}else{
			App_Obj.lock_flag = True;
			OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
			CLR_KEY_LED(~LOCK_LED_MAP);		
			if(App_Obj.foot_led_sta){
				SET_KEY_LED(BACK_LIGHT);
			}
			SET_KEY_LED(LOCK_LED_MAP);
		}
		return (events ^ EVENT_KEY_LOCK_MSG);
	}

	if(events & EVENT_RESET_MSG){
		App_Obj.reset_det_flag = FALSE;
		osal_set_event(Pushrod_TaskGetID(), EVNET_PUSHROD_B_CLOSE);
		OSAL_StopTimer(Pushrod_TaskGetID(), EVNET_PUSHROD_A_CLOSE);
		OSAL_StartTimer(Pushrod_TaskGetID(), EVNET_PUSHROD_A_CLOSE, 100);
		return (events ^ EVENT_RESET_MSG);
	}

	if(events & EVENT_WARN_AUTO_CLS_MSG){
		WARN1_PIN = 0;
		App_Obj.warn_sta = False;
		CLR_KEY_LED(WARN_LED_MAP);
		return (events ^ EVENT_WARN_AUTO_CLS_MSG);
	}

	if(events & EVENT_MSGE_AUTO_CLS_MSG){
		App_Obj.moto_sta = False;
		CLR_KEY_LED(MSGE_LED_MAP);
		osal_set_event(Msge_TaskGetID(), EVENT_MSGE_A_CLOSE);
		return (events ^ EVENT_MSGE_AUTO_CLS_MSG);
	}
	
	if(events & EVENT_HEAT_AUTO_CLS_MSG){
 		
		return (events ^ EVENT_HEAT_AUTO_CLS_MSG);
	}

	if(events & EVENT_COOL_AUTO_CLS_MSG){
		App_Obj.cool_flag = FALSE;
		CLR_KEY_LED(COOL_LED_MAP);
		osal_set_event(HeatCool_TaskGetID(), EVENT_HEAT_COOL_A_CLOSE);
		return (events ^ EVENT_COOL_AUTO_CLS_MSG);
	}

	if(events & EVENT_SYS_AUTO_CLS_MSG){
		App_Obj.sys_auto_cls_flag = True;
		App_Obj.lock_flag = True;
		App_Obj.led_sta = 0;
		#ifdef LED_FUNC_ENABLE
			LED1_PIN = F_LED_PIN = OFF;
			CLR_KEY_LED(BACK_LIGHT);
			App_Obj.foot_led_sta = False;
		#endif		
		
		#ifdef WARN_FUNC_ENABLE
			WARN1_PIN = OFF;
			App_Obj.warn_sta = False;			
			CLR_KEY_LED(WARN_LED_MAP);
		#endif
			
		#ifdef COOL_FUNC_ENABLE
			App_Obj.cool_flag = FALSE;
			CLR_KEY_LED(COOL_LED_MAP);
			osal_set_event(HeatCool_TaskGetID(), EVENT_HEAT_COOL_A_CLOSE);
		#endif
		
		#if (PUSHROD_SUM > 0)
			osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_STOP);
		#endif
		
		#ifdef MSGE_FUNC_ENABLE
			App_Obj.moto_sta = False;
			CLR_KEY_LED(MSGE_LED_MAP);
			osal_set_event(Msge_TaskGetID(), EVENT_MSGE_A_CLOSE);
		#endif
		
		SET_KEY_LED(LOCK_LED_MAP);
		CLR_KEY_LED(~LOCK_LED_MAP);
		return (events ^ EVENT_SYS_AUTO_CLS_MSG);
	}
	
	if(events & EVENT_FAULT_ERROR_MSG){
		while(1);	/*WDT reset*/
	}
	return 0;
}

