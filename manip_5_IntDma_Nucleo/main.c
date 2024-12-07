//usart_send_polling

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

char password[]="QUANTUM001";
char Receive_Buffer[10]; 
char Transmit_Buffer[]="Code-Is-OK";

uint8_t Nbre_Received_Caracters;//Une variable qui permet d'indiquer si 8 caractères ont été reçus

// Structures

GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
 
/* Private functions ---------------------------------------------------------*/
void Config_USART2 (void);
void Config_USART2_Rx_INT (void);
void Config_USART2_Tx_DMA (void);

void Delay(vu32 nCount);
uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength);

int main(void)
{
/* ================  Configure the Periph Clocks ===================== */

  /* Enable GPIOx and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USART2 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	
  /* ================  Configure the GPIO ports ===================== */

    /*Configure (LED) PA5 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
Config_USART2();
Config_USART2_Rx_INT();
Config_USART2_Tx_DMA();

	 
/*----------------------------------------------------------*/

	while(1){
	}//END while

} // End main               


//-- Functions
void Config_USART2(void )
{
	/* Configure USART2 Tx (PA2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = ........;
  GPIO_InitStructure.GPIO_Mode = ..........;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA3) as input floating */
  GPIO_InitStructure.GPIO_Pin = ...........;
  GPIO_InitStructure.GPIO_Mode = .............;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/* ====================  USART2 configuration ======================*/
    /* USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = .....;
  USART_InitStructure.USART_WordLength = .........;
  USART_InitStructure.USART_StopBits = ............;
  USART_InitStructure.USART_Parity = .............. ;
  USART_InitStructure.USART_HardwareFlowControl = ..............;
  USART_InitStructure.USART_Mode = ...................;

// Initialize UART 2 registers with specified parameters
  ............(......, .............);
	
			/* Enable the USARTx */
		USART_Cmd(....., ...........);
}

// Config_USART2_Rx_INT : to enable Interrupts generation by USART2 Rx
// Enable UART2_RX interrupt in NVIC
void Config_USART2_Rx_INT (void)
{
		/*Enable  Rx Interrupt (s) on USART2*/
		USART_ITConfig(........., ..........., ..........);	

     /* Enable and set USART2 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = ..........;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ..............;
   NVIC_Init(&NVIC_InitStructure);	 
}	 



// Config_USART2_Tx_DMA : Enable DMA Transfer from Mem to USART2 
// Enable and configure TC (Transfer Complete) Interrupt
void Config_USART2_Tx_DMA (void)
{
	 	/*Enable  Tx DMA Request (s) on USART2*/
//		USART_DMACmd(........, ..........., ...........);

///* ====================  DMA configuration ======================*/
//		//DMAx channelx (UART2 TX) configuration */
//		DMA_InitStructure.DMA_PeripheralBaseAddr = .............;
//		DMA_InitStructure.DMA_MemoryBaseAddr = ....................;
//		DMA_InitStructure.DMA_DIR = ....................;
//		DMA_InitStructure.DMA_BufferSize = ........;
//		DMA_InitStructure.DMA_PeripheralInc = ..................;
//		DMA_InitStructure.DMA_MemoryInc = ..............;
//		DMA_InitStructure.DMA_PeripheralDataSize = ...................;
//		DMA_InitStructure.DMA_MemoryDataSize = ....................;
//		DMA_InitStructure.DMA_Mode = .................;
//		DMA_InitStructure.DMA_Priority = .................;
//		DMA_InitStructure.DMA_M2M = ....................;	
//		
//		//Initilize DMA Channel Registers 
//		..........(.............., );

//		/* Enable DMAx Channely Transfer Complete/ Half Transfer interrupts */
//		DMA_ITConfig(..........., ................., .........);


//     /* Enable and set DMAx Channel y Interrupt  */
//   NVIC_InitStructure.NVIC_IRQChannel = ....................;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);	
}


uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength){
    int i=0;
   
    while(str1[i]!='\0' && str2[i]!='\0' && i<StrLength){
         if(str1[i]!=str2[i]){
             return 0;             
         }
         i++;
    }
         return 1;

}
  
/******************** Function Name  : Delay**************************/
void Delay(vu32 nCount)
{  for(; nCount != 0; nCount--);}


