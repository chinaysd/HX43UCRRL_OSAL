#include <string.h>
#include <stdlib.h>
#include "hal_init.h"
#include "hal_uart.h"

typedef struct{
	unsigned char lock_flag;
	unsigned int len,send_cnt,buf_len;
	unsigned char *buf;
}Tx_Buf_t;

static XDATA Tx_Buf_t Tx_Buf[UART_SUM];
static Hal_UartRx_Hdl_Cb_t Hal_UartRxHdl[UART_SUM];

unsigned char Hal_UartInit(unsigned char id,unsigned char *buf,unsigned int buf_len)
{
	if(id == UART0_ID){
		#ifdef UART0_ENABLE
		SCON=0x50;
		PCON|=0x80;
		T2CON&=~0x30;
		TMCON|=0x02;
		TMOD&=0x0f;
		TMOD|=0x20;
		TH1=256 - SYS_FRE_SET/BAURATE_SET/16/2*2;
		TR1=0;
		TR1=1;
		EUART=1;
		memset((void*)&Tx_Buf[UART0_ID],0,sizeof(Tx_Buf_t));
		Tx_Buf[UART0_ID].buf = buf;
		Tx_Buf[UART0_ID].buf_len = buf_len;
		SET_OUTPUT(P1, 3);
		UART0_TX_PORT = 1;
		return id;
		#endif
	}else if(id == UART1_ID){
		#ifdef UART1_ENABLE
		unsigned int baud_set = 0;
		OTCON = 0XC0;
		SSCON0 = 0X50;
		baud_set = (unsigned int)(SYS_FRE_SET/16/BAURATE_SET);
		SSCON1 = baud_set%256;
		SSCON2 = baud_set/256;
		IE1 = 0x01;     
		SET_OUTPUT(P2, 0);
		UART1_TX_PORT = 1;
		memset((void*)&Tx_Buf[UART1_ID],0,sizeof(Tx_Buf_t));
		Tx_Buf[UART1_ID].buf = buf;
		Tx_Buf[UART1_ID].buf_len = buf_len;
		return id;
		#endif
	}else{
		return 0XFF;
	}
	return 0XFF;
}

unsigned char Hal_UartSendBuf(unsigned char id,unsigned char *buf,unsigned int len){
	if(id == UART0_ID){	
		#ifdef HAL_UART0_ENABLE
		if(!Tx_Buf[UART0_ID].lock_flag){
			if(len > Tx_Buf[UART0_ID].buf_len){
				len = Tx_Buf[UART0_ID].buf_len;
			}
			memset((void*)&Tx_Buf[UART0_ID].buf[0],0,Tx_Buf[UART0_ID].buf_len);
			memcpy((void*)&Tx_Buf[UART0_ID].buf[0],buf,len);
			Tx_Buf[UART0_ID].len = len;
			Tx_Buf[UART0_ID].lock_flag = True;
			TI = 0;
			SBUF = *buf;
		}
		#endif
	}else if(id == UART1_ID){
		#ifdef HAL_UART1_EANBLE
		if(!Tx_Buf[UART1_ID].lock_flag){
			if(len > Tx_Buf[UART1_ID].buf_len){
				len = Tx_Buf[UART1_ID].buf_len;
			}
			memset((void*)&Tx_Buf[UART1_ID],0,sizeof(Tx_Buf_t));
			memcpy(Tx_Buf[UART1_ID].buf,buf,len);
			Tx_Buf[UART1_ID].len = len;
			Tx_Buf[UART1_ID].lock_flag = True;
			SSDAT = Tx_Buf.buf[0];
		}
		#endif
	}
	return SUCCEED;
}

unsigned char Hal_RegUartRxHdl(unsigned char id,Hal_UartRx_Hdl_Cb_t cb)
{
	if(id > UART_SUM || !cb){
		return PARA_ERROR;
	}
	Hal_UartRxHdl[id] = cb;
	return SUCCEED;
}

void Hal_Uart0IntHdl() interrupt 4
{
	if(TI){
		TI=0;		
		if(Tx_Buf[UART0_ID].send_cnt == Tx_Buf[UART0_ID].len - 1){
			Tx_Buf[UART0_ID].lock_flag = False;
			memset((void*)&Tx_Buf[UART0_ID].buf[0],0,Tx_Buf[UART0_ID].len);
			Tx_Buf[UART0_ID].len = Tx_Buf[UART0_ID].send_cnt = 0;
			UART0_TX_PORT = 1;
			return ;
		}	
		SBUF = Tx_Buf[UART0_ID].buf[++Tx_Buf[UART0_ID].send_cnt];	
	}
	
	if(RI){
		RI = 0;
		if(Hal_UartRxHdl[UART0_ID]){
			Hal_UartRxHdl[UART0_ID]();
		}
	}
}

