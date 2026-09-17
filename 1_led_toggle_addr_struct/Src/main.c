// Where is the led connected?
// Port: A
// PIN: 5

#include <stdint.h>

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

#define __IO					volatile

//typedef struct
//{
//    __IO uint32_t CR;         /*!< RCC clock control register,              Address offset: 0x00 */
//    __IO uint32_t PLLCFGR;    /*!< RCC PLL configuration register,          Address offset: 0x04 */
//    __IO uint32_t CFGR;       /*!< RCC clock configuration register,        Address offset: 0x08 */
//    __IO uint32_t CIR;        /*!< RCC clock interrupt register,             Address offset: 0x0C */
//    __IO uint32_t AHB1RSTR;   /*!< RCC AHB1 peripheral reset register,      Address offset: 0x10 */
//    __IO uint32_t AHB2RSTR;   /*!< RCC AHB2 peripheral reset register,      Address offset: 0x14 */
//    uint32_t      RESERVED0[2]; /*!< Reserved,                                Address offset: 0x18-0x1C */
//    __IO uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,      Address offset: 0x20 */
//    __IO uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,      Address offset: 0x24 */
//    uint32_t      RESERVED1[2]; /*!< Reserved,                                Address offset: 0x28-0x2C */
//    __IO uint32_t AHB1ENR;    /*!< RCC AHB1 peripheral clock enable,       Address offset: 0x30 */
//    __IO uint32_t AHB2ENR;    /*!< RCC AHB2 peripheral clock enable,       Address offset: 0x34 */
//    uint32_t      RESERVED2[2]; /*!< Reserved,                                Address offset: 0x38-0x3C */
//    __IO uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable,       Address offset: 0x40 */
//    __IO uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable,       Address offset: 0x44 */
//    uint32_t      RESERVED3[2]; /*!< Reserved,                                Address offset: 0x48-0x4C */
//    __IO uint32_t AHB1LPENR;  /*!< RCC AHB1 peripheral clock enable in low-power mode,
//                                                       Address offset: 0x50 */
//    __IO uint32_t AHB2LPENR;  /*!< RCC AHB2 peripheral clock enable in low-power mode,
//                                                       Address offset: 0x54 */
//    uint32_t      RESERVED4[2]; /*!< Reserved,                                Address offset: 0x58-0x5C */
//    __IO uint32_t APB1LPENR;  /*!< RCC APB1 peripheral clock enable in low-power mode,
//                                                       Address offset: 0x60 */
//    __IO uint32_t APB2LPENR;  /*!< RCC APB2 peripheral clock enable in low-power mode,
//                                                       Address offset: 0x64 */
//    uint32_t      RESERVED5[2]; /*!< Reserved,                                Address offset: 0x68-0x6C */
//    __IO uint32_t BDCR;       /*!< RCC Backup domain control register,      Address offset: 0x70 */
//    __IO uint32_t CSR;        /*!< RCC clock control & status register,     Address offset: 0x74 */
//    uint32_t      RESERVED6[2]; /*!< Reserved,                                Address offset: 0x78-0x7C */
//    __IO uint32_t SSCGR;      /*!< RCC spread spectrum clock generation,    Address offset: 0x80 */
//    __IO uint32_t PLLI2SCFGR; /*!< RCC PLLI2S configuration register,       Address offset: 0x84 */
//    __IO uint32_t PLLSAICFGR; /*!< RCC PLLSAI configuration register,       Address offset: 0x88 */
//    __IO uint32_t DCKCFGR;    /*!< RCC dedicated clocks configuration,      Address offset: 0x8C */
//} RCC_TypeDef;
//
//
//typedef struct {
//    __IO uint32_t MODER;   /*!< GPIO port mode register,                  Address offset: 0x00 */
//    __IO uint32_t OTYPER;  /*!< GPIO port output type register,           Address offset: 0x04 */
//    __IO uint32_t OSPEEDR; /*!< GPIO port output speed register,          Address offset: 0x08 */
//    __IO uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register,     Address offset: 0x0C */
//    __IO uint32_t IDR;     /*!< GPIO port input data register,            Address offset: 0x10 */
//    __IO uint32_t ODR;     /*!< GPIO port output data register,           Address offset: 0x14 */
//    __IO uint32_t BSRR;    /*!< GPIO port bit set/reset register,         Address offset: 0x18 */
//    __IO uint32_t LCKR;    /*!< GPIO port configuration lock register,   Address offset: 0x1C */
//    __IO uint32_t AFR[2];  /*!< GPIO alternate function registers,       Address offset: 0x20-0x24 */
//} GPIO_TypeDef;

typedef struct {
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;	/*!< RCC AHB1 peripheral clock enable,       Address offset: 0x30 */
} RCC_TypeDef;


typedef struct {
	volatile uint32_t MODER;	/*!< GPIO port mode register,                  Address offset: 0x00 */
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;		/*!< GPIO port output data register,           Address offset: 0x14 */
} GPIO_TypeDef;

#define RCC						((RCC_TypeDef*) RCC_BASE)
#define GPIOA					((GPIO_TypeDef*) GPIOA_BASE)

int main(void){
	/*1. Enable clock access to GPIOA*/
	//RCC_AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOAEN;

	/*2. Set PA5 as output pin*/
	//GPIOA_MODER |= (1U << 10);
	//GPIOA_MODER &= ~(1U << 11);

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1){
		/*3. Set PA5 high*/
		//GPIOA_ODR |= LED_PIN;

		/*4. On off led*/
		GPIOA->ODR ^= LED_PIN;

		for (int i = 0; i < 100000; i++){}
	}
}


