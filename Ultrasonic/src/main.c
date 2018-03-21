#include "stm32f10x.h"

void us_delay();
uint32_t a=0;
int bit;

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

	//GPIO Pins
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_1);
	GPIOA -> CRL |= (GPIO_CRL_MODE0_0);
	GPIOA -> CRL |= (GPIO_CRL_MODE0_1);//OUTPUT(trig)

	GPIOB -> CRH &= ~(GPIO_CRH_CNF10_0);
	GPIOB -> CRH |= (GPIO_CRH_CNF10_1);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE10_0);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE10_1);//input(echo)

	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_1);
	GPIOA -> CRL |= (GPIO_CRL_MODE3_0);
	GPIOA -> CRL |= (GPIO_CRL_MODE3_1);//OUTPUT(trig)

	while(1)
	{
		GPIOA -> BSRR |= GPIO_BSRR_BR0;
		GPIOA -> BSRR |= GPIO_BSRR_BS3;
		us_delay(100);
		GPIOA -> BRR |= GPIO_BRR_BR3;

		//bit = (GPIOB -> IDR)&(0x0000);

		while(!((GPIOB -> IDR)&(1<<10)))
		{}
		//a=a+1;
		//us_delay(250);
		//GPIOA -> BSRR |= GPIO_BSRR_BS0;
		while(((GPIOB -> IDR)&(1<<10)))
		{
			a++;
			//GPIOA -> BSRR |= GPIO_BSRR_BS0;
		}

//		GPIOA -> BSRR |= GPIO_BSRR_BS0;
//		while(1)
//		{}

		if(a<=15000)
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS0;
			us_delay(50000);
			GPIOA -> BSRR |= GPIO_BSRR_BS0;
		}
		//else
			//GPIOA -> BSRR |= GPIO_BSRR_BS0;
		a=0;
	}
}

void us_delay(uint32_t j)
{
	for(uint32_t i=0;i<=(8*j);i++)
	{}
}
