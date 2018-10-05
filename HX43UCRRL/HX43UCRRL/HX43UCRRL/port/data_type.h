#ifndef DATA_TYPE_C_HEADER
#define DATA_TYPE_C_HEADER

typedef bit 			    	BOOL; 		
typedef unsigned char		CHAR;		
typedef unsigned char 		INT8U; 		
typedef signed char 		INT8S; 		
typedef unsigned int 		INT16U; 	
typedef signed int 		    	INT16S; 	
typedef unsigned long 		INT32U; 	
typedef signed long 		INT32S; 
typedef float 			    	FP32; 		
typedef double 			FP64; 		
typedef signed   char   		int8;    			
typedef unsigned char   	uint8;   			 
typedef signed   short  		int16;    			
typedef unsigned short  	uint16;  			
typedef signed   long   		int32;    			
typedef unsigned long   	uint32;  	

#define	BS(SFR,NUM)		(SFR|=(1<<NUM))		
#define	BC(SFR,NUM)		(SFR&=~(1<<NUM))

#define 	True				1
#define 	False			0
#define 	Enable			1
#define 	Disable			0

#define	BIT0				0x01
#define	BIT1				0x02
#define	BIT2				0x04
#define	BIT3				0x08
#define	BIT4				0x10
#define	BIT5				0x20
#define	BIT6				0x40
#define	BIT7				0x80
#define	BIT8				0x0100
#define	BIT9				0x0200

#define Get_Low(x)										((x) & 0XFF)
#define Get_High(x)										(((x) >> 8) & 0XFF)
#define Get_32bit(x,y)										((((x) << 8) | (y)) & 0XFFFF)

/**
	@brief:Set to the output
*/
#define SET_OUTPUT(X,Y)									(X##CON |= ((1)<<(Y)))
#define SET_INPUT(X,Y)									(X##CON &= ~((1)<<(Y)))

/**
	@brief:IO Pull-up register Settings
*/
#define SET_IO_PU(X,Y)									(X##PH |= ((1)<<(Y)))
#define CLR_IO_PU(X,Y)									(X##PH &= ~((1)<<(Y)))

#define CODE   											code
#define XDATA  											xdata
#define ASM_NOP  										 __nop()	

/**
	@brief:type of error
*/
#define SUCCEED											0
#define PARA_ERROR										1
#define SET_ERROR										2

#ifndef ON
#define ON  												1
#endif

#ifndef OFF
#define OFF 												0
#endif

#ifndef FALSE
#define FALSE 											0
#endif

#ifndef TRUE
#define TRUE												1
#endif


#endif
