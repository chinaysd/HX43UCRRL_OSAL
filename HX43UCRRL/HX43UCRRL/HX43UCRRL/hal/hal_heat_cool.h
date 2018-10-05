#ifndef HAL_HEAT_COOL_H_
#define HAL_HEAT_COOL_H_

#include "SC92F732X_C.H"
#include "data_type.h"
/**
	@brief: The number of the heat_cool moudle
*/
#define HEAT_COOL_SUM										(1)

enum{
	HC_CLOSE = 0,
	HC_OPEN
};

typedef enum{
	HC_STOP_MODE = 0
	,HC_COOL_MODE
	,HC_HEAT_MODE
}HC_Mode_t;

typedef enum{
	HC_CMD_STOP = 0,
	HC_CMD_SET_COOL,
	HC_CMD_SET_HEAT,
	HC_CMD_SET_FAN,
	HC_CMD_GET_MODE,
	HC_CMD_SET_MODE,
	HC_CMD_SUPEND,
	HC_CMD_RESUME,
	HC_CMD_GET_SUPED_STA
}HC_Cmd_t;

/*****************************************************************************
 * Function	  : Hal_HeatCoolInit
 * Description   : 
 * Input           : unsigned char sum  :total number of heat cool moudle
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_HeatCoolInit(unsigned char sum);

/*****************************************************************************
 * Function	  : Hal_HeadCoolControl
 * Description   : heat cool module control instruction   
 * Input           : unsigned char id :Module number     
			    unsigned char cmd :@see HC_CMD_t 
			    void *arg :user data         
 * Output		  : None
 * Return		  : unsigned
 * Others		  : 
 * Record
 * 1.Date		  : 20180826
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_HeatCoolControl(unsigned char id,unsigned char cmd,void *arg);

#endif
