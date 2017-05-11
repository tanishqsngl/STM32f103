#include "stm32f10x.h"

int main(void)
{
  volatile uint32_t i = 0;
  RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;//enabling gpio port A
  RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;

  GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
  GPIOA -> CRL |= GPIO_CRL_MODE1_1;
  GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
  GPIOA -> CRL |= GPIO_CRL_CNF1_1;
  TIM2 -> CR2 |= TIM_CR2_MMS_2;
  TIM2 -> CR1 |= TIM_CR1_ARPE;
  TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2;
  TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_1;
  TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_0;
  TIM2 -> CCMR1 |= TIM_CCMR1_OC2PE;
  TIM2 -> CCER |= TIM_CCER_CC2E;
  TIM2 -> CCER |= TIM_CCER_CC2P;
  TIM2 -> ARR = 65535;
  TIM2 -> PSC = 1;
  TIM2 -> EGR |= TIM_EGR_UG;
  AFIO -> MAPR |= AFIO_MAPR_TIM2_REMAP_1;
  AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
  GPIOA -> ODR = 0x00;
  TIM2 -> CR1 |= TIM_CR1_CEN;

  while (1)
    {
		while(i<65535)
		{
	    	TIM2 -> CCR2 = i;
	    	for(int j=0;j<200000;j++);
	    	i+=100;
		}
    }
}
