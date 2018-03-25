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

	GPIOB -> CRH &= ~(GPIO_CRH_CNF12_0);
	GPIOB -> CRH |= (GPIO_CRH_CNF12_1);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE12_0);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE12_1);//input(echo)

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

		while(!((GPIOB -> IDR)&(1<<12)))
		{}
		//a=a+1;
		//us_delay(250);
		//GPIOA -> BSRR |= GPIO_BSRR_BS0;
		while(((GPIOB -> IDR)&(1<<12)))
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

void ultrasonic(uint16_t thr)
{
	uint32_t a=0, flag1=0, a1=0, flag2=0;

	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	us_delay(100);
	GPIOA -> BRR |= GPIO_BRR_BR0;

	while(!((GPIOB -> IDR)&(1<<12)))
	{}

	while(((GPIOB -> IDR)&(1<<12)))
	{
		a++;
	}

	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	us_delay(100);
	GPIOA -> BRR |= GPIO_BRR_BR1;

//	while(!((GPIOB -> IDR)&(1<<13)))
//	{}
//
//	while((GPIOB -> IDR)&(1<<13))
//	{
//		a1++;
//	}
//
	if(a<=thr)
	{
		flag1=1;
	}

	else if(a1<=thr)
	{
		flag2=1;
	}

	if(flag1==1)
	{
		//stop
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//move back
		motorCode(32768,0,22,2,'c');
		us_delay(50000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//rotate left
		motorCode(32768,32768,22,1,'c');
		us_delay(50000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//forward
		motorCode(32768,65535,22,1,'c');
		us_delay(70000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//stop
//		motorCode(32768,32768,13,2,'c');
	}

	else if(flag2==1)
	{
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//move back
		motorCode(32768,0,22,2,'c');
		us_delay(50000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//rotate left
		motorCode(32768,32768,22,1,'c');
		us_delay(50000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
		//forward
		motorCode(32768,65535,22,1,'c');
		us_delay(70000);
		motorCode(32768,32768,13,2,'c');
		us_delay(20000);
	}
}
