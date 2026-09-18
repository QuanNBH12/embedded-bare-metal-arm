#include "stm32f4xx.h"

#define GPIOAEN			(1U << 0)
#define PIN5			(1U << 5)
#define LED_PIN			(PIN5)


int main(void){
	/*1.Enable RCC clock*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1){
		/*3. Set bit BS5(BSRR bit 5) = 1 -> ON*/
		GPIOA->BSRR = LED_PIN; //GPIOA->BSRR = (1U << 5);
		for(int i = 0; i < 500000; i++);

		/*3. Set bit BR5(BSRR bit 21) = 1 -> OFF (Reset)*/
		GPIOA->BSRR = (1U << 21);
		for(int i = 0; i < 500000; i++);
	}
}

