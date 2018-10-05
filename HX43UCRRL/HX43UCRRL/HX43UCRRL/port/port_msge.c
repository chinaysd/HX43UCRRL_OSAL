#include "port_msge.h"

unsigned char Port_MsgeInit(unsigned char id)
{
	if(id == 0){
		SET_OUTPUT(P0, 2);
		Set_MotorA_Out(0);
		SET_OUTPUT(P0, 3);
		Set_MotorB_Out(0);
		return id;
	}
	return 0XFF;
}

unsigned char Port_MsgeSet(unsigned char id,unsigned char num,unsigned char set)
{
	if(id == 0){
		if(num == 0){
			Set_MotorA_Out(set);
		}else if(num == 1){
			Set_MotorB_Out(set);
		}else{
			return 0XFF;
		}
		return id;
	}	
	return 0XFF;
}

