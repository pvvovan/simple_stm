#include "stm32f3xx.h"
#include "main.h"

int g_var = 10;
int g_ver2;
const int g_var3 = 4;

static void gpio_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN ; 	// on
	__IO uint32_t tmpreg = RCC->AHBENR & (~RCC_AHBENR_GPIOAEN);
	(void)tmpreg;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;  	// 0100 0000 0000 we put that value into moder
}

static void clock_init(void)
{
	/* HSE */
	RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0); // wait until HSE is ready
	RCC->CFGR |= RCC_CFGR_SW_HSE; // 01: HSE selected as system clock
	while ((RCC->CFGR & RCC_CFGR_SWS_HSE) == 0); // wait until HSE selected as system clock

	/* FLASH */
	FLASH->ACR|= FLASH_ACR_PRFTBE;		// enabling FLASH prefatch buffer
	FLASH->ACR &= ~FLASH_ACR_LATENCY;	// set all bits to 0 (to ensure)
	FLASH->ACR|= FLASH_ACR_LATENCY_2;	// Two wait sates, if 48 < HCLK ≤ 72 MHz

	/* PLL */
	RCC->CFGR |= RCC_CFGR_PLLMUL9; // 0111: PLL input clock x 9
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV; // 10: HSE used as PREDIV1 entry
	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0); // wait until PLL is ready
	RCC->CFGR |= RCC_CFGR_SW_PLL; // 10: PLL selected as system clock
	while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0); // wait until PLL selected as system clock
}

static void mydelay(void)
{
	for (volatile long i = 0; i < 1000000; i++);
}

int main(void)
{
	clock_init();
	gpio_init();

	volatile float a = 0.1f;
	while(1) {
		a += 0.1f;
		mydelay();
		GPIOA->ODR ^= GPIO_ODR_5;
	}

	return 0;
}
