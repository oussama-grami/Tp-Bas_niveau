
// Interrupts EXTI Project

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
............    ...........;//EXTI
............    ...........; // NVIC
 
/* Private functions ---------------------------------------------------------*/
void Delay(vu32 nCount);

u8 i;
  
int main(void)
{

  
/* Activer les horloges des ports utilisés */
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);  //AFIO for alternate functions

 /* Configure PA5 (LED) Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PC13 (Button) as Input push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  
      /* Connect Button EXTI Line to Button GPIO Pin */
     GPIO_EXTILineConfig(................, GPIO_PinSource.....);

    /* Configure Button EXTI line */
   EXTI_InitStructure.EXTI_Line = .......;
   EXTI_InitStructure.EXTI_Mode = ...........;
   EXTI_InitStructure.EXTI_Trigger = ............; 
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStructure);


   /* Enable and set Button EXTI Interrupt to the lowest priority */

   NVIC_InitStructure.NVIC_IRQChannel = ...........;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
    

    /* Turn on led connected to PA5 pin */
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    /* Insert delay */
    Delay(0xFFFFF);

   
  /* Infinite loop */
  while (1)  
    { 
		//Led OFF
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      }
}

/******************** Function Name  : Delay**************************/
void Delay(vu32 nCount)
{  for(; nCount != 0; nCount--);}
