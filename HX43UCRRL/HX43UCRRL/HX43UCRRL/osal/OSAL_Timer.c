#include "osal_timer.h"
#include "OSAL.H"
#include "comdef.h"
#include <string.h>

typedef struct{
	uint8 use_flag:1;
	uint8 reload_flag:1;
	uint8 task_id:4;	
	uint16 event_id;
	uint32 base_cnt,time_out;
}OSAL_Timer_t;

static XDATA OSAL_Timer_t OSAL_Timer[MAX_TIMER_NUM];

void OSAL_TimerInit(void)
{
	memset(OSAL_Timer,0,sizeof(OSAL_Timer));
}

uint8 OSAL_StartTimer(const uint8 task_id, const uint16 event_id,const uint32 timeout_value )
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(!(OSAL_Timer[i].use_flag)){
			OSAL_Timer[i].use_flag = TRUE;
			OSAL_Timer[i].base_cnt = 0;
			OSAL_Timer[i].event_id = event_id;
			OSAL_Timer[i].reload_flag = FALSE;
			OSAL_Timer[i].task_id = task_id;
			OSAL_Timer[i].time_out = timeout_value;
			return SUCCESS;
		}
	}
	return FAILURE;
}

uint8 OSAL_ReStartTime(const uint8 task_id, const uint16 event_id)
{	
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(OSAL_Timer[i].use_flag){
			if((OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
				OSAL_Timer[i].base_cnt = 0;				
				return SUCCESS;
			}
		}
	}	
	return FAILURE;
}

#ifdef OSAL_RELOAD_TIME_FUNC
uint8 OSAL_StartrReloadTimer(const uint8 task_id, const uint16 event_id, const uint32 timeout_value )
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(!(OSAL_Timer[i].use_flag)){
			OSAL_Timer[i].use_flag = TRUE;
			OSAL_Timer[i].base_cnt = 0;
			OSAL_Timer[i].event_id = event_id;
			OSAL_Timer[i].reload_flag = TRUE;
			OSAL_Timer[i].task_id = task_id;
			OSAL_Timer[i].time_out = timeout_value;
			return SUCCESS;
		}
	}
	return FAILURE;
}
#endif

uint8 OSAL_StopTimer(const uint8 task_id,const uint16 event_id)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if((OSAL_Timer[i].use_flag) && (OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
			OSAL_Timer[i].use_flag = FALSE;
			OSAL_Timer[i].base_cnt = 0;
			OSAL_Timer[i].event_id = 0;
			OSAL_Timer[i].reload_flag = FALSE;
			OSAL_Timer[i].task_id = 0;
			OSAL_Timer[i].time_out = 0;
			return SUCCESS;
		}
	}	
	return FAILURE;
}

#ifdef OSAL_GET_TIME_STA_FUNC
uint8 OSAL_GetTimerSta(const uint8 task_id,const uint16 event_id)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if((OSAL_Timer[i].use_flag) && (OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
			return TRUE;
		}
	}	
	return FALSE;
}
#endif

void OSAL_TimerUpdata(void)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(OSAL_Timer[i].use_flag){
			if(OSAL_Timer[i].base_cnt ++ > OSAL_Timer[i].time_out){
 				if(OSAL_Timer[i].reload_flag){
					OSAL_Timer[i].base_cnt = 0;
				}else{
					OSAL_Timer[i].use_flag = FALSE;
				}
 				osal_set_event(OSAL_Timer[i].task_id, OSAL_Timer[i].event_id);
 			}
		}
	}
}

