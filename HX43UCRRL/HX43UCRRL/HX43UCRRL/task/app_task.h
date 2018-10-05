#ifndef APP_TASK_H_
#define APP_TASK_H_

#include "sys_config.h"

/**
	@brief:event id
*/
#define EVENT_REV_MSG					0X0001
#define EVENT_HEAT_AUTO_CLS_MSG			0X0002
#define EVENT_COOL_AUTO_CLS_MSG		0X0004
#define EVENT_WARN_AUTO_CLS_MSG		0X0008
#define EVENT_MSGE_AUTO_CLS_MSG			0X0010
#define EVENT_SYS_AUTO_CLS_MSG			0X0020
#define EVENT_KEY_LOCK_MSG				0X0040
#define EVENT_RESET_MSG					0X0080
#define EVENT_FAULT_ERROR_MSG			0X8000

#define BUF_SIZE							7
#define START_FIELD						0X55
#define MSG_ID							0X01
#define STOP_MESSAGE						0X0D0A

/**
	@brief:按键值
*/
#define KEY0_VALUE						0X0001
#define KEY1_VALUE						0X0002
#define KEY2_VALUE						0X0004
#define KEY3_VALUE						0X0008
#define KEY4_VALUE						0X0010
#define KEY5_VALUE						0X0020
#define KEY6_VALUE						0X0040
#define KEY7_VALUE						0X0080

/**
	@brief:按键对应的LED指示灯
*/
#define KEY0_LED_VALUE					0X0001
#define KEY1_LED_VALUE					0X0002
#define KEY2_LED_VALUE					0X0004
#define KEY3_LED_VALUE					0X0008
#define KEY4_LED_VALUE					0X0010
#define KEY5_LED_VALUE					0X0020
#define KEY6_LED_VALUE					0X0040
#define KEY7_LED_VALUE					0X0080
#define BACK_LIGHT						0X0100

/**
	@brief:功能LED映射
*/
#define WARN_LED_MAP					KEY0_LED_VALUE
#define HEAT_LED_MAP						KEY0_LED_VALUE
#define COOL_LED_MAP					KEY5_LED_VALUE
#define MSGE_LED_MAP					KEY1_LED_VALUE
#define LIGHT_LED_MAP					KEY6_LED_VALUE
#define LOCK_LED_MAP						KEY6_LED_VALUE
#define HEAD_OPEN_LED_MAP				KEY4_LED_VALUE
#define HEAD_CLOSE_LED_MAP				KEY3_LED_VALUE
#define LUMBAR_OPEN_LED_MAP				KEY2_LED_VALUE
#define LUMBAR_CLOSE_LED_MAP			KEY1_LED_VALUE

/**
	@brief:自动关机
*/ 
#define HEAT_AUTO_CLOSE					3600000
#define WARN_AUTO_CLOSE				3600000
#define COOL_AUTO_CLOSE					7200000
#define MASS_AUTO_CLOSE					1800000
#define SYSTEM_AUTO_CLOSE				14400000	

/*
	@brief:上位机断开后，下位机保护性关机
*/
#define LOST_CTL_VALUE					5000

#define LONG_PRESS_VALUE				1500

#define LED1_PIN							P05
//#define LED2_PIN						P00

#define WARN1_PIN						P04
//#define WARN2_PIN						P05

#define F_LED_PIN							P25							/*<附杯控制>*/

typedef struct{
	INT8U buf[BUF_SIZE];
	INT8U len;
}Rev_Buf_t;

typedef struct{
	Rev_Buf_t rev_buf;
	unsigned int get_key,cur_key;
	unsigned int led_sta;
	INT8U lock_flag:1;
	INT8U lock_det_flag:1,reset_det_flag:1;
	#ifdef LED_FUNC_ENABLE
		INT8U foot_led_sta:1;
	#endif
	#ifdef WARN_FUNC_ENABLE
		INT8U warn_sta:1;
	#endif
	#ifdef COOL_FUNC_ENABLE 
		INT8U cool_flag:1;
	#endif
	#ifdef HEAT_FUNC_ENABLE
		INT8U heat_flag:1;
	#endif
	#ifdef MSGE_FUNC_ENABLE
		INT8U moto_sta:1;
	#endif
	INT8U sys_auto_cls_flag:1;
}App_Obj_t;












unsigned char App_TaskInit(unsigned char task_id);

unsigned int App_TaskProcessEvent(unsigned char task_id,unsigned int events);





#endif

