#include <stdint.h>


#define   Reg_Enable_RCC     (uint32_t*) ......... // adresse du registre assurant l'activation des horloges (RCC) des ports A et C
#define   Reg_Config_Led     (uint32_t*) ......... // adresse du registre de configuration du Port A (Leds)
#define   Reg_BSRR_Led	     (uint32_t*) ......... // adresses du registre permettant la mise � 1 des bits du port A
#define   Reg_BRR_Led	     (uint32_t*) ......... // adresses du registre permettant la mise � 0 des bits du port A

#define   Reg_Config_Bouton  (uint32_t*) ..........// adresse du registre de configuration du port C (reli� au bouton: PC13)
#define   Reg_Bouton         (uint32_t*) ........... //adresse du registre en entr�e (IDR) du port C


 int etat_bouton; // variable permettant de lire l'etat du bouton

main ()
{


 
 // activer les horloges des ports reli�s aux leds et au bouton
 *Reg_Enable_RCC  = ........;

 // Configurer les bits reli�s aux leds
 *Reg_Config_Led = .......;
 
 // configurer le bit reli� au bouton
 *Reg_Config_Bouton = ........; // Input Floating
 


//Testet Bouton et allumer si appuy� sinon �teindre

while (1)
{
  etat_bouton = .....................; // lire l'etat du bit reli� au bouton (bit PA0)
  
if (etat_bouton == 0x0001) // si appui

{
 *Reg_BSRR_Led = .......;// allumer leds

}
else //sinon

{
  // Eteindre les deux leds.
 *Reg_BRR_Led = ......; 

   }
}
}