#ifndef MSGE_TASK_H_
#define MSGE_TASK_H_

#include "hal_msge.h"

/**
	@brief:event id
*/
#define EVENT_MSGE_A_OPEN							0X0001
#define EVENT_MSGE_A_CLOSE							0X0002
#define EVENT_MSGE_A_SUPEND							0X0004
#define EVENT_MSGE_A_RESUME							0X0008


unsigned char Msge_TaskInit(unsigned char task_id);

unsigned int Msge_TaskProcessEvent(unsigned char task_id,unsigned int events);

unsigned char Msge_TaskGetID(void);

#endif

