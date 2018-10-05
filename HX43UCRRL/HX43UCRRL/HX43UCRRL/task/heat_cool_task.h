#ifndef HEAT_COOL_H_
#define HEAT_COOL_H_

#include "sys_config.h"
#include "hal_heat_cool.h"

/*Protect the delay*/
#define HEAT_COOL_DELAY										10000

/**
	@brief:event id
*/
#define EVENT_COOL_A_OPEN									0X0008
#define EVENT_HEAT_A_OPEN									0X0010
#define EVENT_HEAT_COOL_A_CLOSE								0X0020
#define EVENT_HEAT_COOL_A_SUPEND							0X0040
#define EVENT_HEAT_COOL_A_RESUME							0X8000










unsigned char HeatCool_TaskInit(unsigned char task_id);

unsigned int HeatCool_TaskProcessEvent(unsigned char task_id,unsigned int events);

unsigned char HeatCool_TaskGetID(void);

#endif

