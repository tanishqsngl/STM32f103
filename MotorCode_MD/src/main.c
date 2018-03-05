#include "stm32f10x.h"

uint16_t map(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e)
{
  return (a-b)*(e-d)/(c-b) + d;
}

void motorCode(uint16_t x, uint16_t y, uint16_t z, uint16_t w)
{
	TIM2 -> CR1 |= TIM_CR1_CEN;
	TIM2 -> CCER |= TIM_CCER_CC1E;
	TIM2 -> CCER |= TIM_CCER_CC2E;

	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_0;

	uint16_t max = 65535;
	uint16_t buffer = 32768;
	uint16_t buffer1 = buffer + 0.25*buffer; //39321
	uint16_t buffer2 = buffer - 0.25*buffer; //26214

	if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==2)//centre
	{
		TIM2 -> CCR1 = 0;//FL
		TIM2 -> CCR2 = 0;//FR
		GPIOA -> BSRR |= GPIO_BSRR_BR2;
		GPIOA -> BSRR |= GPIO_BSRR_BR3;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==1)//360 left
	{
		TIM2 -> CCR1 = (buffer*z)/25;//FL
		TIM2 -> CCR2 = (buffer*z)/25;//FR
		GPIOA -> BSRR |= GPIO_BSRR_BS2;
		GPIOA -> BSRR |= GPIO_BSRR_BR3;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==3)//360 right
	{
		TIM2 -> CCR1 = (buffer*z)/25;//L
		TIM2 -> CCR2 = (buffer*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR2;
		GPIOA -> BSRR |= GPIO_BSRR_BS3;
	}
	//2-Axis
	else if(x<=buffer1 && x>=buffer2 && y>=buffer1)//forward
	{
		TIM2 -> CCR1 = ((y-buffer)*z)/25;//L
		TIM2 -> CCR2 = ((y-buffer)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BR2;
		GPIOA -> BSRR |= GPIO_BSRR_BR3;
	}
	else if(x<=buffer1 && x>=buffer2 && y<=buffer2)//backward
	{
		TIM2 -> CCR1 = ((buffer-y)*z)/25;//L
		TIM2 -> CCR2 = ((buffer-y)*z)/25;//R
		GPIOA -> BSRR |= GPIO_BSRR_BS2;
		GPIOA -> BSRR |= GPIO_BSRR_BS3;
	}
	else if(y>buffer2 && y<buffer1 && x<buffer2)//Left
	{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = ((buffer-x)*z)/25;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BR2;
			GPIOA -> BSRR |= GPIO_BSRR_BR3;
	}
	else if(y>buffer2 && y<buffer1 && x>buffer1)//Right
	{
		TIM2 -> CCR1 = ((x-buffer)*z)/25;//FL
		TIM2 -> CCR2 = 0;//FR
		GPIOA -> BSRR |= GPIO_BSRR_BR2;
		GPIOA -> BSRR |= GPIO_BSRR_BR3;
	}

	if(x>buffer1 && y>=buffer1)//Upper-Right
	{
		if(y>=x)//Right of F
		{
			x = map(x,buffer1,max,buffer1,buffer+0.5*buffer);
			x=y-x;
			//x=x-buffer;
			TIM2 -> CCR1 = ((y-buffer)*z)/25;//L
			TIM2 -> CCR2 = (x*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BR2;
			GPIOA -> BSRR |= GPIO_BSRR_BR3;

		}
		else//Up of Right
		{
			y = map(y,buffer1,max,max,buffer+0.5*buffer);
			x = map(x,buffer1,max,buffer+0.5*buffer,max);
			if ((x-y)>=0) {
				y=x-y;
				TIM2 -> CCR1 = ((x-buffer)*z)/25;//L
				TIM2 -> CCR2 = (y*z)/25;//R
				GPIOA -> BSRR |= GPIO_BSRR_BR2;
				GPIOA -> BSRR |= GPIO_BSRR_BR3;
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
			TIM2 -> CCR1 = (x*z)/25;//L
			TIM2 -> CCR2 = ((y-buffer)*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BR2;
			GPIOA -> BSRR |= GPIO_BSRR_BR3;
		}
		else
		{
			//x=2048-x;
			y = map(y,max,buffer1,buffer+0.5*buffer,max);
			x = map(x,buffer1,max,buffer+0.5*buffer,max);
			if ((x-y)>=0)
			{
				y=x-y;
				TIM2 -> CCR1 = (y*z)/25;//L
				TIM2 -> CCR2 = ((x-buffer)*z)/25;//R
				GPIOA -> BSRR |= GPIO_BSRR_BR2;
				GPIOA -> BSRR |= GPIO_BSRR_BR3;
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
			TIM2 -> CCR1 = ((y-buffer)*z)/25;//L
			TIM2 -> CCR2 = (x*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BS2;
			GPIOA -> BSRR |= GPIO_BSRR_BS3;
		}
		else //Bottom of Left
		{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BS2;
			GPIOA -> BSRR |= GPIO_BSRR_BS3;
		}
	}
	else if(x>buffer1 && y<buffer2)//Bottom-Right
	{
		y=max-y;
		if(y>=x)//Right of Back
		{
			x=y-x;
			TIM2 -> CCR1 = (x*z)/25;//L
			TIM2 -> CCR2 = ((y-buffer)*z)/25;//R
			GPIOA -> BSRR |= GPIO_BSRR_BS2;
			GPIOA -> BSRR |= GPIO_BSRR_BS3;
		}
		else //Bottom of Right
		{
			y=x-y;
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			GPIOA -> BSRR |= GPIO_BSRR_BS2;
			GPIOA -> BSRR |= GPIO_BSRR_BS3;
		}
	}
}

void emStop(void)
{
	int b = 0;
    TIM3 -> CR1 |= TIM_CR1_ARPE;
    TIM3 -> PSC = 65535;
    TIM3 -> ARR = 1000;
    TIM3 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART1 -> SR & (1<<5)))
	{
		TIM3 -> CR1 |= TIM_CR1_CEN;
		b = TIM3 -> CNT;
		if(b >= 500)
		{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
		}
	}
	TIM3 -> CNT = 0;
}

void timerSetup(void)
{
	//PWM
	TIM2 -> CR1 &= ~(TIM_CR1_ARPE);
	TIM2 -> CR1 &= ~(TIM_CR1_UDIS);
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM2 -> CCMR1 &= ~(TIM_CCMR1_OC1M_1);
	TIM2 -> CCMR1 |= (TIM_CCMR1_OC1M_0);
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1PE;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM2 -> CCMR1 &= ~(TIM_CCMR1_OC2M_1);
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_0;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2 -> CCER &= ~(TIM_CCER_CC1E);
	TIM2 -> CCER |= (TIM_CCER_CC1P);
	TIM2 -> CCER &= ~(TIM_CCER_CC2E);
	TIM2 -> CCER |= (TIM_CCER_CC2P);
	TIM2 -> DIER |= TIM_DIER_UIE;
	TIM2 -> ARR = 32768;
	TIM2 -> PSC = 0;
	TIM2 -> EGR |= TIM_EGR_UG;
	TIM2 -> CR1 &= ~(TIM_CR1_CEN);
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
}

void GPIOSetup(void)
{
	GPIOA -> CRL &= ~(GPIO_CRL_MODE1_0);
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;
	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE2_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOA -> CRL |= GPIO_CRL_CNF1_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_1);
	GPIOA -> CRL |= GPIO_CRL_MODE0_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE0_1);
	GPIOA -> CRL |= GPIO_CRL_MODE3_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE3_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOA -> CRL |= GPIO_CRL_CNF0_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_1);
	GPIOA -> CRH |= (GPIO_CRH_MODE9_0);
	GPIOA -> CRH |= GPIO_CRH_MODE9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOA -> CRH |= GPIO_CRH_CNF9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_1);
	GPIOA -> CRH |= (GPIO_CRH_CNF10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF10_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
	GPIOA -> ODR &= ~(GPIO_ODR_ODR0);
	GPIOA -> ODR &= ~(GPIO_ODR_ODR1);
	GPIOA -> ODR &= ~(GPIO_ODR_ODR2);
	GPIOA -> ODR &= ~(GPIO_ODR_ODR3);
}

void UARTSetup(void)
{
	//UART
	USART1 -> BRR = 0x271;//57600 EA6 753 271 1D4C
	USART1 -> CR1 &= ~(USART_CR1_M);//8 data bits
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	USART1 -> CR1 |= USART_CR1_RE;
	USART1 -> CR1 |= USART_CR1_IDLEIE;
	USART1 -> CR3 &= ~(USART_CR3_RTSE);
}

int main(void)
{
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t a = 0;
	uint32_t x1 = 0;
	uint32_t y1 = 0;
	uint8_t z = 0;
	uint8_t z1 = 0;
	uint8_t w = 0;
	uint8_t w1 = 0;

	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);
	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_1);
	RCC -> CFGR |= RCC_CFGR_PPRE2_2;
	//RCC -> AHBENR |= RCC_AHBENR_DMA1EN;//Channel 5
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	timerSetup();

	GPIOSetup();

	UARTSetup();

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_UE;
		emStop();
		a = USART1 -> DR;

		if(a == 97)
		{
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

//			emStop();
//			x = USART1 -> DR;
//			x = x - 48;
//			x1 = x + x1*10;
//
//			emStop();
//			x = USART1 -> DR;
//			x = x - 48;
//			x1 = x + x1*10;
//
//			emStop();
//			x = USART1 -> DR;
//			x = x - 48;
//			x1 = x + x1*10;
//
//			emStop();
//			x = USART1 -> DR;
//			x = x - 48;
//			x1 = x + x1*10;
//
//
//			emStop();
//			y = USART1 -> DR;
//			y = y - 48;
//			y1 = y + y1*10;
//
//			emStop();
//			y = USART1 -> DR;
//			y = y - 48;
//			y1 = y + y1*10;
//
//			emStop();
//			y = USART1 -> DR;
//			y = y - 48;
//			y1 = y + y1*10;
//
//			emStop();
//			y = USART1 -> DR;
//			y = y - 48;
//			y1 = y + y1*10;
//
//
//			emStop();
//			z = USART1 -> DR;
//			z = z - 48;
//			z1 = z + z1*10;
//
//			emStop();
//			z = USART1 -> DR;
//			z = z - 48;
//			z1 = z + z1*10;

			emStop();
			w = USART1 -> DR;
			w = w - 48;
			w1 = w;

			y1 = y1 - 1024;
			z1 = z1 - 13;
			x1 = x1 - 1024;

			x1 = x1*32;
			y1 = y1*32;

			if(x1==65536)
				x1=65535;

			if(y1==65536)
				y1=65535;

			motorCode(x1, y1, z1, w1);
			x1=0;
			y1=0;
			z1=0;
			w1=0;
		  }
	}
}
