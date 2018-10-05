#include <string.h>
#include <stdlib.h>
#include "comdef.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "hal_init.h"

uint8 osal_set_event( uint8 task_id, uint16 event_flag )
{
	if ( task_id < tasksCnt ){
		halIntState_t   intState;
		HAL_ENTER_CRITICAL_SECTION(intState);   
		tasksEvents[task_id] |= event_flag; 		 
		HAL_EXIT_CRITICAL_SECTION(intState);   
		return ( SUCCESS );
	}else{
		return ( INVALID_TASK );
	}
}

uint8 osal_clear_event( uint8 task_id, uint16 event_flag )
{
	if ( task_id < tasksCnt ){
		halIntState_t   intState;
		HAL_ENTER_CRITICAL_SECTION(intState);   
		tasksEvents[task_id] &= ~(event_flag);     
		HAL_EXIT_CRITICAL_SECTION(intState);
		return ( SUCCESS );
	}else{
		return ( INVALID_TASK );
	}
}

void osal_run_system( void )
{
	for(;;){			
		uint8 idx = 0;
		#ifdef WDT_FUNC_ENABLE
		CLEAR_WDT();
		#endif
		Hal_ProcessPoll();
		do {
			if (tasksEvents[idx]){
				break;
			}
		} while (++idx < tasksCnt);

		if (idx < tasksCnt){
			uint16 events = 0,ret=0;
			halIntState_t intState;

			HAL_ENTER_CRITICAL_SECTION(intState);
			events = tasksEvents[idx];
			tasksEvents[idx] = 0;
			HAL_EXIT_CRITICAL_SECTION(intState);

			events = (tasksArr[idx])( idx, events );

			HAL_ENTER_CRITICAL_SECTION(intState);
			tasksEvents[idx] |= events;
			HAL_EXIT_CRITICAL_SECTION(intState);
		}
	}
}

