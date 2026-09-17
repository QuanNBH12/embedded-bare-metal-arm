// Where is the led connected?
// Port: A
// PIN: 5

#define PERIPH_BASE				(0x40000000UL) //Base địa chỉ thiết bị ngoại vi

#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000U)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1ENR_OFFSET			(0x30UL)
#define RCC_AHB1ENR				(*(volatile unsigned int*) (RCC_BASE + AHB1ENR_OFFSET))

#define MODER_OFFSET			(0x00UL)
#define GPIOA_MODER				(*(volatile unsigned int*) (GPIOA_BASE + MODER_OFFSET))

#define ORD_OFFSET				(0x14UL)
#define GPIOA_ODR				(*(volatile unsigned int*) (GPIOA_BASE + ORD_OFFSET))

#define GPIOAEN					(1U << 0)

#define PIN5					(1U << 5)
#define LED_PIN					(PIN5)

/* |= (1U << 10) //Set bit 10 to 1
 * &=~(1U << 11) //Set bit 11 to 0
 * */

int main(void){
	/*1. Enable clock access to GPIOA*/
	RCC_AHB1ENR |= GPIOAEN;
	/*2. Set PA5 as output pin*/
	GPIOA_MODER |= (1U << 10);
	GPIOA_MODER &= ~(1U << 11);

	while (1){
		/*3. Set PA5 high*/
		//GPIOA_ODR |= LED_PIN;

		/*4. On off led*/
		GPIOA_ODR ^= LED_PIN;

		for (int i = 0; i < 100000; i++){}
	}
}


