#include "stm32f10x.h"

void motorCode(uint16_t x, uint16_t y, uint16_t z, uint16_t w)
{
	uint16_t x1 = 0;
	uint16_t y1 = 0;
	if(x<2252 && y<2252 && x>1843 && y>1843)//centre
	{
		TIM2 -> CCR1 = 0;//FL
		TIM2 -> CCR2 = 0;//FR
		TIM2 -> CCR3 = 0;//BL
		TIM2 -> CCR4 = 0;//BR
	}

	if(x<2252 && y<2252 && x>1843 && y>1843 && w<1843)//360 left
	{
		w = 2048 - w;
		TIM2 -> CCR1 = 0;//FL
		TIM2 -> CCR2 = (w*z)/25;//FR
		TIM2 -> CCR3 = (w*z)/25;//BL
		TIM2 -> CCR4 = 0;//BR
	}

	if(x<2252 && y<2252 && x>1843 && y>1843 && w>2140)//360 right
	{
		TIM2 -> CCR1 = (w*z)/25;//FL
		TIM2 -> CCR2 = 0;//FR
		TIM2 -> CCR3 = 0;//BL
		TIM2 -> CCR4 = (w*z)/25;//BR
	}
	//2-Axis
	else if(x<=2252 && x>=1843 && y>=2252)//forward
	{
		TIM2 -> CCR1 = ((y-2048)*z)/25;//FL
		TIM2 -> CCR2 = ((y-2048)*z)/25;//FR
		TIM2 -> CCR3 = 0;//BL
		TIM2 -> CCR4 = 0;//BR
	}
	else if(x<=2252 && x>=1843 && y<1843)//backward
	{
		TIM2 -> CCR1 = 0;//FL
		TIM2 -> CCR2 = 0;//FR
		TIM2 -> CCR3 = ((2047-y)*z)/25;//BL
		TIM2 -> CCR4 = ((2047-y)*z)/25;//BR
	}
	/*else if(y>1843 && y<2252 && x<1843)//Left
	{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = ((2047-x)*z)/25;//FR
			TIM2 -> CCR3 = ((2047-x)*z)/25;//BL
			TIM2 -> CCR4 = 0;//BR
	}
	else if(y>1843 && y<2252 && x>2252)//Right
	{
		TIM2 -> CCR1 = ((x-2048)*z)/25;//FL
		TIM2 -> CCR2 = 0;//FR
		TIM2 -> CCR3 = 0;//BL
		TIM2 -> CCR4 = ((x-2048)*z)/25;//BR
	}*/

	else if(x>2252 && y>2252)//Upper-Right
	{
		if(y>=x)//Right of F
		{
			x=y-x;
			//x=x-2048;
			TIM2 -> CCR1 = ((y-2048)*z)/25;//FL
			TIM2 -> CCR2 = ((x-1024)*z)/25;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}
		/*else//Up of Right
		{
			y=x-y;
			//y=y-2048;
			TIM2 -> CCR1 = ((x-2048)*z)/25;//FL
			TIM2 -> CCR2 = ((y-2048)*z)/25;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}*/
	}
	else if(x<1843 && y>2252)//Upper-Left
	{
		x=4095-x;
		//y=y-2048;
		if(y>x)//Left of F
		{
			x=y-x;
			TIM2 -> CCR1 = (x*z)/25;//FL
			TIM2 -> CCR2 = ((y-2048)*z)/25;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}
		/*else
		{
			y=x-y;
				TIM2 -> CCR1 = 0;//FL
				TIM2 -> CCR2 = (x*z)/25;//FR
				TIM2 -> CCR3 = (y*z)/25;//BL
				TIM2 -> CCR4 = 0;//BR
		}*/
	}
	else if(x<1843 && y<1843)//Bottom-Left
	{
		x=4095-x;
		y=4095-y;
		if(y>x)//Left Back
		{
			x=y-x;
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			TIM2 -> CCR3 = ((y-2048)*z)/25;//BL
			TIM2 -> CCR4 = (x*z)/25;//BR
		}
		else //Bottom of Left
		{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}
	}
	else if(x>2252 && y<1843)//Bottom-Right
	{
		y=4095-y;
		if(y>x)//Right of Back
		{
			x=y-x;
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			TIM2 -> CCR3 = (x*z)/25;//BL
			TIM2 -> CCR4 = ((y-2048)*z)/25;//BR
		}
		else //Bottom of Right
		{
			y=x-y;
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}
	}
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void emStop(void)
{
	int b = 0;
    TIM3 -> CR1 |= TIM_CR1_ARPE;
    TIM3 -> PSC = 65535;
    TIM3 -> ARR = 2000;
    TIM3 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART1 -> SR & (1<<5)))
	{
		TIM3 -> CR1 |= TIM_CR1_CEN;
		b = TIM3 -> CNT;
		if(b >= 1000)
		{
			TIM2 -> CCR1 = 0;//FL
			TIM2 -> CCR2 = 0;//FR
			TIM2 -> CCR3 = 0;//BL
			TIM2 -> CCR4 = 0;//BR
		}
	}
	TIM3 -> CNT = 0;
}

void timerSetup(void)
{
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
    TIM2 -> CR1 |= TIM_CR1_CEN;
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
	TIM2 -> CCR3 = 0;
	TIM2 -> CCR4 = 0;
}

void GPIOSetup(void)
{
	GPIOA -> CRL |= GPIO_CRL_MODE1_0;
		GPIOA -> CRL |= GPIO_CRL_MODE1_1;
		GPIOA -> CRL |= GPIO_CRL_MODE2_0;
		GPIOA -> CRL |= GPIO_CRL_MODE2_1;
		GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);
		GPIOA -> CRL |= GPIO_CRL_CNF1_1;
		GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
		GPIOA -> CRL |= GPIO_CRL_CNF2_1;
		GPIOA -> CRL |= GPIO_CRL_MODE0_0;
		GPIOA -> CRL |= GPIO_CRL_MODE0_1;
		GPIOA -> CRL |= GPIO_CRL_MODE3_0;
		GPIOA -> CRL |= GPIO_CRL_MODE3_1;
		GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
		GPIOA -> CRL |= GPIO_CRL_CNF0_1;
		GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
		GPIOA -> CRL |= GPIO_CRL_CNF3_1;
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
		GPIOA -> ODR = 0x00;
}

void UARTSetup(void)
{
	//UART
	//dr address = 0x40013804
	USART1 -> BRR = 0x271;//57600 EA6 753
	USART1 -> CR1 &= ~(USART_CR1_M);//8 data bits
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	USART1 -> CR1 |= USART_CR1_RE;
	USART1 -> CR1 |= USART_CR1_IDLEIE;
	USART1 -> CR3 &= ~(USART_CR3_RTSE);
}

int main(void)
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t a = 0;
	uint16_t x1 = 0;
	uint16_t y1 = 0;
	uint16_t z = 0;
	uint16_t z1 = 0;
	uint16_t w = 0;
	uint16_t w1 = 0;

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

	TIM2 -> CCR1 = 0;//FL
	TIM2 -> CCR2 = 0;//FR
	TIM2 -> CCR3 = 0;//BL
	TIM2 -> CCR4 = 0;//BR

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_UE;
		emStop();
		a = USART1 -> DR;

		if(a == 97)
		{
			emStop();
			x = USART1 -> DR;
			x = x - 48;
			x1 = x + x1*10;

			emStop();
			x = USART1 -> DR;
			x = x - 48;
			x1 = x + x1*10;

			emStop();
			x = USART1 -> DR;
			x = x - 48;
			x1 = x + x1*10;

			emStop();
			x = USART1 -> DR;
			x = x - 48;
			x1 = x + x1*10;
			//x1 is output

			emStop();
			y = USART1 -> DR;
			y = y - 48;
			y1 = y + y1*10;

			emStop();
			y = USART1 -> DR;
			y = y - 48;
			y1 = y + y1*10;

			emStop();
			y = USART1 -> DR;
			y = y - 48;
			y1 = y + y1*10;

			emStop();
			y = USART1 -> DR;
			y = y - 48;
			y1 = y + y1*10;
			//y1 is output

			emStop();
			z = USART1 -> DR;
			z = z - 48;
			z1 = z + z1*10;

			emStop();
			z = USART1 -> DR;
			z = z - 48;
			z1 = z + z1*10;

			emStop();
			w = USART1 -> DR;
			w = w - 48;
			w1 = w + w1*10;

			emStop();
			w = USART1 -> DR;
			w = w - 48;
			w1 = w + w1*10;

			emStop();
			w = USART1 -> DR;
			w = w - 48;
			w1 = w + w1*10;

			emStop();
			w = USART1 -> DR;
			w = w - 48;
			w1 = w + w1*10;

			y1 = map(y1, 2047, 6140, 4095, 0);

			z1 = z1 - 13;
			x1 = x1 - 2047;
			//y1 = y1 - 2047;
			w1 = w1 - 2047;

			motorCode(x1, y1, z1, w1);
			x1=0;
			y1=0;
			z1=0;
			w1=0;
		  }
	}
}
