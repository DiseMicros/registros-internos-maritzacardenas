#include <stdint.h>
#include "MK64F12.h"

void delay(uint16_t delay);

int main(void){

	uint32_t input = 0, input_2 = 0;
	uint8_t  sw2_state = 0, sw3_state = 0;

	/**Activating the GPIOB and GPIOE clock gating*/
	SIM->SCGC5 = 0x0400;
	SIM->SCGC5 = SIM->SCGC5 | 0x2000 | (1 << 11) | (1 << 9);

	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	PORTB->PCR[21] = 0x00000100;
	PORTB->PCR[22] = 0x00000100;
	PORTE->PCR[26] = 0x00000100;

	PORTC->PCR[10] = 0x00000100;
	PORTA->PCR[4] = 0x00000100;


	GPIOB->PCOR = (1 << 21) | (1 << 22);
	GPIOE->PCOR = 1 << 26;

	GPIOC->PDDR &= !(1 << 10);//set pin 6 PORTC as input
	GPIOA->PDDR &= !(1 << 4);//set pin 4 PRTA as input
	/*GPIOB->PDOR = 0xFFFFFFF;*/

	/**Configures GPIOB pin21 as output*/
	GPIOB->PDDR = (1 << 21);
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= (1 << 22);
	/**Configures GPIOE pin26 as output*/
	GPIOE->PDDR = (1 << 26);

	GPIOC->PDDR &= !(1 << 10);
	GPIOA->PDDR &= !(1 << 04);

	sw2_state = 0;
	sw3_state = 0;

    while(1) {

    	input = GPIOC->PDIR;
    	input_2 = GPIOA->PDIR;
    	input = input & (1 << 10);
    	input_2 = input_2 & (1 << 04);

    	if(0x00 == input){
            delay(10000); // Esperar un tiempo para evitar el rebote

            if(0x00 == input) { // Verificar nuevamente el estado del SW2

                // Implementar la secuencia de cambio de color para SW2
                if (sw2_state == 0){
                    // Amarillo
                	GPIOB->PSOR = 0x00200000;/**Blue led on*/
                	GPIOE->PCOR = 0x04000000;/**Green led on**/
                	GPIOB->PCOR = 0x00400000;/**Red led off*/
                } else if (sw2_state == 1){
                    // Rojo
                    GPIOB->PSOR = 0x00200000;/**Blue led off*/
                    GPIOE->PSOR = 0x04000000;/**Green led off**/
                    GPIOB->PCOR = 0x00400000;/**Red led on*/
                } else if (sw2_state == 2){
                    // Morado
                    GPIOB->PCOR = 0x00200000;/**Blue led on*/
                    GPIOE->PSOR = 0x04000000;/**Green led off**/
                    GPIOB->PCOR = 0x00400000;/**Red led on*/
                } else if (sw2_state == 3){
                    // Azul
                    GPIOB->PSOR = 0x00400000;/**Red led off*/
                    GPIOE->PSOR = 0x04000000;/**Green led off**/
                    GPIOB->PCOR = 0x00200000;/**Blue led on*/
                } else if (sw2_state == 4){
                    // Verde
                    GPIOB->PSOR = 0x00400000;/**Red led off*/
                    GPIOB->PSOR = 0x00200000;/**Blue led off*/
                    GPIOE->PCOR = 0x04000000;/**Green led on**/
                }

                for(int i = 0; i < 100; i++)
                	delay(5000000);

                sw2_state = (sw2_state + 1) % 5; // Incrementar el estado de SW2
            }
        }

    	if ( 0x00 == input_2){
            delay(10000); // Esperar un tiempo para evitar el rebote

            if (0x00 == input_2){ // Verificar nuevamente el estado del SW3

                // Implementar la secuencia de cambio de color para SW3
                if (sw3_state == 0){
                	// Verde
                	GPIOB->PSOR = 0x00400000;/**Red led off*/
                	GPIOB->PSOR = 0x00200000;/**Blue led off*/
                	GPIOE->PCOR = 0x04000000;/**Green led on**/

                } else if (sw3_state == 1){
                	 // Azul
                	GPIOB->PSOR = 0x00400000;/**Red led off*/
                	GPIOE->PSOR = 0x04000000;/**Green led off**/
                	GPIOB->PCOR = 0x00200000;/**Blue led on*/

                } else if (sw3_state == 2){
                    // Morado
                    GPIOB->PCOR = 0x00200000;/**Blue led on*/
                    GPIOE->PSOR = 0x04000000;/**Green led off**/
                    GPIOB->PCOR = 0x00400000;/**Red led on*/
                } else if (sw3_state == 3) {
                	// Rojo
                	GPIOB->PSOR = 0x00200000;/**Blue led off*/
                	GPIOE->PSOR = 0x04000000;/**Green led off**/
                	GPIOB->PCOR = 0x00400000;/**Red led on*/
                } else if (sw3_state == 4){
                    // Amarillo
                    GPIOB->PSOR = 0x00200000;/**Blue led on*/
                    GPIOE->PCOR = 0x04000000;/**Green led on**/
                    GPIOB->PCOR = 0x00400000;/**Red led off*/
                }

                for(int i = 0; i < 100; i++)
                	delay(5000000);

                sw3_state = (sw3_state + 1) % 5; // Incrementar el estado de SW3
            }
        }

    }
    return 0 ;
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint16_t delay)
{
	volatile uint16_t counter;

	for(counter=delay; counter > 0; counter--)
	{
		__asm("nop");
	}
}
