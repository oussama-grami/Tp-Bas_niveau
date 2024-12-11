#include "stm32f10x.h"
#include "Serial_Mode_Name.h"

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* =======================================*/
/* 1 : Functions For PinAsInput Class --- */
/*----------------------------------------*/
	
void serial_init_in_def(PinName pin);	
	
void serial_init_in(PinName pin, PinInMode mode);

	
int serial_read (PinName thepin);	
	
	
static USART_TypeDef* _serial_init(uint8_t COMPORT, uint8_t PinTX, uint8_t PinRX ,uint16_t Speed, uint8_t Config, uint8_t Mode);
static void GPIO_Pin_init(GPIO_TypeDef* GPIOx ,uint16_t Pin,GPIOMode_TypeDef mode );
static config_typedef get_serial_config (UartConfig config);
static uint32_t get_serial_speed (UartSpeed speed);
static uint16_t get_serial_mode (UartMode mode);
static uint16_t get_serial_comport (UartComport comport);


/*==========================================*/


	
/* --- 2 : Common Functions ---- */

/*  Get the GPIOx From PinName  */
static GPIO_TypeDef* get_gpioport (PinName pin);
	

#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_GPIO_H
