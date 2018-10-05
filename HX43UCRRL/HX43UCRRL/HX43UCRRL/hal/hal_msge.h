#ifndef HAL_MSGE_H_
#define HAL_MSGE_H_

#include "port_msge.h"

/**
	@function: The number of the msge
*/
#define MSGE_SUM								1

/**
	@brief:Number of motors per set
*/
#define GROUP_OF_MSGE							2
#define NUM_0									0
#define NUM_1									1

/**
	@breif:Motor toggle time definition.
*/
#define M_500MS									500		
#define M_1S										1000
#define M_SWITCH_VALUES							60000

/**
	@brief:mode definition
*/
enum{
	M_MODE_1 =0,
	M_MODE_2,
	M_MODE_3
};

/**
	@breif:Mode control type
*/
enum{
	MANUAL_CTR = 0,
	AUTO_CTR
};

/**
	@brief:default config
*/
#define DEFAULT_MSGE_INTEN							8
#define DEFAULT_MSGE_CTL_TYPE						AUTO_CTR
#define DEFAULE_MSGE_MODE							M_MODE_1

/**
	@brief:device control command
*/
typedef enum{
	MSGE_CMD_OPEN = 0x01,
	MSGE_CMD_CLOSE,
	MSGE_CMD_GET_RUN_STA,
	MSGE_CMD_SUPEND,
	MSGE_CMD_RESUME,
	MSGE_CMD_SET_MODE,
	MSGE_CMD_SET_INTENSITY
}Msge_Cmd_t;

/*****************************************************************************
 * Function	  : Hal_MsgeInit
 * Description   :  
 * Input           : unsigned char sum  :total number of heat cool moudle
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180712
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_MsgeInit(unsigned char sum);

/*****************************************************************************
 * Function	  : Hal_MsgePoll
 * Description   : The polling process msge 
 * Input           : unsigned char sum :total number of heat cool moudle 
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180712
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_MsgePoll(unsigned char sum);

/*****************************************************************************
 * Function	  : Hal_MsgeTimeHdl
 * Description   : Regular calls(1ms) 
 * Input           : unsigned char sum :total number of heat cool moudle  
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180712
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_MsgeTimeHdl(unsigned char sum);

/*****************************************************************************
 * Function	  : Hal_MsgeControl
 * Description   : Motor module control instruction  
 * Input           : unsigned char id  : msge id
			    unsigned int cmd  : @see Msge_Cmd_t
			    void *arg  :  user data     
 * Output		  : None
 * Return		  : unsigned
 * Others		  : 
 * Record
 * 1.Date		  : 20180826
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_MsgeControl(unsigned char id,unsigned char cmd,void *arg);

#endif

