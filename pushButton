#include "stm32f10x.h"

int main(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPEEN;//enabling io on E

	GPIOE -> CRL |= GPIO_CRL_MODE0_1;//OUTPUT on E0
	GPIOE -> CRL |= GPIO_CRL_MODE0_0;
	GPIOE -> CRL &= ~(GPIO_CRL_CNF0_1);//mode
	GPIOE -> CRL |= GPIO_CRL_CNF0_0;


	GPIOE -> CRL |= ~(GPIO_CRL_MODE1_1);//INPUT on E1
	GPIOE -> CRL |= ~(GPIO_CRL_MODE1_0);
	GPIOE -> CRL &= ~(GPIO_CRL_CNF1_0);//mode
	GPIOE -> CRL |= GPIO_CRL_CNF1_1;

	while(1)
	{
		if(GPIOE -> IDR & GPIO_IDR_IDR1)
		{
			GPIOE -> BSRR |= GPIO_BSRR_BS0;
		}
		else
		{
			GPIOE -> BSRR |= GPIO_BSRR_BR0;
		}
	}
}
