#ifndef HAL_INIT_H_
#define HAL_INIT_H_

#include "SC92F732X_C.H"
#include "data_type.h"

#include "hal_timer.h"
#include "hal_msge.h"
#include "hal_pushrod.h"
#include "hal_heat_cool.h"
#include "hal_uart.h"
















/*****************************************************************************
 * Function	  : Hal_Init
 * Description   : Hal initialization 
 * Input           : void  
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180814
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
void Hal_Init(void);

/*****************************************************************************
 * Function	  : Hal_ProcessPoll
 * Description   : Hal polling processing 
 * Input           : void  
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180814
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
void Hal_ProcessPoll(void);

#endif

