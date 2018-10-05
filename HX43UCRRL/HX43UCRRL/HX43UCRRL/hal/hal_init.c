#include "hal_init.h"


unsigned char App_TxBuf[7];

void Hal_Init(void)
{
	Hal_TimerInit();
	Hal_MsgeInit(MSGE_SUM);
	Hal_PushrodInit(PUSHROD_SUM);
	Hal_HeatCoolInit(HEAT_COOL_SUM);
	Hal_UartInit(UART0_ID, App_TxBuf, sizeof(App_TxBuf));
}

void Hal_ProcessPoll(void)
{
	Hal_MsgePoll(MSGE_SUM);
}



