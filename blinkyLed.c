#include "stm32f10x.h"

void Delay(int time)
{
	volatile int i,j;
	for (i=0;i<time;i++)
		j++;
}

int main(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN; //enabling gpio port A

	GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;

	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_1);



  while (1)
    {
	  	  GPIOA -> BSRR |= GPIO_BSRR_BS1;//giving it high

	  	  Delay(2000000);

	  	  GPIOA -> BSRR |= GPIO_BSRR_BR1;//giving it low

	  	  Delay(2000000);
    }
}

















