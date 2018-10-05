#ifndef SYS_CONFIG_H_
#define SYS_CONFIG_H_

#include "SC92F732X_C.H"
#include "data_type.h"

/**
	@brief:Crystal oscillator frequency Settings
*/
#define SYS_FRE_SET										(12000000UL)

/**
	@brief:feed dogs 
*/
#define CLEAR_WDT()										(WDTCON  = 0x10)	

#define st(x)      											do { x } while (__LINE__ == -1)

#define HAL_ENABLE_INTERRUPTS()         						st( EA = 1; )
#define HAL_DISABLE_INTERRUPTS()        						st( EA = 0; )
#define HAL_INTERRUPTS_ARE_ENABLED()    					(EA)

typedef unsigned char halIntState_t;
#define HAL_ENTER_CRITICAL_SECTION(x)   					st( x = EA;  HAL_DISABLE_INTERRUPTS(); )
#define HAL_EXIT_CRITICAL_SECTION(x)    					st( EA = x; )
#define HAL_CRITICAL_STATEMENT(x)       					st( halIntState_t _s; HAL_ENTER_CRITICAL_SECTION(_s); x; HAL_EXIT_CRITICAL_SECTION(_s); )

/**
	@brief:function definition
*/
#define COOL_FUNC_ENABLE
//#define HEAT_FUNC_ENABLE
#define MSGE_FUNC_ENABLE 
#define WARN_FUNC_ENABLE
#define LED_FUNC_ENABLE
#define PUSHROD_HEAD_FUNC_ENABLE
#define PUSHROD_LUMBAR_FUNC_ENABLE
#define PUSHROD_RESET_FUNC_ENABLE
#define WDT_FUNC_ENABLE
#ifdef PUSHROD_HEAD_FUNC_ENABLE
	#define PUSHROD_FUNC_ENABLE				1
#endif
#ifdef PUSHROD_LUMBAR_FUNC_ENABLE			
	#define PUSHROD_FUNC_ENABLE				1
#endif
#define UART0_ENABLE
//#define UART1_ENABLE

#endif

