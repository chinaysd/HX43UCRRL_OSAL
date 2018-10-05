#include "heat_cool_task.h"
#include "OSAL.h"
#include "osal_timer.h"

static unsigned char HeatCool_TaskID;

/*private event id*/
#define EVENT_COOL_A_START						0X0001
#define EVENT_HEAT_A_START						0X0002
#define EVENT_STOP_A								0x0004

unsigned char HeatCool_TaskInit(unsigned char task_id)
{
	HeatCool_TaskID = task_id;
	return SUCCEED;
}

unsigned int HeatCool_TaskProcessEvent(unsigned char task_id,unsigned int events)
{
	(void)task_id;
#ifdef HEAT_FUNC_ENABLE
	if(events & EVENT_HEAT_A_START){
		unsigned char set = HC_OPEN;
		Hal_HeatCoolControl(0,HC_CMD_SET_HEAT,(void*)&set);
		/*制热要定时检测热敏电阻温度*/
		/*to do*/
		return (events ^ EVENT_HEAT_A_START);
	}
#endif
	if(events & EVENT_COOL_A_START){		
		unsigned char set = HC_OPEN;
		Hal_HeatCoolControl(0,HC_CMD_SET_COOL,(void*)&set);
		return (events ^ EVENT_COOL_A_START);
	}

	if(events & EVENT_STOP_A){
		unsigned char set = HC_CLOSE;
		Hal_HeatCoolControl(0,HC_CMD_SET_FAN,(void*)&set);
		return (events ^ EVENT_STOP_A);
	}
	
	if(events & EVENT_COOL_A_OPEN){
		unsigned char mode,set;
		Hal_HeatCoolControl(0,HC_CMD_GET_MODE,(void*)&mode);
		set = HC_OPEN;
		Hal_HeatCoolControl(0,HC_CMD_SET_FAN,(void*)&set);
		OSAL_StopTimer(HeatCool_TaskID, EVENT_STOP_A);
		if(mode != HC_COOL_MODE){
			set = HC_CLOSE;
			Hal_HeatCoolControl(0,HC_CMD_SET_COOL,(void*)&set);
			Hal_HeatCoolControl(0,HC_CMD_SET_HEAT,(void*)&set);
			OSAL_StopTimer(HeatCool_TaskID, EVENT_COOL_A_START);
			OSAL_StartTimer(HeatCool_TaskID, EVENT_COOL_A_START, HEAT_COOL_DELAY);
		}		
		mode = HC_COOL_MODE;
		Hal_HeatCoolControl(0,HC_CMD_SET_MODE,(void*)&mode);
		return (events ^ EVENT_COOL_A_OPEN);
	}
#ifdef HEAT_FUNC_ENABLE
	if(events & EVENT_HEAT_A_OPEN){
		unsigned char mode;
		Hal_HeatCoolGetMode(0,&mode);
		Hal_HeatCoolSetFan(0, HC_OPEN);
		if(mode == HC_STOP_MODE){
			Hal_HeatCoolSetHeat(0, HC_OPEN);			
			/*制热要定时检测热敏电阻温度*/			
			/*to do*/
		}else if(mode == HC_COOL_MODE){
			Hal_HeatCoolSetHeat(0, HC_CLOSE);
			Hal_HeatCoolSetCool(0, HC_CLOSE);
			OSAL_StartTimer(HeatCool_TaskID, EVENT_HEAT_A_START, HEAT_COOL_DELAY);
		}		
		Hal_HeatCoolSetMode(0, HC_HEAT_MODE);
		return (events ^ EVENT_HEAT_A_OPEN);
	}
#endif
	if(events & EVENT_HEAT_COOL_A_CLOSE){
		unsigned char set;
		set = HC_CLOSE;
		Hal_HeatCoolControl(0,HC_CMD_SET_COOL,(void*)&set);
		Hal_HeatCoolControl(0,HC_CMD_SET_HEAT,(void*)&set);
		set = HC_STOP_MODE;
		Hal_HeatCoolControl(0,HC_CMD_SET_HEAT,(void*)&set);
		OSAL_StopTimer(HeatCool_TaskID, EVENT_STOP_A);
		OSAL_StopTimer(HeatCool_TaskID, EVENT_COOL_A_START);
		OSAL_StartTimer(HeatCool_TaskID, EVENT_STOP_A, HEAT_COOL_DELAY);
		return (events ^ EVENT_HEAT_COOL_A_CLOSE);
	}

	if(events & EVENT_HEAT_COOL_A_SUPEND){
		Hal_HeatCoolControl(0,HC_CMD_SUPEND,0);
		return (events ^ EVENT_HEAT_COOL_A_SUPEND);
	}

	if(events & EVENT_HEAT_COOL_A_RESUME){
		Hal_HeatCoolControl(0,HC_CMD_RESUME,0);
		return (events & EVENT_HEAT_COOL_A_RESUME);
	}

	return 0;
}

unsigned char HeatCool_TaskGetID(void)
{
	return HeatCool_TaskID;
}


