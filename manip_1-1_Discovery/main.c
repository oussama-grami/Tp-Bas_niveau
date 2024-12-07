#include <stdint.h>


/*#define   Reg_Enable_RCC     (uint32_t*) ......... // adresse du registre assurant l'activation des horloges (RCC) des ports A et C
#define   Reg_Config_Led     (uint32_t*) ......... // adresse du registre de configuration du Port C (relié aux leds)
#define   Reg_BSRR_Led	     (uint32_t*) ......... // adresses du registre permettant la mise à 1 des bits du port C
#define   Reg_BRR_Led	     (uint32_t*) ......... // adresses du registre permettant la mise à 0 des bits du port C

#define   Reg_Config_Bouton  (uint32_t*) ..........// adresse du registre de configuration du port A (relié au bouton)
#define   Reg_Bouton         (uint32_t*) ........... //adresse du registre en entrée (IDR) du port A*/

#define RCC_APB2ENR  (uint32_t*) 0x40021018
#define GPIO_A_CRL (uint32_t*) 0x40010800
#define GPIO_C_CRH (uint32_t*) 0x40011004
#define GPIO_A_IDR (uint32_t*) 0x40010808
#define GPIO_C_BSRR (uint32_t*) 0x40011010
#define GPIO_C_BRR (uint32_t*) 0x40011014
uint32_t pa0;

 int etat_bouton; // variable permettant de lire l'etat du bouton

int main ()
{




*RCC_APB2ENR = 0x05u <<2;
*GPIO_A_CRL &=~0x0Fu;
*GPIO_A_CRL |= 0x01u <<2;
*GPIO_C_CRH &=~ 0xFFu;
*GPIO_C_CRH |= 0x22u;
while(1){
	pa0 = *GPIO_A_IDR & 0x01u ;
	if(pa0){
		*GPIO_C_BSRR = 0x03u <<8;
	}
	else{
		*GPIO_C_BRR = 0x03u <<8;
	}
}

 
 /*// activer les horloges des ports reliés aux leds et au bouton
 *Reg_Enable_RCC  = ........;

 // Configurer les bits reliés aux leds
 *Reg_Config_Led = .......;
 
 // configurer le bit relié au bouton
 *Reg_Config_Bouton = ........; // Input Floating
 


//Testet Bouton et allumer si appuyé sinon éteindre

while (1)
{
  etat_bouton = .....................; // lire l'etat du bit relié au bouton (bit PA0)
  
if (etat_bouton == 0x0001) // si appui

{
 *Reg_BSRR_Led = 0x0300;// allumer leds

}
else //sinon

{
  // Eteindre les deux leds.
 *Reg_BRR_Led = 0x0300; 

   }
}
*/
}