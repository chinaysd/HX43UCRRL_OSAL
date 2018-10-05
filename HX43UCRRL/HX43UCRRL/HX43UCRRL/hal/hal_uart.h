#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "SC92F732X_C.H"

/*The number of the UART moudle*/
#define UART_SUM									1

/*Serial port baud rate Settings*/
#define BAURATE_SET								9600

/*Hardware serial port selection*/	
#define UART0_ID									0X00
#define UART1_ID									0X01

/*UART PORT*/
#define UART0_TX_PORT							P13
#define UART1_TX_PORT							P20

/*callback handler type*/
typedef void (*Hal_UartRx_Hdl_Cb_t)(void);









/*****************************************************************************
 * Function	  : Hal_UartInit
 * Description   : Hardware serial port initialization 
 * Input           : unsigned char id : Hardware serial port    
			    unsigned char *buf : Configure the serial port to receive the cache   
			    unsigned int buf_len : Configure the serial port to receive the cache length
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180712
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_UartInit(unsigned char id,unsigned char *buf,unsigned int buf_len);

/*****************************************************************************
 * Function	  : Hal_UartSendBuf
 * Description   : Send data through a serial port 
 * Input           : unsigned char id : Hardware serial port      
			    unsigned char *buf :The data you want to send 
			    unsigned int len : The length of data you want to send  
 * Output		  : None
 * Return		  : unsigned char :SUCCEED->ok ;otherwise->failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180712
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_UartSendBuf(unsigned char id,unsigned char *buf,unsigned int len);

/*****************************************************************************
 * Function	  : Hal_RegUartRxHdl
 * Description   : Register the serial port interrupt reception handler  
 * Input           : unsigned char id  :uart id
			    Hal_UartRx_Hdl_Cb_t cb  :callback function 
 * Output		  : None
 * Return		  : unsigned
 * Others		  : 
 * Record
 * 1.Date		  : 20180814
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
unsigned char Hal_RegUartRxHdl(unsigned char id,Hal_UartRx_Hdl_Cb_t cb);

#endif

