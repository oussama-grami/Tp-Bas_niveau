/*********************************************************************************/
/* OO STM32 Library : PinAsInput CLASS DECLARATION To configure GPIO Pins as Input 
	 E.D INSA TNov 2021 
	      Default Constructor: Floating
 
        Use:  PinAsInput  ObjectName (PA_i) , 
              where X is for GPIOX (A, B, C or D)
			        i is the pin Number (0 to 15)

		Example:  PinAsInput MyButton (PA_0);
************************************************************************************/

#include <stm32_wrapper_serial.h>

namespace OOlayer {

class Serial {
		USART_TypeDef* USARTx;
public:	

Serial MyPortCom (){
	USARTx = _serial_init(ComportDefault,0X02,0X03,SpeedDefault,ConfDefault,ModeDefault);
}
Serial MyPortCom (UartComport COMPORT,PinName PinTX, PinName PinRX){
	USARTx = _serial_init(COMPORT,PinTX,PinRX,SpeedDefault,ConfDefault,ModeDefault);
}
Serial MyPortCom (UartComport COMPORT,PinName PinTX,PinName PinRX,UartSpeed Speed){
	USARTx = _serial_init(COMPORT,PinTX,PinRX,Speed,ConfDefault,ModeDefault);
}
Serial MyPortCom (UartComport COMPORT,PinName PinTX, PinName PinRX,UartSpeed Speed,UartConfig Config){
	USARTx = _serial_init(COMPORT,PinTX,PinRX,Speed,Config,ModeDefault);
}
Serial MyPortCom (UartComport COMPORT,PinName PinTX,PinName PinRX,UartSpeed Speed,UartConfig Config,UartMode Mode){
	USARTx  = _serial_init(COMPORT,PinTX,PinRX,Speed,Config,Mode);
}
		
/***** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */

GPIO_TypeDef* get_GPIO(){
	if((USARTx == USART1) || (USARTx == USART2)) return GPIOA;
	else return GPIOB;
}
void printchaine(char* chaine , int length){
	int i;
	char Char_tosend;
		for (i=0; i <length; i++)
	{
		while (USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET); //wait until USART2 TX Register is Empty
		Char_tosend = chaine[i];
		USART_SendData(USARTx,Char_tosend);  //Send Data
	}
}

char* readchaine(int length){
	int 	nbChar = 0;
	char 	receivedChar;
	char buffer[length] ;
	while(nbChar<length){
		 		 
	 while (USART_GetFlagStatus(USART3,USART_FLAG_RXNE)==RESET); //wait until USART1 RX Register is not Empty
	 receivedChar = USART_ReceiveData (USART3);		 
	 buffer[nbChar] = receivedChar;  //read character

}



		
		
		
/***** An operator shorthand for read()
--> To Read an Input, use only The object Name
		Example:  int BtnState = MyButton;
     */
    operator int() {
        return read();
    }
}; //Class End

} //namespace
