
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t Nber_Transfer_DMA;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


extern uint8_t One_second;
int mscount;
void SysTick_Handler(void)
{
	mscount++;
	if (mscount >=1000)
		One_second=1;
}


/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

void DMA1_Channel6_IRQHandler(void)
{
  /* Test on DMA1 Channel6 Transfer Complete interrupt */
  if( DMA_GetITStatus(DMA1_IT_TC6))
  {

    //A chaque fin d'un cycle de transfert 
	//incrémenter Nber_Transfer_DMA++
	
  		if (One_second==0) Nber_Transfer_DMA++;
		
    
    /* Clear DMA1 Channel6 Global interrupt pending bits */
   DMA_ClearITPendingBit(DMA1_IT_TC6);
  }
  
  
}





/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
