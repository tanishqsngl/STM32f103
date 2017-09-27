#include "stm32f10x.h"

int main(void)
{
  	//For PWM
  	uint32_t a = 0;
  	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
  	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
  	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;

  GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
  GPIOA -> CRL |= GPIO_CRL_MODE1_1;
  GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
  GPIOA -> CRL |= GPIO_CRL_CNF1_1;
  GPIOA -> CRL &= ~(GPIO_CRL_MODE6_0);
  GPIOA -> CRL &= ~(GPIO_CRL_MODE6_1);
  GPIOA -> CRL &= ~(GPIO_CRL_CNF6_0);
  GPIOA -> CRL &= ~(GPIO_CRL_CNF6_1);
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

  RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
  ADC1 -> CR2 |= ADC_CR2_ALIGN;
  ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_0);
  ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_1);
  ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_2);
  ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_3);
  ADC1 -> CR2 |= ADC_CR2_CONT;
  ADC1 -> CR2 |= ADC_CR2_RSTCAL;
  ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_0;
  ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_1;
  ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_2;
  /*ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_0;
  ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_1;
  ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_2;*/
  ADC1 -> SQR1 |= (ADC_SQR1_L_0);
  ADC1 -> SQR1 &= ~(ADC_SQR1_L_1);
  ADC1 -> SQR1 &= ~(ADC_SQR1_L_2);
  ADC1 -> SQR1 &= ~(ADC_SQR1_L_3);
  ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_0);
  ADC1 -> SQR3 |= ADC_SQR3_SQ1_1;
  ADC1 -> SQR3 |= ADC_SQR3_SQ1_2;
  ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_3);
  ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_4);
  /*ADC1 -> SQR3 |= (ADC_SQR3_SQ1_0);
  ADC1 -> SQR3 |= ADC_SQR3_SQ1_1;
  ADC1 -> SQR3 |= ADC_SQR3_SQ1_2;
  ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_3);
  ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_4);*/
  ADC1 -> CR2 |= ADC_CR2_ADON;
  ADC1 -> CR2 |= ADC_CR2_CAL;

  while (1)
    {
	  ADC1 -> CR2 |= ADC_CR2_SWSTART;
	  a = ADC1 -> DR;
	  TIM2 -> CCR2 = a;
    }
}
