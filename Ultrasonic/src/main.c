#include "stm32f10x.h"

void us_delay();
uint32_t a=0;
uint32_t b=0;
int bit;

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

	//GPIO Pins
	GPIOB -> CRL &= ~(GPIO_CRL_CNF6_0);
	GPIOB -> CRL &= ~(GPIO_CRL_CNF6_1);
	GPIOB -> CRL |= (GPIO_CRL_MODE6_0);
	GPIOB -> CRL |= (GPIO_CRL_MODE6_1);//OUTPUT(trig)

	GPIOB -> CRL &= ~(GPIO_CRL_CNF7_0);
	GPIOB -> CRL |= (GPIO_CRL_CNF7_1);
	GPIOB -> CRL &= ~(GPIO_CRL_MODE7_0);
	GPIOB -> CRL &= ~(GPIO_CRL_MODE7_1);//input(echo)

	GPIOB -> CRH &= ~(GPIO_CRH_CNF8_0);
	GPIOB -> CRH &= ~(GPIO_CRH_CNF8_1);
	GPIOB -> CRH |= (GPIO_CRH_MODE8_0);
	GPIOB -> CRH |= (GPIO_CRH_MODE8_1);//OUTPUT(trig)

	GPIOB -> CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOB -> CRH |= (GPIO_CRH_CNF9_1);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE9_0);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE9_1);//input(echo)

	while(1)
	{
		GPIOB -> BSRR |= GPIO_BSRR_BS6;
		us_delay(100);
		GPIOB -> BRR |= GPIO_BRR_BR6;

		while(!((GPIOB -> IDR)&(1<<7)))
		{}

		while(((GPIOB -> IDR)&(1<<7)))
		{
			a++;
		}

		if(a<=15000)
		{
		}
		a=0;

		GPIOB -> BSRR |= GPIO_BSRR_BS8;
		us_delay(100);
		GPIOB -> BRR |= GPIO_BRR_BR8;

		while(!((GPIOB -> IDR)&(1<<9)))
		{}

		while(((GPIOB -> IDR)&(1<<9)))
		{
			b++;
		}

		if(b<=15000)
		{
		}
		b=0;
	}
}

void us_delay(uint32_t j)
{
	for(uint32_t i=0;i<=(8*j);i++)
	{}
}
