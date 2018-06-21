#include "stm32f10x.h"

uint32_t x2=0, y2=0;
uint8_t z2=0, w2=0, c2=0;

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
		if(b >= 5500)
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

	while(!(USART3 -> SR & (1<<5)))
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
	GPIOA -> CRH = 0x000004B3;//2 Empty(11 12)
	GPIOB -> CRL = 0x4B0000BB;//1 Empty(5) UART ~I2C
	GPIOB -> CRH = 0x33B04088;//3 Empty(10 11 12)
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

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_1);
	RCC -> CFGR |= RCC_CFGR_PPRE2_2;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	timerSetup();

	GPIOSetup();

	UARTSetup();

	uint16_t A = 0;

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_RE;

		emStop();
		A = USART1 -> DR;

		if(A=='u')
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

			motorCode(x1, y1, z1, w1, c1);

			x1=0,y1=0,z1=0,w1=0,c1=0;
		}
	}
}
