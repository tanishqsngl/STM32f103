#include "stm32f10x.h"

uint32_t x2=0, y2=0;
uint8_t z2=0, w2=0, c2=0;
volatile uint32_t mAddr[32];

void emStop(void)
{
	int b = 0;
    TIM2 -> CR1 |= TIM_CR1_ARPE;
    TIM2 -> PSC = 7200;
    TIM2 -> ARR = 10000;
    TIM2 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART1 -> SR & (1<<5)))
	{
		TIM2 -> CR1 |= TIM_CR1_CEN;
		b = TIM2 -> CNT;
		if(b >= 1500)
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FL
			TIM3 -> CCR2 = 0;//FR
			TIM3 -> CCR1 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;
		}
	}
	TIM2 -> CNT = 0;
}

void emStop1(void)
{
	int b = 0;
    TIM2 -> CR1 |= TIM_CR1_ARPE;
    TIM2 -> PSC = 7200;
    TIM2 -> ARR = 10000;
    TIM2 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART2 -> SR & (1<<5)))
	{
		TIM2 -> CR1 |= TIM_CR1_CEN;
		b = TIM2 -> CNT;
		if(b >= 9500)
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FL
			TIM3 -> CCR2 = 0;//FR
			TIM3 -> CCR1 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;
		}
	}
	TIM2 -> CNT = 0;
}

void ADCSetup(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1 -> CR2 &= ~(ADC_CR2_ALIGN);
	ADC1 -> CR2 |= ADC_CR2_DMA;
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
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_1);
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_2);
	ADC1 -> SQR3 |= (ADC_SQR3_SQ1_3);
	ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_4);
	ADC1 -> SQR3 |= (ADC_SQR3_SQ2_0);
	ADC1 -> SQR3 |= ADC_SQR3_SQ2_1;
	ADC1 -> SQR3 |= ADC_SQR3_SQ2_2;
	ADC1 -> SQR3 |= (ADC_SQR3_SQ2_3);
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
	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_DIR);
	DMA1_Channel1 -> CPAR = 0x4001244C;
	DMA1_Channel1 -> CMAR = mAddr;
}

void timerSetup(void)
{
	//Wheel Motor
	TIM3 -> CR1 &= ~(TIM_CR1_ARPE);
	TIM3 -> CR1 &= ~(TIM_CR1_UDIS);
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3 -> CCMR2 &= ~(TIM_CCMR2_OC3M_1);
	TIM3 -> CCMR2 |= (TIM_CCMR2_OC3M_0);
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3 -> CCMR2 &= ~(TIM_CCMR2_OC4M_1);
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4PE;
	TIM3 -> CCER &= ~(TIM_CCER_CC3E);
	TIM3 -> CCER |= (TIM_CCER_CC3P);
	TIM3 -> CCER &= ~(TIM_CCER_CC4E);
	TIM3 -> CCER |= (TIM_CCER_CC4P);
	TIM3 -> DIER |= TIM_DIER_UIE;
	TIM3 -> ARR = 32768;
	TIM3 -> PSC = 0;
	TIM3 -> EGR |= TIM_EGR_UG;
	TIM3 -> CR1 &= ~(TIM_CR1_CEN);
	TIM3 -> CCR3 = 0;
	TIM3 -> CCR4 = 0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM3 -> CCMR1 &= ~(TIM_CCMR1_OC1M_1);
	TIM3 -> CCMR1 |= (TIM_CCMR1_OC1M_0);
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1PE;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM3 -> CCMR1 &= ~(TIM_CCMR1_OC2M_1);
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2PE;
	TIM3 -> CCER &= ~(TIM_CCER_CC1E);
	TIM3 -> CCER |= (TIM_CCER_CC1P);
	TIM3 -> CCER &= ~(TIM_CCER_CC2E);
	TIM3 -> CCER |= (TIM_CCER_CC2P);
}

void GPIOSetup(void)
{
	GPIOA -> CRL = 0xBB334B33;
	GPIOA -> CRH = 0x000004B0;//2 Empty(11 12)
	GPIOB -> CRL = 0x4B0000BB;//1 Empty(5) UART ~I2C
	GPIOB -> CRH = 0x33B00088;//3 Empty(10 11 12)
	GPIOC -> CRH = 0x33000000;//1 Empty(13)
}

void UARTSetup(void)
{
	//UART
	USART1 -> CR1 |= USART_CR1_UE;
	USART1 -> BRR = 0x271;
	USART1 -> CR1 &= ~(USART_CR1_M);
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	USART1 -> CR1 |= USART_CR1_IDLEIE;
	USART1 -> CR3 &= ~(USART_CR3_RTSE);
}

void UARTSetup1(void)
{
	//UART
	USART2 -> CR1 |= USART_CR1_UE;
	USART2 -> BRR = 0x271;
	USART2 -> CR1 &= ~(USART_CR1_M);
	USART2 -> CR1 |= USART_CR1_RXNEIE;
	USART2 -> CR1 |= USART_CR1_IDLEIE;
	USART2 -> CR3 &= ~(USART_CR3_RTSE);
}

uint16_t map(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e)
{
  return (a-b)*(e-d)/(c-b) + d;
}

void motorCode(uint16_t x, uint16_t y, uint16_t z, uint16_t w, uint16_t c1)
{
	TIM3 -> CR1 |= TIM_CR1_CEN;
	TIM3 -> CCER |= TIM_CCER_CC3E;
	TIM3 -> CCER |= TIM_CCER_CC4E;
	TIM3 -> CCER |= TIM_CCER_CC1E;
	TIM3 -> CCER |= TIM_CCER_CC2E;

	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_0;

	uint16_t max = 65535;
	uint16_t buffer = 32768;
	uint16_t buffer1 = buffer + 0.25*buffer; //39321
	uint16_t buffer2 = buffer - 0.25*buffer; //26214

	if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==2)//centre
	{
		TIM3 -> CCR4 = 0;//L
		TIM3 -> CCR3 = 0;//L
		TIM3 -> CCR2 = 0;//R
		TIM3 -> CCR1 = 0;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==1)//360 left
	{
		TIM3 -> CCR4 = (buffer*z)/25;//L
		TIM3 -> CCR3 = (buffer*z)/25;//L
		TIM3 -> CCR2 = (buffer*z)/25;//R
		TIM3 -> CCR1 = (buffer*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BS14;
		GPIOC -> BSRR |= GPIO_BSRR_BS15;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==3)//360 right
	{
		TIM3 -> CCR4 = (buffer*z)/25;//L
		TIM3 -> CCR3 = (buffer*z)/25;//L
		TIM3 -> CCR2 = (buffer*z)/25;//R
		TIM3 -> CCR1 = (buffer*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BS4;
		GPIOA -> BSRR |= GPIO_BSRR_BS5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}
	//2-Axis
	else if(x<=buffer1 && x>=buffer2 && y>=buffer1)//forward
	{
		TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
		TIM3 -> CCR3 = ((y-buffer)*z)/25;//L
		TIM3 -> CCR2 = ((y-buffer)*z)/25;//R
		TIM3 -> CCR1 = ((y-buffer)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}
	else if(x<=buffer1 && x>=buffer2 && y<=buffer2)//backward
	{
		TIM3 -> CCR4 = ((buffer-y)*z)/25;//L
		TIM3 -> CCR3 = ((buffer-y)*z)/25;//L
		TIM3 -> CCR2 = ((buffer-y)*z)/25;//R
		TIM3 -> CCR1 = ((buffer-y)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BS4;
		GPIOA -> BSRR |= GPIO_BSRR_BS5;
		GPIOC -> BSRR |= GPIO_BSRR_BS14;
		GPIOC -> BSRR |= GPIO_BSRR_BS15;
	}
	else if(y>buffer2 && y<buffer1 && x<buffer2)//Left
	{
		TIM3 -> CCR4 = 0;//FL
		TIM3 -> CCR3 = 0;//FL
		TIM3 -> CCR2 = ((buffer-x)*z)/25;//FR
		TIM3 -> CCR1 = ((buffer-x)*z)/25;//FR
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}
	else if(y>buffer2 && y<buffer1 && x>buffer1)//Right
	{
		TIM3 -> CCR4 = ((x-buffer)*z)/25;//FL
		TIM3 -> CCR3 = ((x-buffer)*z)/25;//FL
		TIM3 -> CCR2 = 0;//FR
		TIM3 -> CCR1 = 0;//FR
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}

	if(x>buffer1 && y>=buffer1)//Upper-Right
	{
		if(y>=x)//Right of F
		{
			x = map(x,buffer1,max,buffer1,buffer+0.5*buffer);
			x=y-x;
			//x=x-buffer;
			TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
			TIM3 -> CCR3 = ((y-buffer)*z)/25;//L
			TIM3 -> CCR2 = (x*z)/25;//R
			TIM3 -> CCR1 = (x*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;

		}
		else//Up of Right
		{
			y = map(y,buffer1,max,max,buffer+0.5*buffer);
			x = map(x,buffer1,max,buffer+0.5*buffer,max);
			if ((x-y)>=0)
			{
				y=x-y;
				TIM3 -> CCR4 = ((x-buffer)*z)/25;//L
				TIM3 -> CCR3 = ((x-buffer)*z)/25;//L
				TIM3 -> CCR2 = (y*z)/25;//R
				TIM3 -> CCR1 = (y*z)/25;//R
				GPIOA -> BSRR |= GPIO_BSRR_BR4;
				GPIOA -> BSRR |= GPIO_BSRR_BR5;
				GPIOC -> BSRR |= GPIO_BSRR_BR14;
				GPIOC -> BSRR |= GPIO_BSRR_BR15;
			}
		}
	}
	else if(x<buffer2 && y>buffer1)//Upper-Left
	{
		x=max-x;
		if(y>x)//Left of F
		{
			x = map(x,max,buffer1,buffer+0.5*buffer,buffer1);
			x=y-x;
			TIM3 -> CCR4 = (x*z)/25;//L
			TIM3 -> CCR3 = (x*z)/25;//L
			TIM3 -> CCR2 = ((y-buffer)*z)/25;//R
			TIM3 -> CCR1 = ((y-buffer)*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;
		}
		else
		{
			//x=2048-x;
			y = map(y,max,buffer1,buffer+0.5*buffer,max);
			x = map(x,buffer1,max,buffer+0.5*buffer,max);
			if ((x-y)>=0)
			{
				y=x-y;
				TIM3 -> CCR4 = (y*z)/25;//L
				TIM3 -> CCR3 = (y*z)/25;//L
				TIM3 -> CCR2 = ((x-buffer)*z)/25;//R
				TIM3 -> CCR1 = ((x-buffer)*z)/25;//R
				GPIOA -> BSRR |= GPIO_BSRR_BR4;
				GPIOA -> BSRR |= GPIO_BSRR_BR5;
				GPIOC -> BSRR |= GPIO_BSRR_BR14;
				GPIOC -> BSRR |= GPIO_BSRR_BR15;
			}
		}
	}
	else if(x<buffer2 && y<buffer2)//Bottom-Left
	{
		x=max-x;
		y=max-y;
		if(y>=x)//Left Back
		{
			x=y-x;
			TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
			TIM3 -> CCR3 = ((y-buffer)*z)/25;//L
			TIM3 -> CCR2 = (x*z)/25;//R
			TIM3 -> CCR1 = (x*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BS5;
			GPIOC -> BSRR |= GPIO_BSRR_BS14;
			GPIOC -> BSRR |= GPIO_BSRR_BS15;
		}
		else //Bottom of Left
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FL
			TIM3 -> CCR2 = 0;//FR
			TIM3 -> CCR1 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BS5;
			GPIOC -> BSRR |= GPIO_BSRR_BS14;
			GPIOC -> BSRR |= GPIO_BSRR_BS15;
		}
	}
	else if(x>buffer1 && y<buffer2)//Bottom-Right
	{
		y=max-y;
		if(y>=x)//Right of Back
		{
			x=y-x;
			TIM3 -> CCR4 = (x*z)/25;//L
			TIM3 -> CCR3 = (x*z)/25;//L
			TIM3 -> CCR2 = ((y-buffer)*z)/25;//R
			TIM3 -> CCR1 = ((y-buffer)*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BS5;
			GPIOC -> BSRR |= GPIO_BSRR_BS14;
			GPIOC -> BSRR |= GPIO_BSRR_BS15;
		}
		else //Bottom of Right
		{
			y=x-y;
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FL
			TIM3 -> CCR2 = 0;//FR
			TIM3 -> CCR1 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BS5;
			GPIOC -> BSRR |= GPIO_BSRR_BS14;
			GPIOC -> BSRR |= GPIO_BSRR_BS15;
		}
	}
	else if(c1=='c')
	{
	}
}

void motorCode1(uint16_t x, uint16_t y, uint16_t z, uint16_t w, uint16_t c1)
{
	TIM3 -> CR1 |= TIM_CR1_CEN;
	TIM3 -> CCER |= TIM_CCER_CC3E;
	TIM3 -> CCER |= TIM_CCER_CC4E;
	TIM3 -> CCER |= TIM_CCER_CC1E;
	TIM3 -> CCER |= TIM_CCER_CC2E;

	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_0;

	//uint16_t max = 65535;
	uint16_t buffer = 32768;
	uint16_t buffer1 = buffer + 0.25*buffer; //39321
	uint16_t buffer2 = buffer - 0.25*buffer; //26214

	if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==2)//centre
	{
		TIM3 -> CCR4 = 0;//L
		TIM3 -> CCR3 = 0;//L
		TIM3 -> CCR2 = 0;//R
		TIM3 -> CCR1 = 0;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==1)//360 left
	{
		TIM3 -> CCR4 = (buffer*z)/25;//L
		TIM3 -> CCR3 = (buffer*z)/25;//L
		TIM3 -> CCR2 = (buffer*z)/25;//R
		TIM3 -> CCR1 = (buffer*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BS14;
		GPIOC -> BSRR |= GPIO_BSRR_BS15;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==3)//360 right
	{
		TIM3 -> CCR4 = (buffer*z)/25;//L
		TIM3 -> CCR3 = (buffer*z)/25;//L
		TIM3 -> CCR2 = (buffer*z)/25;//R
		TIM3 -> CCR1 = (buffer*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BS4;
		GPIOA -> BSRR |= GPIO_BSRR_BS5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}
	//2-Axis
	else if(x<=buffer1 && x>=buffer2 && y>=buffer1)//forward
	{
		TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
		TIM3 -> CCR3 = ((y-buffer)*z)/25;//L
		TIM3 -> CCR2 = ((y-buffer)*z)/25;//R
		TIM3 -> CCR1 = ((y-buffer)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR4;
		GPIOA -> BSRR |= GPIO_BSRR_BR5;
		GPIOC -> BSRR |= GPIO_BSRR_BR14;
		GPIOC -> BSRR |= GPIO_BSRR_BR15;
	}
	else if(x<=buffer1 && x>=buffer2 && y<=buffer2)//backward
	{
		TIM3 -> CCR4 = ((buffer-y)*z)/25;//L
		TIM3 -> CCR3 = ((buffer-y)*z)/25;//L
		TIM3 -> CCR2 = ((buffer-y)*z)/25;//R
		TIM3 -> CCR1 = ((buffer-y)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BS4;
		GPIOA -> BSRR |= GPIO_BSRR_BS5;
		GPIOC -> BSRR |= GPIO_BSRR_BS14;
		GPIOC -> BSRR |= GPIO_BSRR_BS15;
	}
	else if(c1=='m'||c1=='M'||c1=='c'||c1=='n'||c1=='N')
	{
	}
}

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_1);
	RCC -> CFGR |= RCC_CFGR_PPRE2_2;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	timerSetup();

	GPIOSetup();

	UARTSetup();

	UARTSetup1();

	uint16_t A = 0;
	uint16_t count = 0;
	uint16_t B = 0;
	uint32_t X = 0;
	uint32_t Y = 0;

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_RE;
		USART2 -> CR1 |= USART_CR1_RE;


		if (count==0)
		{
			emStop();
			A = USART1 -> DR;

			if(A=='l')
				count=1;

			if(A == 'a')
			{
				uint32_t x=0, y=0, x1=0, y1=0;
				uint8_t z=0, z1=0, w=0, w1=0, c1=0;

				for(int i=0;i<4;i++)
				{
					emStop();
					x = USART1 -> DR;
					x = x - 48;
					x1 = x + x1*10;
				}
				//x1 is output

				for(int j=0;j<4;j++)
				{
					emStop();
					y = USART1 -> DR;
					y = y - 48;
					y1 = y + y1*10;
				}
				//y1 is output

				for(int k=0;k<2;k++)
				{
					emStop();
					z = USART1 -> DR;
					z = z - 48;
					z1 = z + z1*10;
				}

				emStop();
				w = USART1 -> DR;
				w = w - 48;
				w1 = w;

				emStop();
				c1 = USART1 -> DR;

				y1 = y1 - 1024;
				z1 = z1 - 13;
				x1 = x1 - 1024;

				if(x1==2047)
					x1=2048;

				if(y1==1)
					y1=0;

				x1 = x1*32;
				y1 = y1*32;

				if(x1==65536)
					x1=65535;

				if(y1==65536)
					y1=65535;

				x2=x1;
				y2=y1;
				z2=z1;
				w2=w1;
				c2=c1;

				GPIOB -> BSRR |= GPIO_BSRR_BR14;
				GPIOB -> BSRR |= GPIO_BSRR_BS15;

				motorCode(x1, y1, z1, w1, c1);

				x1=0,y1=0,z1=0,w1=0,c1=0;
			}
			if(A=='r')
			{
				motorCode(x2, y2, z2, w2,c2);
			}

			DMA1_Channel1 -> CCR &= ~(DMA_CCR1_EN);
			DMA1_Channel1 -> CNDTR = 16;
			ADC1 -> CR2 |= ADC_CR2_ADON;
			ADC1 -> CR2 |= ADC_CR2_SWSTART;
			DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
			while(!(ADC1 -> SR & (1<<1)));
			X = mAddr[0];
			Y = mAddr[1];

			USART2 -> DR = X;
			while(!((USART2->SR)&(1<<7)))
			{}

			USART2 -> DR = Y;
			while(!((USART2->SR)&(1<<7)))
			{}
		}

		if(count==1)
		{
			emStop1();
			B = USART2 -> DR;

			if(B=='l')
				count=0;

			if(B == 'a')
			{
				uint32_t x=0, y=0, x1=0, y1=0;
				uint8_t z=0, z1=0, w=0, w1=0, c1=0;

				for(int i=0;i<4;i++)
				{
					emStop1();
					x = USART2 -> DR;
					x = x - 48;
					x1 = x + x1*10;
				}
				//x1 is output

				for(int j=0;j<4;j++)
				{
					emStop1();
					y = USART2 -> DR;
					y = y - 48;
					y1 = y + y1*10;
				}
				//y1 is output

				for(int k=0;k<2;k++)
				{
					emStop1();
					z = USART2 -> DR;
					z = z - 48;
					z1 = z + z1*10;
				}

				emStop1();
				w = USART2 -> DR;
				w = w - 48;
				w1 = w;

				emStop1();
				c1 = USART2 -> DR;

				y1 = y1 - 1024;
				z1 = z1 - 13;
				x1 = x1 - 1024;

				if(x1==2047)
					x1=2048;

				if(y1==1)
					y1=0;

				x1 = x1*32;
				y1 = y1*32;

				if(x1==65536)
					x1=65535;

				if(y1==65536)
					y1=65535;

				GPIOB -> BSRR |= GPIO_BSRR_BS14;
				GPIOB -> BSRR |= GPIO_BSRR_BS15;

				motorCode(x1, y1, z1, w1, c1);

				x1=0,y1=0,z1=0,w1=0,c1=0;
			}
		}
	}
}
