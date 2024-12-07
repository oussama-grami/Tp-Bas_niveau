#include <gpio.h>

int GPIO_TestPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
	return GPIOx->IDR & GPIO_PIN;
}

void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->BSRR = GPIO_PIN;
	
}

void GPIO_ResetPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->BRR = GPIO_PIN;
}
void GPIO_Init(GPIO_TypeDef* GPIOx , GPIO_Struct*  GPIO_InitStruct){
	uint16_t GPIO_PIN = GPIO_InitStruct->GPIO_PIN;
	int i = 0;
	for( i = 0 ;i<16 ;i++){
			if(GPIO_PIN && 0x01 ==1 ){
				if(i<=7){
					GPIOx->CRL &= ~(0x0Fu) << (4*i); 
					GPIOx->CRL |= GPIO_InitStruct->GPIO_Mode << (4*i);
				}else{
					GPIOx->CRH &= ~(0x0Fu) << (4*(i-8)); 
					GPIOx->CRH |= GPIO_InitStruct->GPIO_Mode << (4*(i-8));
				}
			}GPIO_PIN = GPIO_PIN>> 1;
	}
}



