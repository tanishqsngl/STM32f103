#include "stm32f10x.h"

int main(void)
{
	//For PWM
	uint32_t a = 0;
	uint32_t pAddr = 0x4001244C;
	volatile uint16_t mAddr[32];
	//int ArraySize = 32;
	uint32_t y = 0;
	uint32_t *b = 0;
	//int ArraySize = 32;
	uint32_t x;
	//uint32_t *a;

	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;

	GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;
	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL |= GPIO_CRL_MODE2_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
	GPIOA -> CRL |= GPIO_CRL_CNF1_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOA -> CRL |= GPIO_CRL_CNF2_1;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE6_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE6_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF6_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF6_1);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE7_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE7_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF7_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF7_1);
	TIM2 -> CR2 |= TIM_CR2_MMS_0;
	TIM2 -> CR1 |= TIM_CR1_ARPE;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_0;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM2 -> CCER |= TIM_CCER_CC2E;
	TIM2 -> CCER |= TIM_CCER_CC2P;
	TIM2 -> CCER |= TIM_CCER_CC3E;
	TIM2 -> CCER |= TIM_CCER_CC3P;
	TIM2 -> ARR = 65535;
	TIM2 -> PSC = 1;
	TIM2 -> EGR |= TIM_EGR_UG;
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
	GPIOA -> ODR = 0x00;
	TIM2 -> CR1 |= TIM_CR1_CEN;

	  //For ADC
	RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1 -> CR2 &= ~(ADC_CR2_ALIGN);
	ADC1 -> CR2 |= ADC_CR2_DMA;
	//ADC1 -> SR |= ADC_SR_EOC;
	ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_0);
	ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_1);
	ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_2);
	ADC1 -> CR1 &= ~(ADC_CR1_DUALMOD_3);
	ADC1 -> CR1 |= ADC_CR1_SCAN;
	ADC1 -> CR2 |= ADC_CR2_CONT;
	ADC1 -> CR2 |= ADC_CR2_RSTCAL;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_0;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_1;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP6_2;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_0;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_1;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP7_2;
	ADC1 -> SQR1 |= (ADC_SQR1_L_0);
	ADC1 -> SQR1 &= ~(ADC_SQR1_L_1);
	ADC1 -> SQR1 &= ~(ADC_SQR1_L_2);
	ADC1 -> SQR1 &= ~(ADC_SQR1_L_3);
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_0);
	ADC1 -> SQR3 |= ADC_SQR3_SQ1_1;
	ADC1 -> SQR3 |= ADC_SQR3_SQ1_2;
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_3);
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_4);
	ADC1 -> SQR3 |= (ADC_SQR3_SQ2_0);
	ADC1 -> SQR3 |= ADC_SQR3_SQ2_1;
	ADC1 -> SQR3 |= ADC_SQR3_SQ2_2;
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ2_3);
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ2_4);
	ADC1 -> CR2 |= ADC_CR2_EXTSEL_0;
	ADC1 -> CR2 |= ADC_CR2_EXTSEL_1;
	ADC1 -> CR2 |= ADC_CR2_EXTSEL_2;
	ADC1 -> CR2 |= ADC_CR2_EXTTRIG;
  	ADC1 -> CR2 |= ADC_CR2_ADON;
  	ADC1 -> CR2 |= ADC_CR2_CAL;

  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_EN);
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_MEM2MEM);
  	DMA1_Channel1 -> CCR |= DMA_CCR1_PL_0;
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_PL_1);
  	DMA1_Channel1 -> CCR |= DMA_CCR1_MSIZE_0;
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_MSIZE_1);
  	DMA1_Channel1 -> CCR |= DMA_CCR1_PSIZE_0;
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_PSIZE_1);
  	DMA1_Channel1 -> CCR |= DMA_CCR1_MINC;
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_PINC);
  	DMA1_Channel1 -> CCR |= (DMA_CCR1_CIRC);
  	//DMA1_Channel1 -> CCR |= DMA_CCR1_TCIE;
  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_DIR);
  	//DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
  	//*a = ADC1 -> DR;
  	DMA1_Channel1 -> CPAR = 0x4001244C;
  	DMA1_Channel1 -> CMAR = mAddr;
  	//while((DMA1 -> ISR & (1<<1)));
  	//ADC1 -> CR2 |= ADC_CR2_ADON;
  	//ADC1 -> CR2 |= ADC_CR2_CAL;

  	while (1)
    	{
	  	//GPIOA -> BSRR |= GPIO_BSRR_BS3;
	  	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_EN);
	  	DMA1_Channel1 -> CNDTR = 16;
	  	ADC1 -> CR2 |= ADC_CR2_ADON;
	 	ADC1 -> CR2 |= ADC_CR2_SWSTART;
	  	DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
	  	while(!(ADC1 -> SR & (1<<1)));
	  	x = mAddr[0];
	  	y = mAddr[1];
	  	//while((DMA1 -> ISR & (1<<1)))
	  	//{
			//  GPIOA -> BSRR |= GPIO_BSRR_BS3;
	  	//}
	  	a = ADC1 -> DR;
	  	TIM2 -> CCR3 = y;
	  	TIM2 -> CCR2 = x;
	  	//GPIOA -> BSRR |= GPIO_BSRR_BS3;
    	}
}
