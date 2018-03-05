#include "stm32f10x.h"

void ms_delay();

void us_delay();

void Delay();

int a=0;
int dist=0;

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> CR |= RCC_CR_HSION;

	//GPIO Pins
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_1);
	GPIOA -> CRL |= (GPIO_CRL_MODE0_0);
	GPIOA -> CRL |= (GPIO_CRL_MODE0_1);//OUTPUT(trig)

	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOA -> CRL |= GPIO_CRL_CNF1_1;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE1_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE1_1);//input(echo)

	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL |= GPIO_CRL_MODE2_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
    GPIOA -> CRL |= GPIO_CRL_CNF2_1;

	//PWM Pins
	TIM2 -> CR2 |= TIM_CR2_MMS_0;
	TIM2 -> CR1 |= TIM_CR1_ARPE;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM2 -> CCER |= TIM_CCER_CC3E;
	TIM2 -> CCER |= TIM_CCER_CC3P;
	TIM2 -> ARR = 800;
	TIM2 -> PSC = 0;
	TIM2 -> EGR |= TIM_EGR_UG;
	TIM2 -> CR1 |= TIM_CR1_CEN;

	while(1)
	{
		GPIOA -> BSRR |= GPIO_BSRR_BS0;
		Delay(3276);
		GPIOA -> BSRR |= GPIO_BSRR_BR0;
		//Delay(327680);

		while(!(GPIOA -> IDR & (1<<1)))
		{
			for(a=0;a<18079;a++);
			break;
		}

		a = a*14500;
		a = a/327680;

		TIM2 -> CCR3 = a;
	}
}

void ms_delay(int k)
{
	for(int i=0;i<k*333;i++)//327680 is a second
	{}
}

void us_delay(int j)
{
	for(int i=0;i<j*3;j++)
	{}
}
void Delay(int time)
{
	float i;
	for (i=0;i<time;i++);
}
