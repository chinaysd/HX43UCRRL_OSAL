#ifndef TASK_PUSHROD_H_
#define TASK_PUSHROD_H_

#include "hal_pushrod.h"



/**
	@brief:event id
*/
#define EVNET_PUSHROD_STOP										(0X0001)
#define EVNET_PUSHROD_A_OPEN									(0X0002)
#define EVNET_PUSHROD_A_CLOSE									(0X0004)
#define EVNET_PUSHROD_B_OPEN									(0X0008)
#define EVNET_PUSHROD_B_CLOSE									(0X0010)
#define EVNET_PUSHROD_C_OPEN									(0X0020)
#define EVNET_PUSHROD_C_CLOSE									(0X0040)
#define EVNET_PUSHROD_D_OPEN									(0X0080)
#define EVNET_PUSHROD_D_CLOSE									(0X0100)
#define EVNET_PUSHROD_E_OPEN									(0X0200)
#define EVNET_PUSHROD_E_CLOSE									(0X0400)
#define EVNET_PUSHROD_F_OPEN									(0X0800)
#define EVNET_PUSHROD_F_CLOSE									(0X1000)















/*****************************************************************************
 * Function	  : Pushrod_TaskInit
 * Description   : 
 * Input           : unsigned char task_id :task id 
 * Output		  : None
 * Return		  : SUCCEED->OK,otherwise failed
 * Others		  :  
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Pushrod_TaskInit(unsigned char task_id);

/*****************************************************************************
 * Function	  : Pushrod_TaskProcessEvent
 * Description   :  
 * Input           : unsigned char task_id :task id
			    unsigned int events :input events   
 * Output		  : None
 * Return		  : Unhandled events 
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned int Pushrod_TaskProcessEvent(unsigned char task_id,unsigned int events);

/*****************************************************************************
 * Function	  : Pushrod_TaskGetID
 * Description   : Gets the task id 
 * Input           : void  
 * Output		  : None
 * Return		  : unsigned
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Pushrod_TaskGetID(void);

#endif

