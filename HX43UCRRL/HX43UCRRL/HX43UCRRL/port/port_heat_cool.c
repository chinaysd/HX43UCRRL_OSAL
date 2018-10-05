#include "port_heat_cool.h"

unsigned char Port_HeatCoolInit(unsigned char id)
{
	if(id == 0){
		SET_OUTPUT(P1, 7);
		Set_Cool_Out(0);
		SET_OUTPUT(P1, 0);
		Set_Heat_Out(0);
		SET_OUTPUT(P1, 6);
		Set_Fan_Out(0);
		return id;
	}
	return 0XFF;
}

unsigned char Port_CoolSet(unsigned char id,unsigned char set)
{
	if(id == 0){
		Set_Cool_Out(set);
		return id;
	}
	return 0XFF;
}

unsigned char Port_HeatSet(unsigned char id,unsigned char set)
{
	if(id == 0){
		Set_Heat_Out(set);
		return id;
	}
	return 0XFF;
}

unsigned char Port_FanSet(unsigned char id,unsigned char set)
{
	if(id == 0){
		Set_Fan_Out(set);
		return id;
	}
	return 0XFF;
}

