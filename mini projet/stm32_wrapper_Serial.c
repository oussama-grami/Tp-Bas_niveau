/* ***************************************************************************/
/* WRAPPER LAYER : ADAPT OO Pin REPRESENTATION (mbed) TO ST Firmware Libraray*/
/* OO Representation : PA_0 = 0x01, PA_1=0x01, ...., PA_15=0x0F              */
/*                   : PB_0 = 0x11, PB_1=0x11, ...., PB_15=0x1F              */
/*																																           */
/* OO --> ST Firmware  : PA_0 --> serialA, serial_Pin_0 							           */
/*											 PB_12 --> serialB, serial_Pin_12							           */
/* Emir DAMERGI  -  INSAT 2021                                               */

/* ***************************************************************************/

#include "stm32_wrapper_serial.h"
/*================================================*/
/*     Part 1: Functions For PinAsInput Class     */
/*================================================*/


/*=== Functions Called by The PinAsInput Constructors ===*/

/*Constructor Without Mode = Default = Floating*/
void serial_init_in_def(PinName pin) 
{
    serial_init_in (pin, InDefault);
}

/*Constructor With Mode */
void serial_init_in (PinName pin, PinInMode mode)
{
    _serial_init_in(pin, mode);
}


/*=== Function To get serial mode for ST FW lib === */
static uint16_t get_serial_mode (UartMode mode)
{	
	switch (mode){
		case 1: return USART_Mode_Tx;break;
		case 2: return USART_Mode_Rx;break;
		case 3: return USART_Mode_Rx | USART_Mode_Tx;break;
		default: return USART_Mode_Rx | USART_Mode_Tx; break;
		}
}
static uint16_t get_serial_comport (UartComport comport)
{	
	switch (comport){
		case 1: return USART_HardwareFlowControl_RTS;break;
		case 2: return USART_HardwareFlowControl_None;break;
		case 3: return USART_HardwareFlowControl_CTS;break;
		default: return USART_HardwareFlowControl_None;break;
		}
}


static uint32_t get_serial_speed (UartSpeed speed)
{	
	switch (speed){
		case 1: return 9600;break;
		case 2: return 19200;break;
		case 3: return 115200;break;
		default: return 9600; break;
		}
}
static config_typedef get_serial_config (UartConfig config)
{	
	config_typedef conf;
	
	switch (config){
		case 1: conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_No;conf.StopBits = USART_StopBits_1;break;
		case 2:  conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_No;conf.StopBits = USART_StopBits_2;break;
		case 3:  conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_Even;conf.StopBits = USART_StopBits_1;break;
		case 4:  conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_Even;conf.StopBits = USART_StopBits_2;break;
		case 5:  conf.WordLength = USART_WordLength_8b;conf.Parity =USART_Parity_Odd;conf.StopBits = USART_StopBits_1;break;
		case 6:  conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_Odd;conf.StopBits = USART_StopBits_2;break;
		case 7:   conf.WordLength = USART_WordLength_9b ;conf.Parity =USART_Parity_No;conf.StopBits = USART_StopBits_1;break;
		case 8:  conf.WordLength = USART_WordLength_9b;conf.Parity =USART_Parity_No;conf.StopBits = USART_StopBits_2;break;
		case 9:  conf.WordLength = USART_WordLength_9b ;conf.Parity =USART_Parity_Even;conf.StopBits = USART_StopBits_1;break;
		case 10:  conf.WordLength = USART_WordLength_9b ;conf.Parity =USART_Parity_Even;conf.StopBits = USART_StopBits_2;break;
		case 11:  conf.WordLength = USART_WordLength_9b ;conf.Parity =USART_Parity_Odd;conf.StopBits = USART_StopBits_1;break;
		case 12:  conf.WordLength = USART_WordLength_9b ;conf.Parity =USART_Parity_Odd;conf.StopBits = USART_StopBits_2;break;
		
		default: conf.WordLength = USART_WordLength_8b ;conf.Parity =USART_Parity_No;conf.StopBits = USART_StopBits_1;
		}
	return conf;
}
//static methode to activate gpio pin
static void GPIO_Pin_init(GPIO_TypeDef* GPIOx ,uint16_t Pin,GPIOMode_TypeDef mode ){
	GPIO_InitTypeDef GPIO_InitStruct;
	
// Enable used GPIOs Clocks
GPIO_InitStruct.GPIO_Pin = Pin;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStruct.GPIO_Mode = mode;
GPIO_Init( GPIOx, &GPIO_InitStruct);
}

/*=== Function To read Pin Value from IDR ====== */
	int serial_read(PinName pin)
{
	int pinID = (pin & 0x0F);
	int pinValue =  (get_serialport(pin)->IDR) & (1<<pinID);
	return (pinValue) ;
}

/*--------------------------------------------------------------*/
/*   INITIALLIZATION FUNCTION for PinAsInput Objects :          */          
/*      - Translates OO Pin Represetation (Px_i) to ST FWL      */
/*      - And Calls ST FWLibrary Functions                      */
/*--------------------------------------------------------------*/
static USART_TypeDef* _serial_init(uint8_t COMPORT, uint8_t PinTX, uint8_t PinRX ,uint16_t Speed, uint8_t Config, uint8_t Mode)
{
	
		//get the serialID from PinName (0 for serialA, 1 for serialB, ...) 	
	int gpioId = (PinTX & 0xF0) >> 4;
	int pinIdTX  = (PinTX & 0x0F);
	GPIO_TypeDef* gpio;
	uint16_t pinTX;
	uint16_t pinRX;
	switch(gpioId){
		case 0 : gpio = GPIOA;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);break;
		case 1 : gpio = GPIOB;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);break;
		case 2 : gpio = GPIOC;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);break;
		default: break;
	}
	switch(pinIdTX){
		case 0:pinTX =GPIO_Pin_0;break;
		case 1:pinTX =GPIO_Pin_1;break;
		case 2:pinTX =GPIO_Pin_2;break;
		case 3:pinTX =GPIO_Pin_3;break;
		case 4:pinTX =GPIO_Pin_4;break;
		case 5:pinTX =GPIO_Pin_5;break;
		case 6:pinTX =GPIO_Pin_6;break;
		case 7:pinTX =GPIO_Pin_7;break;
		case 8:pinTX =GPIO_Pin_8;break;
		case 9:pinTX =GPIO_Pin_9;break;
		case 10:pinTX =GPIO_Pin_10;break;
		case 11:pinTX =GPIO_Pin_11;break;
		case 12:pinTX =GPIO_Pin_12;break;
		case 13:pinTX =GPIO_Pin_13;break;
		case 14:pinTX =GPIO_Pin_14;break;
		case 15:pinTX =GPIO_Pin_15;break;
		default: break;
	}
	pinRX = pinTX <<1;
	
	
	USART_InitTypeDef USART_InitStructure ; 
	  //convert serialID to serialx
	uint16_t mode = get_serial_mode (Mode);
	UartSpeed speed = get_serial_speed(Speed);
	config_typedef config = get_serial_config(Config);
	UartComport comport = get_serial_comport(COMPORT);
	
	if(mode == USART_Mode_Tx){
		GPIO_Pin_init(gpio,PinTX,GPIO_Mode_AF_PP);
	}
	else if(mode == USART_Mode_Rx){
		GPIO_Pin_init(gpio,PinRX,GPIO_Mode_IN_FLOATING);
	} 
	else{
		GPIO_Pin_init(gpio,PinTX,GPIO_Mode_AF_PP);
		GPIO_Pin_init(gpio,PinRX,GPIO_Mode_IN_FLOATING);
	}
	
	USART_TypeDef* USARTx;
	switch(pinIdTX){
		case 9: USARTx = USART1; RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);break;
		case 2: USARTx = USART2; RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
		case 10: USARTx = USART3; RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
		default : break;
	}
	
	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength  = config.WordLength;
	USART_InitStructure.USART_Parity = config.Parity;
	USART_InitStructure.USART_StopBits = config.StopBits;
	USART_InitStructure.USART_HardwareFlowControl = comport;
	USART_InitStructure.USART_Mode = mode;
	
	USART_Init( USARTx, &USART_InitStructure);
	USART_Cmd( USARTx, ENABLE);
	return USARTx;
}

/*=========== End PinAsInput Class Functions =============*/


	
/*-------------------------------------------------*/
	/* Common Function : To get serialx From PinName Value */
/*_________________________________________________*/
	
