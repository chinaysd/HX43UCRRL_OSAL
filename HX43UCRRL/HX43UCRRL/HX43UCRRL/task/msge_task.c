#include "msge_task.h"

static unsigned char Msge_TaskID;

unsigned char Msge_TaskInit(unsigned char task_id)
{
	Msge_TaskID = task_id;
	return SUCCEED;	
}

unsigned int Msge_TaskProcessEvent(unsigned char task_id,unsigned int events)
{
	(void)task_id;

	if(events & EVENT_MSGE_A_OPEN){
		Hal_MsgeControl(0, MSGE_CMD_OPEN, 0);
		return (events^EVENT_MSGE_A_OPEN);
	}

	if(events & EVENT_MSGE_A_CLOSE){
		Hal_MsgeControl(0, MSGE_CMD_CLOSE, 0);
		return (events^EVENT_MSGE_A_CLOSE);
	}

	return 0;
}

unsigned char Msge_TaskGetID(void)
{
	return Msge_TaskID;
}

