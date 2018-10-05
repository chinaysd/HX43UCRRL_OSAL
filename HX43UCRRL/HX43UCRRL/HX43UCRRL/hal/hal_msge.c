#include "hal_msge.h"
#include <string.h>

typedef struct{
	INT8U id:4;
	INT8U mode:4; 		
	INT8U sw_sta:1; 						/*<switch>*/
	INT8U sup_flag:1;		
	INT8U sw_type:1;						/*<Motor mode switching mode.>*/
	INT8U intensity:5;						/*<Motor strength value>*/
}Msge_Obj_t;

static XDATA INT8U Motor_Ctr[MSGE_SUM][GROUP_OF_MSGE];
static XDATA INT8U FreCnt[MSGE_SUM],Mode_SwCnt[MSGE_SUM];
static XDATA INT16U TimeCnt[MSGE_SUM],TimeCntFlag[MSGE_SUM];
static XDATA INT16U AutoSwitchCnt[MSGE_SUM];
static XDATA Msge_Obj_t Msge_Obj[MSGE_SUM];

static unsigned char Hal_MsgeOpen(unsigned char id)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	if(id == 0){
		Msge_Obj[id].intensity = DEFAULT_MSGE_INTEN;
		Msge_Obj[id].mode = DEFAULE_MSGE_MODE;
		Msge_Obj[id].sup_flag = False;
		Msge_Obj[id].sw_sta = True;
		Msge_Obj[id].sw_type = DEFAULT_MSGE_CTL_TYPE;
		return SUCCEED;
	}
	return PARA_ERROR;
}

static unsigned char Hal_MsgeClose(unsigned char id)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	Msge_Obj[id].sw_sta = False;
	if(id == 0){
		Set_MotorA_Out(0);
		Set_MotorB_Out(0);
	}
	return SUCCEED;
}

static unsigned char Hal_MsgeSupend(unsigned char id)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	Msge_Obj[id].sup_flag = TRUE;
	Port_MsgeSet(id, 0, 0);
	Port_MsgeSet(id, 1, 0);
	return SUCCEED;
}

static unsigned char Hal_MsgeResume(unsigned char id)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	Msge_Obj[id].sup_flag = FALSE;
	return SUCCEED;
}

static unsigned char Hal_MsgeGetRunSta(unsigned char id,unsigned char *sta)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	*sta = Msge_Obj[id].sw_sta && (!Msge_Obj[id].sup_flag);
	return SUCCEED;
}

static unsigned char Hal_MsgeSetMode(unsigned char id,unsigned char mode)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	Msge_Obj[id].mode = mode;
	return SUCCEED;
}

static unsigned char Hal_MsgeSetIntensity(unsigned char id,unsigned char inten)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	Msge_Obj[id].intensity = inten;
	return SUCCEED;
}

unsigned char Hal_MsgeInit(unsigned char sum)
{
	int i;
	if(sum > MSGE_SUM)
		return PARA_ERROR;
	
	for(i = 0; i < MSGE_SUM;i ++){
		if(Port_MsgeInit(i) != i)
			break;
		memset(&Msge_Obj[i],0,sizeof(Msge_Obj_t));
		Msge_Obj[i].id = i;
		AutoSwitchCnt[i] = 0;
		TimeCnt[i] = 0; 
		TimeCntFlag[i] = 0;
		FreCnt[i] = 0;
		Mode_SwCnt[i] = 0;
	}
	
	if(i != sum)
		return SET_ERROR;
	else
		return SUCCEED;
}

unsigned char Hal_MsgePoll(unsigned char sum)
{
	int i;
	if(sum > MSGE_SUM)
		return PARA_ERROR;
	
	for(i = 0;i < sum ;i ++){
		if(Msge_Obj[i].sw_type == AUTO_CTR){
			if(AutoSwitchCnt[i]  > M_SWITCH_VALUES){
				AutoSwitchCnt[i] = 0; 
				TimeCnt[i] = 0;
				if(Msge_Obj[i].mode ++ > M_MODE_3){
					Mode_SwCnt[i] = 0;
					Msge_Obj[i].mode = M_MODE_1;
				}
			}
		}

		switch(Msge_Obj[i].mode){
			case M_MODE_1:{
				TimeCntFlag[i] = True;
				if(TimeCnt[i] > M_500MS){	
					TimeCnt[i] = 0;
					if(Mode_SwCnt[i] ++ >= 2){
						Mode_SwCnt[i] = 0;
					}
					Motor_Ctr[i][NUM_0] = (Mode_SwCnt[i] == 0) ? True:False;
					Motor_Ctr[i][NUM_1] = (Mode_SwCnt[i] == 1) ? True:False;
				}
				break;
			}
			case M_MODE_2:{
				TimeCntFlag[i] = True;
				if(TimeCnt[i] > M_1S){
					Mode_SwCnt[i] = !Mode_SwCnt[i];
					Motor_Ctr[i][NUM_0] = (Mode_SwCnt[i]) ? True:False;
					Motor_Ctr[i][NUM_1] = !Motor_Ctr[i][0];
					TimeCnt[i] = 0;
				}
				break;
			}
			case M_MODE_3:{
				TimeCntFlag[i] = True;
				if(TimeCnt[i] > M_1S){
					TimeCnt[i] = 0;
					Mode_SwCnt[i] =!Mode_SwCnt[i];
					Motor_Ctr[i][NUM_0] = (Mode_SwCnt[i]) ? True:False;
					Motor_Ctr[i][NUM_1] = (Mode_SwCnt[i]) ? True:False;
				}
				break;
			}
			default:{
				Msge_Obj[i].mode = M_MODE_1;
				break;
			}
		}
	
	}
	return SUCCEED;
}

unsigned char Hal_MsgeTimeHdl(unsigned char sum)
{
	int i;
	if(sum > MSGE_SUM)
		return PARA_ERROR;
	for(i = 0;i < MSGE_SUM;i ++){
		if(Msge_Obj[i].sw_sta && (!Msge_Obj[i].sup_flag)){
			FreCnt[i] ++;
		
			if(FreCnt[i] < Msge_Obj[i].intensity){
				if(Motor_Ctr[i][NUM_0]){
					Port_MsgeSet(i, NUM_0, 1);
				}else{
					Port_MsgeSet(i, NUM_0, 0);
				}
				if(Motor_Ctr[i][NUM_1]){
					Port_MsgeSet(i, NUM_1, 1);
				}else{
					Port_MsgeSet(i, NUM_1, 0);
				}
			}else {
				Port_MsgeSet(i, NUM_0, 0);
				Port_MsgeSet(i, NUM_1, 0);
				if(FreCnt[i] > 13){				
					FreCnt[i] = 0;
				}
			}

			if(TimeCntFlag[i]){
				TimeCnt[i] ++;
			}
			
			if(Msge_Obj[i].sw_type == AUTO_CTR){
				AutoSwitchCnt[i] ++;
			}
		}
	}
	
	
	return SUCCEED;
}

unsigned char Hal_MsgeControl(unsigned char id,unsigned char cmd,void *arg)
{
	if(id > MSGE_SUM)
		return PARA_ERROR;
	switch(cmd){
		case MSGE_CMD_OPEN:{
			return Hal_MsgeOpen(id);
		}
		
		case MSGE_CMD_CLOSE:{
			return Hal_MsgeClose(id);
		}

		case MSGE_CMD_GET_RUN_STA:{
			return Hal_MsgeGetRunSta(id, (unsigned char*)arg);
		}

		case MSGE_CMD_SUPEND:{
			return Hal_MsgeSupend(id);
		}

		case MSGE_CMD_RESUME:{
			return Hal_MsgeResume(id);
		}

		case MSGE_CMD_SET_MODE:{
			unsigned char mode = *((unsigned char*)arg);
			return Hal_MsgeSetMode(id, mode);
		}

		case MSGE_CMD_SET_INTENSITY:{
			unsigned char inten = *((unsigned char*)arg);
			return Hal_MsgeSetIntensity(id, inten);
		}
		
		default:
			return PARA_ERROR;
	}
}
