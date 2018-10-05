#ifndef HAL_PUSHROD_H_
#define HAL_PUSHROD_H_


/**
	@function: The number of the push rod
*/
#define PUSHROD_SUM										(2)

/*
	@function :get push rod running status 
*/
//#define PUSHROD_GET_RUNNING_STATUS_FUNC

/*
	@function: reverse switch(defaults to shut down)
	@brief: can use a switch ,to control the push rod reverse
*/
//#define PUSHROD_REVERSE_SWITCH_FUNC	

/**
	@brief:push rod id
*/
#define PUSHROD_A										(0)
#define PUSHROD_B										(1)
#define PUSHROD_C										(2)
#define PUSHROD_D										(3)
#define PUSHROD_E										(4)
#define PUSHROD_F										(5)

typedef enum{	
	PUSHROD_CMD_STOP = 0,
	PUSHROD_CMD_OPEN,
	PUSHROD_CMD_CLOSE,
	PUSHROD_CMD_SET_REVERSE,
	PUSHROD_CMD_GET_RUN_STA,
}Pushrod_Cmd_t;





/*****************************************************************************
 * Function	  : Hal_PushrodInit
 * Description   :  
 * Input           : unsigned char sum  :total nums of push rod
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180710
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_PushrodInit(unsigned char sum);

/*****************************************************************************
 * Function	  : Hal_Pushrod_Control
 * Description   : Pushrod module control instruction  
 * Input           : unsigned char id  :pushrod id
			    unsigned int cmd  :@see Pushrod_Cmd_t
			    void *arg :user data        
 * Output		  : None
 * Return		  : unsigned
 * Others		  : 
 * Record
 * 1.Date		  : 20180826
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_PushrodControl(unsigned char id,unsigned char cmd,void *arg);

#endif
