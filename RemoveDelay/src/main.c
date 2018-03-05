#include "stm32f10x.h"

volatile uint16_t mAddr[11];

uint16_t map(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e)
{
  return (a-b)*(e-d)/(c-b) + d;
}

void motorCode(uint16_t x, uint16_t y, uint16_t z, uint16_t w)
{
	TIM3 -> CR1 |= TIM_CR1_CEN;
	TIM3 -> CCER |= TIM_CCER_CC3E;
	TIM3 -> CCER |= TIM_CCER_CC4E;

	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;

	uint16_t max = 65535;
	uint16_t buffer = 32768;
	uint16_t buffer1 = 1.25*buffer; //39321
	uint16_t buffer2 = 0.75*buffer; //26214

	if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==2)//centre
	{
		TIM3 -> CCR4 = 0;//FL
		TIM3 -> CCR3 = 0;//FR
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==1)//360 left
	{
		TIM3 -> CCR4 = (buffer*z)/25;//FL
		TIM3 -> CCR3 = (buffer*z)/25;//FR
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BS11;
	}

	else if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==3)//360 right
	{
		TIM3 -> CCR4 = (buffer*z)/25;//L
		TIM3 -> CCR3 = (buffer*z)/25;//R
		GPIOB -> BSRR |= GPIO_BSRR_BS10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}
	//2-Axis
	else if(x<=buffer1 && x>=buffer2 && y>=buffer1)//forward
	{
		TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
		TIM3 -> CCR3 = ((y-buffer)*z)/25;//R
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}
	else if(x<=buffer1 && x>=buffer2 && y<=buffer2)//backward
	{
		TIM3 -> CCR4 = ((buffer-y)*z)/25;//L
		TIM3 -> CCR3 = ((buffer-y)*z)/25;//R
		GPIOB -> BSRR |= GPIO_BSRR_BS10;
		GPIOB -> BSRR |= GPIO_BSRR_BS11;
	}
	else if(y>buffer2 && y<buffer1 && x<buffer2)//Left
	{
		TIM3 -> CCR4 = 0;//FL
		TIM3 -> CCR3 = ((buffer-x)*z)/25;//FR
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}
	else if(y>buffer2 && y<buffer1 && x>buffer1)//Right
	{
		TIM3 -> CCR4 = ((x-buffer)*z)/25;//FL
		TIM3 -> CCR3 = 0;//FR
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}

	if(x>buffer1 && y>=buffer1)//Upper-Right
	{
		if(y>=x)//Right of F
		{
			x = map(x,buffer1,max,buffer1,buffer+0.5*buffer);
			x=y-x;
			//x=x-buffer;
			TIM3 -> CCR4 = ((y-buffer)*z)/25;//L
			TIM3 -> CCR3 = (x*z)/25;//R
			GPIOB -> BSRR |= GPIO_BSRR_BR10;
			GPIOB -> BSRR |= GPIO_BSRR_BR11;

		}
		else//Up of Right
		{
			y = map(y,buffer1,max,max,buffer+0.5*buffer);
			x = map(x,buffer1,max,buffer+0.5*buffer,max);
			if ((x-y)>=0)
			{
				y=x-y;
				TIM3 -> CCR4 = ((x-buffer)*z)/25;//L
				TIM3 -> CCR3 = (y*z)/25;//R
				GPIOB -> BSRR |= GPIO_BSRR_BR10;
				GPIOB -> BSRR |= GPIO_BSRR_BR11;
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
			TIM3 -> CCR3 = ((y-buffer)*z)/25;//R
			GPIOB -> BSRR |= GPIO_BSRR_BR10;
			GPIOB -> BSRR |= GPIO_BSRR_BR11;
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
				TIM3 -> CCR3 = ((x-buffer)*z)/25;//R
				GPIOB -> BSRR |= GPIO_BSRR_BR10;
				GPIOB -> BSRR |= GPIO_BSRR_BR11;
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
			TIM3 -> CCR3 = (x*z)/25;//R
			GPIOB -> BSRR |= GPIO_BSRR_BS10;
			GPIOB -> BSRR |= GPIO_BSRR_BS11;
		}
		else //Bottom of Left
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FR
			GPIOB -> BSRR |= GPIO_BSRR_BS10;
			GPIOB -> BSRR |= GPIO_BSRR_BS11;
		}
	}
	else if(x>buffer1 && y<buffer2)//Bottom-Right
	{
		y=max-y;
		if(y>=x)//Right of Back
		{
			x=y-x;
			TIM3 -> CCR4 = (x*z)/25;//L
			TIM3 -> CCR3 = ((y-buffer)*z)/25;//R
			GPIOB -> BSRR |= GPIO_BSRR_BS10;
			GPIOB -> BSRR |= GPIO_BSRR_BS11;
		}
		else //Bottom of Right
		{
			y=x-y;
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FR
			GPIOB -> BSRR |= GPIO_BSRR_BS10;
			GPIOB -> BSRR |= GPIO_BSRR_BS11;
		}
	}
}

void emStop(void)
{
//	int b = 0;
//    TIM2 -> CR1 |= TIM_CR1_ARPE;
//    TIM2 -> PSC = 65535;
//    TIM2 -> ARR = 1500;
//    TIM2 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART1 -> SR & (1<<5)));
//	{
//		TIM2 -> CR1 |= TIM_CR1_CEN;
//		b = TIM2 -> CNT;
//		if(b >= 1500)
//		{
//			TIM3 -> CCR4 = 0;//FL
//			TIM3 -> CCR3 = 0;//FR
//		}
//	}
//	TIM2 -> CNT = 0;
}

void timerSetup(void)
{
	//PWM
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
	TIM3 -> ARR = 4096;
	TIM3 -> PSC = 0;
	TIM3 -> EGR |= TIM_EGR_UG;
	TIM3 -> CR1 &= ~(TIM_CR1_CEN);
	TIM3 -> CCR3 = 0;
	TIM3 -> CCR4 = 0;
}

void GPIOSetup(void)
{
	GPIOB -> CRL |= (GPIO_CRL_MODE0_0);
	GPIOB -> CRL &= ~(GPIO_CRL_MODE0_1);
	GPIOB -> CRH |= GPIO_CRH_MODE10_0;
	GPIOB -> CRH &= ~(GPIO_CRH_MODE10_1);
	GPIOB -> CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOB -> CRL |= GPIO_CRL_CNF0_1;
	GPIOB -> CRH &= ~(GPIO_CRH_CNF10_0);
	GPIOB -> CRH &= ~(GPIO_CRH_CNF10_1);
	GPIOB -> CRL |= GPIO_CRL_MODE1_0;
	GPIOB -> CRL &= ~(GPIO_CRL_MODE1_1);
	GPIOB -> CRH |= GPIO_CRH_MODE11_0;
	GPIOB -> CRH &= ~(GPIO_CRH_MODE11_1);
	GPIOB -> CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOB -> CRL |= GPIO_CRL_CNF1_1;
	GPIOB -> CRH &= ~(GPIO_CRH_CNF11_0);
	GPIOB -> CRH &= ~(GPIO_CRH_CNF11_1);
	GPIOA -> CRH |= (GPIO_CRH_MODE9_0);
	GPIOA -> CRH |= GPIO_CRH_MODE9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOA -> CRH |= GPIO_CRH_CNF9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_1);
	GPIOA -> CRH |= (GPIO_CRH_CNF10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF10_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM3_REMAP_1);
	AFIO -> MAPR &= ~(AFIO_MAPR_TIM3_REMAP_0);
	GPIOB -> ODR &= ~(GPIO_ODR_ODR0);
	GPIOB -> ODR &= ~(GPIO_ODR_ODR1);
	GPIOB -> ODR &= ~(GPIO_ODR_ODR6);
	GPIOB -> ODR &= ~(GPIO_ODR_ODR7);
}

void UARTSetup(void)
{
	//UART
	USART1 -> CR1 |= USART_CR1_UE;
	USART1 -> BRR = 0x1D4C;//EA6(9600 36) 271(57600 36) 4E2(57600 72) 1D4C(9600 72)
	USART1 -> CR1 &= ~(USART_CR1_M);//8 data bits
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	//USART1 -> CR1 |= USART_CR1_IDLEIE;
	//USART1 -> CR3 &= ~(USART_CR3_RTSE);
}

int main(void)
{
	uint32_t x1=0, y1=0;
	uint8_t z=0, z1=0, w=0, w1=0;
	uint16_t x=0, y=0;
	uint32_t a = 0;

	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
//	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);
//	RCC -> CFGR &= ~(RCC_CFGR_PPRE2_1);
//	RCC -> CFGR |= RCC_CFGR_PPRE2_2;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;

	timerSetup();

	GPIOSetup();

	UARTSetup();

//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_EN);
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_MEM2MEM);
//	DMA1_Channel5 -> CCR |= DMA_CCR1_PL_0;
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PL_1);
//	DMA1_Channel5 -> CCR |= DMA_CCR1_MSIZE_0;
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_MSIZE_1);
//	DMA1_Channel5 -> CCR |= DMA_CCR1_PSIZE_0;
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PSIZE_1);
//	DMA1_Channel5 -> CCR |= (DMA_CCR1_MINC);
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_PINC);
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_CIRC);
//	//DMA1_Channel5 -> CCR |= DMA_CCR1_TCIE;
//	DMA1_Channel5 -> CCR &= ~(DMA_CCR1_DIR);
//	//DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
//	DMA1_Channel5 -> CPAR = 0x40013804;
//	DMA1_Channel5 -> CMAR = mAddr;

	TIM3 -> CR1 |= TIM_CR1_CEN;
	TIM3 -> CCER |= TIM_CCER_CC3E;
	TIM3 -> CCER |= TIM_CCER_CC4E;

	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;

	while(1)
	{
//		DMA1_Channel5 -> CNDTR = 11;
//		DMA1_Channel5 -> CCR |= DMA_CCR1_EN;
		USART1 -> CR1 |= USART_CR1_RE;

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

//			for(int j=0;j<4;j++)
//			{
//				emStop();
//				y = mAddr[5+j];
//				y = y - 48;
//				y1 = y + y1*10;
//			}
//			//y1 is output
//
//			for(int k=0;k<2;k++)
//			{
//				emStop();
//				z = mAddr[9+k];
//				z = z - 48;
//				z1 = z + z1*10;
//			}
//
//			emStop();
//			w = mAddr[10];
//			w = w - 48;
//			w1 = w;

//			y1 = y1 - 1024;
//			z1 = z1 - 13;
			x1 = x1 - 2047;

//			if(x1==2047)
//				x1=2048;
//
//			if(y1==1)
//				y1=0;
//
//
//			x1 = x1*32;
//			y1 = y1*32;
//
//			if(x1==65536)
//				x1=65535;
//
//			if(y1==65536)
//				y1=65535;

			TIM3 -> CCR3 = x1;//FR

//			motorCode(x1, y1, z1, w1);
			x1=0;
			y1=0;
			z1=0;
			w1=0;
		  }
	}
}
