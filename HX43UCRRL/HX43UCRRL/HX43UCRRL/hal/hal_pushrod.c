#include "hal_pushrod.h"
#include "port_pushrod.h"

typedef enum{
	PUSH_STOP = 0,
	PUSH_OPEN,
	PUSH_CLOSE
}Push_Status_t;

typedef struct{
	unsigned char id:4;
	#ifdef PUSHROD_REVERSE_SWITCH_FUNC
	unsigned char ReverseFlag:1;
	#endif
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
	unsigned char IsRun:1;
	#endif
	Push_Status_t Sta:2;
}Push_Obj_t;

static XDATA Push_Obj_t Push_Obj[PUSHROD_SUM]; 

#ifdef PUSHROD_REVERSE_SWITCH_FUNC
static unsigned char Hal_PushrodSetReverseFlag(unsigned char id,unsigned char flag){
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	Push_Obj[id].ReverseFlag = flag;
	return SUCCEED;
}
#endif

#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
static unsigned char Hal_PushrodGetRunFlag(unsigned char id,unsigned char *flag){
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	*flag = Push_Obj[id].IsRun;
	return SUCCEED;
}
#endif

static unsigned char Hal_PushrodOpen(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].IsRun = True;
	#endif
	
	if(Prot_PushrodOpen(Push_Obj[id].id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char Hal_PushrodClose(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].IsRun = True;
	#endif
	
	if(Prot_PushrodClose(Push_Obj[id].id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char Hal_PushrodStop(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].IsRun = False;
	#endif
	
	if(Prot_PushrodStop(Push_Obj[id].id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

unsigned char Hal_PushrodInit(unsigned char sum)
{
	unsigned char i =0;
	if(sum > PUSHROD_SUM)
		return PARA_ERROR;

	for(i = 0;i < sum;i ++){
		if( i != Port_PushrodInit(i))
			break;
		Push_Obj[i].id = i;
		#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[i].IsRun = FALSE;
		#endif
		Push_Obj[i].Sta = PUSH_STOP;
	}	
	
	if(i != sum )
		return PARA_ERROR;
	return SUCCEED;
}

unsigned char Hal_PushrodControl(unsigned char id,unsigned char cmd,void *arg)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	switch(cmd){
		case PUSHROD_CMD_STOP:{
			return Hal_PushrodStop(id);
		}

		case PUSHROD_CMD_OPEN:{
			return Hal_PushrodOpen(id);
		}

		case PUSHROD_CMD_CLOSE:{
			return Hal_PushrodClose(id);
		}
		
		#ifdef PUSHROD_REVERSE_SWITCH_FUNC
		case PUSHROD_CMD_SET_REVERSE:{
			unsigned char set = *(unsigned char*)arg;
			return Hal_PushrodSetReverseFlag(id, set);
		}
		#endif

		#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		case PUSHROD_CMD_GET_RUN_STA:{
			return Hal_PushrodGetRunFlag(id, (unsigned char *)arg);
		}
		#endif
		
		default:
			return PARA_ERROR;
	}
}
