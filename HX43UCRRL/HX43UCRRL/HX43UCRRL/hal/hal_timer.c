#include "hal_timer.h"
#include "SC92F732X_C.H"
#include "data_type.h"

static Hal_Timer_Hdl_Cb_t Hal_Timer_Hdl_Cb;


unsigned char Hal_TimerInit(void)
{
	TMCON = 0x00;		
	TMOD = 0x11;    
	TL0 = (65536 - 1000)%256;    
	TH0 = (65536 - 1000)/256;
	TR0 = 0;
	ET0 = 1;
	TR0 = 1;
	return True;
}     

unsigned char Hal_RegTimeHdl(Hal_Timer_Hdl_Cb_t func)
{
	if(!func){
		return False;
	}
	Hal_Timer_Hdl_Cb = func;

	return True;
}


void Hal_TimerIntHdl() interrupt 1{
	
	TL0 = (65536 - 999)%256;   
	TH0 = (65536 - 999)/256;
	if(Hal_Timer_Hdl_Cb){
		Hal_Timer_Hdl_Cb();
	}
}





