#include "stm32f4xx.h"

#define GPIOAEN			(1U << 0)
#define GPIOCEN			(1U << 2)


#define PIN5			(1U << 5)
#define PIN13			(1U << 13)


#define LED_PIN			(PIN5)
#define BTN_PIN			(PIN13)


int main(void){
	/*1.Enable RCC clock access for GPIOA and GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*2.Set PA5 as output pin and set PC13 as input pin*/
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	while (1){
		/*3. If button pressed*/
		if (!(GPIOC->IDR & BTN_PIN)){
			/*4. Set bit BS5(BSRR bit 5) = 1 -> Turn ON led*/
			GPIOA->BSRR = LED_PIN; //GPIOA->BSRR = (1U << 5);
		} else {
			/*5. Set bit BR5(BSRR bit 21) = 1 -> Turn OFF (Reset) led*/
			GPIOA->BSRR = (1U << 21);
		}
	}
}

