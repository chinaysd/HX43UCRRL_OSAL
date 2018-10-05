#ifndef PORT_MSGE_H_
#define PORT_MSGE_H_

#include "sys_config.h"

/**
	@brief:port layer
*/
#define MOTOR_A_PIN				P02
#define MOTOR_B_PIN				P03

#define Set_MotorA_Out(X)			((X)?(MOTOR_A_PIN = 1):(MOTOR_A_PIN = 0))	
#define Set_MotorB_Out(X)			((X)?(MOTOR_B_PIN = 1):(MOTOR_B_PIN = 0))	








unsigned char Port_MsgeInit(unsigned char id);

unsigned char Port_MsgeSet(unsigned char id,unsigned char num,unsigned char set);




#endif

