#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

typedef void (*Hal_Timer_Hdl_Cb_t)(void);
















unsigned char Hal_TimerInit(void);

unsigned char Hal_RegTimeHdl(Hal_Timer_Hdl_Cb_t func);




#endif
