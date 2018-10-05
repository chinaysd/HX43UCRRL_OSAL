#ifndef OSAL_TASKS_H
#define OSAL_TASKS_H

#include "data_type.h"

#define TASK_NO_TASK      0xFF

/*********************************************************************
 * TYPEDEFS
 */

/*
 * Event handler function prototype
 */
typedef unsigned short (*pTaskEventHandlerFn)( unsigned char task_id, unsigned short event );

/*********************************************************************
 * GLOBAL VARIABLES
 */
 
extern uint8 tasksCnt;
extern pTaskEventHandlerFn tasksArr[];
extern uint16 tasksEvents[];

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Call each of the tasks initialization functions.
 */
void OSAL_InitTasks( void );

#endif /* OSAL_TASKS_H */

