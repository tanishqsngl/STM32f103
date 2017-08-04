#include "stm32f10x.h"

int main(void)
{
	volatile uint16_t mAddr[10];
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t x1 = 0;
	uint8_t y1 = 0;

	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_1);
	RCC -> CFGR |= RCC_CFGR_PPRE2_2;
	//RCC -> AHBENR |= RCC_AHBENR_DMA1EN;//Channel 5
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

	GPIOA -> CRL |= GPIO_CRL_MODE1_0;
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;
	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL |= GPIO_CRL_MODE2_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);
    GPIOA -> CRL |= (GPIO_CRL_CNF1_1);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
    GPIOA -> CRL |= (GPIO_CRL_CNF2_1);
    GPIOA -> CRL |= GPIO_CRL_MODE0_0;
    GPIOA -> CRL |= GPIO_CRL_MODE0_1;
    GPIOA -> CRL |= GPIO_CRL_MODE3_0;
    GPIOA -> CRL |= GPIO_CRL_MODE3_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
    GPIOA -> CRL |= (GPIO_CRL_CNF0_1);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
    GPIOA -> CRL |= (GPIO_CRL_CNF3_1);
	GPIOA -> CRH |= (GPIO_CRH_MODE9_0);
	GPIOA -> CRH |= GPIO_CRH_MODE9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOA -> CRH |= GPIO_CRH_CNF9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_1);
	GPIOA -> CRH |= (GPIO_CRH_CNF10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF10_1);

	//UART
	//dr address = 0x40013804
	USART1 -> BRR = 0xEA6;//9600 EA6 753
	USART1 -> CR1 &= ~(USART_CR1_M);//8 data bits
	//USART1 -> CR1 |= (USART_CR1_PCE);//even parity, parity on
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	//USART1 -> CR1 |= USART_CR1_TE;
	USART1 -> CR1 |= USART_CR1_RE;
	//USART1 -> CR1 |= USART_CR1_TCIE;
	USART1 -> CR1 |= USART_CR1_IDLEIE;
	USART1 -> CR3 |= USART_CR3_DMAR;
	USART1 -> CR3 &= ~(USART_CR3_RTSE);

	//DMA
	/*DMA1_Channel5 -> CCR &= ~(DMA_CCR1_EN);
	DMA1_Channel5 -> CCR |= (DMA_CCR1_MEM2MEM);
	DMA1_Channel5 -> CCR |= DMA_CCR1_PL_0;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PL_1);
	DMA1_Channel5 -> CCR |= DMA_CCR1_MSIZE_0;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_MSIZE_1);
	DMA1_Channel5 -> CCR |= DMA_CCR1_PSIZE_0;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PSIZE_1);
	DMA1_Channel5 -> CCR |= DMA_CCR1_MINC;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PINC);
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_CIRC);
	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_DIR);
	DMA1_Channel5 -> CPAR = 0x40013804;
	DMA1_Channel5 -> CMAR = mAddr;*/

	//PWM
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
	TIM2 -> ARR = 2047;
	TIM2 -> PSC = 0;
	TIM2 -> EGR |= TIM_EGR_UG;
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
	GPIOA -> ODR = 0x00;
	TIM2 -> CR1 |= TIM_CR1_CEN;
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
	TIM2 -> CCR3 = 0;

	while(1)
	{
		//DMA1_Channel5 -> CCR &= ~(DMA_CCR1_EN);
		//DMA1_Channel5 -> CNDTR = 256;
		//USART1 -> CR1 |= USART_CR1_UE;
		//DMA1_Channel5 -> CCR |= DMA_CCR1_EN;
		USART1 -> CR1 |= USART_CR1_UE;
		TIM2 -> CR1 |= TIM_CR1_CEN;
		while(!(USART1 -> SR & (1<<5)));
		a = USART1 -> DR;
		//while(!(USART1 -> SR & (1<<5)));

		if(a == 97)
		{
			//while(!(USART1 -> SR & (1<<5)));
			while(!(USART1 -> SR & (1<<5)));
			x = USART1 -> DR;
			x = x - 48;
			x1 = x*10 + x1;
			while(!(USART1 -> SR & (1<<5)));
			x = USART1 -> DR;
			x = x - 48;
			x1 = x*10 + x1;
			while(!(USART1 -> SR & (1<<5)));
			x = USART1 -> DR;
			x = x - 48;
			x1 = x*10 + x1;
			while(!(USART1 -> SR & (1<<5)));
			x = USART1 -> DR;
			x = x - 48;
			x1 = x*10 + x1;
			TIM2 -> CCR1 = x1;
			x1=0;
			while(!(USART1 -> SR & (1<<5)));
			y = USART1 -> DR;
			y = y - 48;
			y1 = y*10 + y1;
			while(!(USART1 -> SR & (1<<5)));
			y = USART1 -> DR;
			y = y - 48;
			y1 = y*10 + y1;
			while(!(USART1 -> SR & (1<<5)));
			y = USART1 -> DR;
			y = y - 48;
			y1 = y*10 + y1;
			while(!(USART1 -> SR & (1<<5)));
			y = USART1 -> DR;
			y = y - 48;
			y1 = y*10 + y1;
			TIM2 -> CCR2 = y1;
			y1=0;
		  }
	}
}
