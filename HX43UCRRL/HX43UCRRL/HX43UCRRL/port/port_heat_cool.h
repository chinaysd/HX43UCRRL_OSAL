#ifndef PORT_HEAT_COOL_H_
#define PORT_HEAT_COOL_H_

#include "SC92F732X_C.H"
#include "data_type.h"

/**
	@brief:port layer
*/
#define COOL_PIN					P17
#define HEAT_PIN					P10
#define FAN_PIN					P16

#define Set_Cool_Out(X)			((X)?(COOL_PIN = 1):(COOL_PIN = 0))	
#define Set_Heat_Out(X)			((X)?(HEAT_PIN = 1):(HEAT_PIN = 0))		
#define Set_Fan_Out(X)			((X)?(FAN_PIN = 1):(FAN_PIN = 0))	











unsigned char Port_HeatCoolInit(unsigned char id);

unsigned char Port_CoolSet(unsigned char id,unsigned char set);

unsigned char Port_HeatSet(unsigned char id,unsigned char set);

unsigned char Port_FanSet(unsigned char id,unsigned char set);




#endif

