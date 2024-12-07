#include <gpio.h>


#define   RCC_APB2ENR     (uint32_t*) 0x40021018
uint8_t EtatBouton;

int main ()
{	
	//Activate GPIOs Clocks
 
	 *RCC_APB2ENR  |=  .............; //Activation de l'horloge du PORT A/C

	//Configure GPIO Pins (Push Button)=PC13:Input Floating Mode
	..................
	...............
	//Configure GPIO Pins (LED)=PA5:Output Push Pull 2 MHZ
	..........
	..........

	
 while (1)
  {		
		//Test Push Button
 		//Read Oush Button State (0=Pressed, 1=Released)
		EtatBouton=GPIO_TestPin(GPIOC,GPIO_PIN_13);
		
	if (EtatBouton==0)  //If Pressed, Led ON	
	GPIO_SetPin(GPIOA, GPIO_PIN_5);
	else //Released, Led OFF
	GPIO_ResetPin(GPIOA, GPIO_PIN_5);				
}
	}
