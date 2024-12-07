
#include "stm32f10x.h"


//Global Var
uint32_t Nbr_loops;


/* declaration des structures relatives aux periphs utilisés -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;


/* Private functions ---------------------------------------------------------*/
void Delay(vu32 nCount);


int main(void)
{  /* activer l'horloge du port c connecté aux leds */
 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    /* Configurer les pins PA5  du port A */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;// output Push Pull
		GPIO_Init(GPIOA, &GPIO_InitStructure);

while (1)	{
	  
       //allumer des deux leds reliées aux bits PC8 et PC9
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	Delay (0xFFFFF);
	 
        // les éteindre
  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	Delay (0xFFFFF);
			 
	Nbr_loops++;
				}
}
///************** Function Name  : Delay  *****************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
