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
	RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0);
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
