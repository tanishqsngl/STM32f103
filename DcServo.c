#include "stm32f10x.h"

void Delay(int time)
{
	volatile int i,j;
	for (i=0;i<time;i++)
		j++;
}

int main(void)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	//RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	//RCC -> AHBENR |= RCC_AHBENR_DMA1EN;

	//For PWM
	GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;
	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL |= GPIO_CRL_MODE2_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
	GPIOA -> CRL |= GPIO_CRL_CNF1_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOA -> CRL |= GPIO_CRL_CNF2_1;
	GPIOA -> CRL |= GPIO_CRL_MODE0_0; //setting high speed (and) output
	GPIOA -> CRL |= GPIO_CRL_MODE0_1;
	GPIOA -> CRL |= GPIO_CRL_MODE3_0;
	GPIOA -> CRL |= GPIO_CRL_MODE3_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);//push pull
	GPIOA -> CRL |= GPIO_CRL_CNF0_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
	GPIOA -> CRL |= GPIO_CRL_CNF3_1;

	TIM2 -> CR2 |= TIM_CR2_MMS_0;
	TIM2 -> CR1 |= TIM_CR1_ARPE;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1PE;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_0;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC4M_0;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC4PE;
	TIM2 -> CCER |= TIM_CCER_CC1E;
	TIM2 -> CCER |= TIM_CCER_CC1P;
	TIM2 -> CCER |= TIM_CCER_CC2E;
	TIM2 -> CCER |= TIM_CCER_CC2P;
	TIM2 -> CCER |= TIM_CCER_CC3E;
	TIM2 -> CCER |= TIM_CCER_CC3P;
	TIM2 -> CCER |= TIM_CCER_CC4E;
	TIM2 -> CCER |= TIM_CCER_CC4P;
	TIM2 -> ARR = 2048;
	TIM2 -> PSC = 0;
	TIM2 -> EGR |= TIM_EGR_UG;
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
	TIM2 -> CR1 |= TIM_CR1_CEN;

	TIM2 -> CCR1 = 0;//FL
	TIM2 -> CCR2 = 0;//FR
	TIM2 -> CCR3 = 0;//BL
	TIM2 -> CCR4 = 0;//BR


  while (1)
    {
	  TIM2 -> CCR1 = 2048;//FL
	  TIM2 -> CCR2 = 2048;//FR
	  TIM2 -> CCR3 = 0;//BL
	  TIM2 -> CCR4 = 0;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 0;//FL
	  TIM2 -> CCR2 = 2048;//FR
	  TIM2 -> CCR3 = 0;//BL
	  TIM2 -> CCR4 = 0;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 0;//FL
	  TIM2 -> CCR2 = 2048;//FR
	  TIM2 -> CCR3 = 2048;//BL
	  TIM2 -> CCR4 = 0;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 0;//FL
	  TIM2 -> CCR2 = 0;//FR
	  TIM2 -> CCR3 = 2048;//BL
	  TIM2 -> CCR4 = 0;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 0;//FL
	  TIM2 -> CCR2 = 0;//FR
	  TIM2 -> CCR3 = 2048;//BL
	  TIM2 -> CCR4 = 2048;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 0;//FL
	  TIM2 -> CCR2 = 0;//FR
	  TIM2 -> CCR3 = 0;//BL
	  TIM2 -> CCR4 = 2048;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 2048;//FL
	  TIM2 -> CCR2 = 0;//FR
	  TIM2 -> CCR3 = 0;//BL
	  TIM2 -> CCR4 = 2048;//BR

	  Delay(2000);

	  TIM2 -> CCR1 = 2048;//FL
	  TIM2 -> CCR2 = 0;//FR
	  TIM2 -> CCR3 = 0;//BL
	  TIM2 -> CCR4 = 0;//BR

	  Delay(2000);
    }
}

















