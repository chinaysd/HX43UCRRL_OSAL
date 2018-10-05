#ifndef PORT_PUSHROD_H_
#define PORT_PUSHROD_H_

#include "SC92F732X_C.H"
#include "data_type.h"

/**
	@brief:port layer
*/
#define PUSH1A_PIN				P20
#define PUSH1B_PIN				P21
#define PUSH2A_PIN				P24
#define PUSH2B_PIN				P25


#define Set_Push1A_Out(X)			((X)?(PUSH1A_PIN = 1):(PUSH1A_PIN = 0))	
#define Set_Push1B_Out(X)			((X)?(PUSH1B_PIN = 1):(PUSH1B_PIN = 0))	
#define Set_Push2A_Out(X)			((X)?(PUSH2A_PIN = 1):(PUSH2A_PIN = 0))	
#define Set_Push2B_Out(X)			((X)?(PUSH2B_PIN = 1):(PUSH2B_PIN = 0))	











unsigned char Port_PushrodInit(unsigned char id);

unsigned char Prot_PushrodOpen(unsigned char id);

unsigned char Prot_PushrodClose(unsigned char id);

unsigned char Prot_PushrodStop(unsigned char id);


#endif

