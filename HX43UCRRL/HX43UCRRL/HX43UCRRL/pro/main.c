#include "OSAL.h"
#include "osal_timer.h"
#include "osal_tasks.h"
#include "hal_init.h"
#include "sys_config.h"


void main(void)
{	
	HAL_DISABLE_INTERRUPTS();
	Hal_Init();
	OSAL_TimerInit();
	OSAL_InitTasks();
	#ifdef WDT_FUNC_ENABLE
		CLEAR_WDT();
	#endif
	HAL_ENABLE_INTERRUPTS();
	osal_run_system();




    
}
