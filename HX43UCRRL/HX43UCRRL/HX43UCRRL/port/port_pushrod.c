#include "port_pushrod.h"

unsigned char Port_PushrodInit(unsigned char id)
{
	if(id == 0){
		SET_OUTPUT(P2, 1);
		SET_OUTPUT(P2, 0);
		Set_Push1A_Out(0);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		SET_OUTPUT(P2, 4);
		SET_OUTPUT(P2, 5);
		Set_Push2A_Out(0);
		Set_Push2B_Out(0);
		return id;
	}	
	return 0XFF;
}

unsigned char Prot_PushrodOpen(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(1);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(1);
		Set_Push2B_Out(0);
		return id;
	}	
	return 0XFF;
}

unsigned char Prot_PushrodClose(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(0);
		Set_Push1B_Out(1);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(0);
		Set_Push2B_Out(1);
		return id;
	}	
	return 0XFF;
}

unsigned char Prot_PushrodStop(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(0);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(0);
		Set_Push2B_Out(0);
		return id;
	}	
	return 0XFF;
}


