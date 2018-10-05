#include "osal_tasks.h"
#include <string.h>

#include "sys_config.h"
#include "pushrod_task.h"
#include "heat_cool_task.h"
#include "msge_task.h"
#include "app_task.h"


pTaskEventHandlerFn tasksArr[] =
{
	Pushrod_TaskProcessEvent,
	HeatCool_TaskProcessEvent,
	Msge_TaskProcessEvent,
	App_TaskProcessEvent,
};

uint8 tasksCnt;
uint16 tasksEvents[sizeof(tasksArr) /sizeof(tasksArr[0])];

void OSAL_InitTasks( void )
{
	uint8 taskID = 0;
	tasksCnt = sizeof(tasksArr) /sizeof(tasksArr[0]);
	memset( tasksEvents, 0, sizeof(tasksEvents));
	Pushrod_TaskInit(taskID ++);
	HeatCool_TaskInit(taskID ++);
	Msge_TaskInit(taskID ++);
	App_TaskInit(taskID );
}

