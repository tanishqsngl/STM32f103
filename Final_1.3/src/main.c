#include "stm32f10x.h"
int servo1 = 1500;
int servo2 = 1500;
uint32_t x2 = 0;
uint32_t y2 = 0;
uint8_t z2 = 0;
uint8_t w2 = 0;
uint8_t c2=0;

void stopArm(void)
{
	TIM1 -> CCR2 = 0;
	TIM1 -> CCR3 = 0;
	GPIOC -> BSRR |= GPIO_BSRR_BR13;
	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	TIM3 -> CCR1 = 0;
	TIM3 -> CCR2 = 0;
	TIM4 -> CCR3 = servo1;
	TIM4 -> CCR4 = servo2;
	GPIOA -> BSRR |= GPIO_BSRR_BR11;
	GPIOA -> BSRR |= GPIO_BSRR_BR12;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;
	GPIOB -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR9;
}

void emStop(void)
{
	int t=0;

	while(!((USART1->SR)&(1<<5)))
	{
		t++;
		if(t==327680)//0.5 second
		{
			TIM3 -> CCR4 = 2;//FL
			TIM3 -> CCR3 = 2;//FR
			stopArm();
			GPIOB -> BSRR |= GPIO_BSRR_BS10;
		}
		t=0;
	}
}

void emStop1(void)
{
	long t=0;

	while(!(USART2 -> SR & (1<<5)))
	{
		t++;
		if(t>=4000000)//0.5 second
		{
			TIM3 -> CCR4 = 2;//FL
			TIM3 -> CCR3 = 2;//FR
			stopArm();
		}
		t=0;
	}
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

	//rArm
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

	//Swivel Base Pins
	//TIM1 -> CR1 |= (TIM_CR1_DIR);
	TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM1 -> CCMR2 &= ~(TIM_CCMR2_OC3M_1);
	TIM1 -> CCMR2 |= (TIM_CCMR2_OC3M_0);
	TIM1 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM1 -> CCMR1 &= ~(TIM_CCMR1_OC2M_1);
	TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_0;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC2PE;
	TIM1 -> CCER &= ~(TIM_CCER_CC2E);
	TIM1 -> CCER |= (TIM_CCER_CC2P);
	TIM1 -> CCER |= (TIM_CCER_CC2NP);
	TIM1 -> CCER &= ~(TIM_CCER_CC3E);
	TIM1 -> CCER |= (TIM_CCER_CC3P);
	TIM1 -> CCER |= (TIM_CCER_CC3NP);
	//TIM1 -> CCER |= (TIM_CCER_CC3NE);
	//TIM1 -> CCER |= (TIM_CCER_CC2NE);
	TIM1 -> DIER |= TIM_DIER_UIE;
	TIM1 -> ARR = 32768;
	TIM1 -> PSC = 0;
	TIM1 -> EGR |= TIM_EGR_UG;
	TIM1 -> CR1 &= ~(TIM_CR1_CEN);
	TIM1 -> BDTR |= TIM_BDTR_MOE;
	TIM1 -> CCR3 = 0;
	TIM1 -> CCR2 = 0;

	//Wheel Motor
	TIM4 -> CR1 &= ~(TIM_CR1_ARPE);
	TIM4 -> CR1 &= ~(TIM_CR1_UDIS);
	TIM4 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM4 -> CCMR2 &= ~(TIM_CCMR2_OC3M_1);
	TIM4 -> CCMR2 |= (TIM_CCMR2_OC3M_0);
	TIM4 -> CCMR2 |= TIM_CCMR2_OC3PE;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM4 -> CCMR2 &= ~(TIM_CCMR2_OC4M_1);
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_0;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4PE;
	TIM4 -> CCER &= ~(TIM_CCER_CC3E);
	TIM4 -> CCER |= (TIM_CCER_CC3P);
	TIM4 -> CCER &= ~(TIM_CCER_CC4E);
	TIM4 -> CCER |= (TIM_CCER_CC4P);
	TIM4 -> DIER |= TIM_DIER_UIE;
	TIM4 -> ARR = 20000;
	TIM4 -> PSC = 72;
	TIM4 -> EGR |= TIM_EGR_UG;
	TIM4 -> CR1 &= ~(TIM_CR1_CEN);
	TIM4 -> CCR3 = 0;
	TIM4 -> CCR4 = 0;
}

void GPIOSetup(void)
{
	GPIOA -> CRL = 0xBB334333;
	GPIOA -> CRH = 0x000334B3;
	GPIOB -> CRL = 0x333000BB;
	GPIOB -> CRH = 0xBB3333BB;
	GPIOC -> CRH = 0x33300000;
}

void UARTSetup(void)
{
	//UART
	USART1 -> CR1 |= USART_CR1_UE;
	USART1 -> BRR = 0x271;//EA6(9600 36) 271(57600 36) 4E2(57600 72) 753(38400 72)
	USART1 -> CR1 &= ~(USART_CR1_M);//8 data bits
	USART1 -> CR1 |= USART_CR1_RXNEIE;
	USART1 -> CR1 |= USART_CR1_IDLEIE;
	USART1 -> CR3 &= ~(USART_CR3_RTSE);
}

void UARTSetup1(void)
{
	//UART
	USART2 -> CR1 |= USART_CR1_UE;
	USART2 -> BRR = 0x271;//EA6(9600 36) 271(57600 36) 4E2(57600 72) 753(38400 72)
	USART2 -> CR1 &= ~(USART_CR1_M);//8 data bits
	USART2 -> CR1 |= USART_CR1_RXNEIE;
	USART2 -> CR1 |= USART_CR1_IDLEIE;
	USART2 -> CR3 &= ~(USART_CR3_RTSE);
}

void DCServoF(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BS2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;

	Delay(aDelay);
}

void DCServoB(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BS2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);
}

void DCServoF1(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BS5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BS7;

	Delay(aDelay);
}

void DCServoB1(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS8;
	GPIOB -> BSRR |= GPIO_BSRR_BS5;
	GPIOB -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BS7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS8;
	GPIOB -> BSRR |= GPIO_BSRR_BS5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BS7;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BS5;
	GPIOB -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BS7;

	Delay(aDelay);
}

uint16_t map(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e)
{
  return (a-b)*(e-d)/(c-b) + d;
}

void Delay(int time)
{
	volatile int i,j;

	time = time*10;
	for (i=0;i<time;i++)
		j++;
}

void motorCode(uint16_t x, uint16_t y, uint16_t z, uint16_t w, uint16_t c1)
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

	TIM4 -> CR1 |= TIM_CR1_CEN;
	TIM4 -> CCER |= TIM_CCER_CC3E;
	TIM4 -> CCER |= TIM_CCER_CC4E;

	TIM4 -> CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC3M_0;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_0;

	uint16_t max = 65535;
	uint16_t buffer = 32768;
	uint16_t buffer1 = buffer + 0.25*buffer; //39321
	uint16_t buffer2 = buffer - 0.25*buffer; //26214

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
	else if(c1=='m'||c1=='M'||c1=='c'||c1=='n'||c1=='N'||c1=='A')
	{
		if(c1=='m')
		{
			servo1++;
			if(servo1>2500)
				servo1=2500;
		}
		if(c1=='M')
		{
			servo1--;
			if(servo1<400)
				servo1=400;
		}
		if(c1=='n')
		{
			servo2++;
			if(servo2>2500)
				servo2=2500;
		}
		if(c1=='N')
		{
			servo2--;
			if(servo2<400)
				servo2=400;
		}
		if(c1=='c')
		{
			TIM4 -> CCR3 = servo1;
			TIM4 -> CCR4 = servo2;
		}
		TIM4 -> CCR3 = servo1;
		TIM4 -> CCR4 = servo2;
		if(c1=='A')
		{
			motorCode1(x2,y2,z2,w2,c2);
		}
		x2=0,y2=0,z2=0,w2=0,c2=0;
	}
}

void motorCode1(uint16_t x, uint16_t y, uint16_t z, uint16_t w, uint16_t c1)
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
	uint16_t buffer1 = buffer + 0.25*buffer; //39321
	uint16_t buffer2 = buffer - 0.25*buffer; //26214

	if(x<buffer1 && y<buffer1 && x>buffer2 && y>buffer2 && w==2)//centre
	{
		TIM3 -> CCR4 = 0;//FL
		TIM3 -> CCR3 = 0;//FR
		GPIOB -> BSRR |= GPIO_BSRR_BR10;
		GPIOB -> BSRR |= GPIO_BSRR_BR11;
	}
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
	else if(c1=='m'||c1=='M'||c1=='c'||c1=='n'||c1=='N')
	{
		if(c1=='c')
		{
		}
	}
}

void ultrasonic(int threshold)
{
    int flag1=0, flag2=0, count=0, count2=0;

    GPIOA->BSRR=(1<<5);
    delay(100);
    GPIOA->BRR=(1<<5);

    while(!((GPIOB->IDR)&&(1<<4)));

    while((GPIOB->IDR)&&(1<<4))
    {
        count++;
    }

    if (count<=threshold)
    {
        flag1=1;
    }

    GPIOB->BSRR=(1<<13);
    delay(100);
    GPIOB->BRR=(1<<13);

    while(!((GPIOB->IDR)&&(1<<12)));

    while((GPIOB->IDR)&&(1<<12))
    {
        count2++;
    }

    if (count2<=threshold)
    {
        flag2=1;
    }

    if(flag1==1)
    {
        //give command for stopping the rover for 0.5 second
    	motorCode(32768,32768,13,2,'c');
    	delay(500);
        //give command for moving the rover backwards for 1 second
    	motorCode(32768,0,25,2,'c');
    	delay(1000);
        //give command for turning in one direction for 2 seconds
    	motorCode(32768,32768,25,1,'c');
    	delay(2000);
    }

    if(flag2==1)
    {
        //give command for stopping the rover for 0.5 second
    	motorCode(32768,32768,13,2,'c');
    	delay(500);
        //give command for moving the rover backwards for 1 second
    	motorCode(32768,0,25,2,'c');
    	delay(1000);
        //give command for turning in the other direction for 2 seconds
    	motorCode(32768,32768,25,3,'c');
    	delay(2000);
    }
}

void RoboticArm(uint32_t A)
{
	uint16_t sBase = 0;
	uint16_t sBase1 = 0;
	uint32_t roll = 0;
	uint32_t roll1 = 0;
	uint16_t servoD = 0;
	uint16_t servoD1 = 0;
	uint16_t servoD2 = 0;
	uint16_t servoD21 = 0;

	if(A=='s' || A=='S')//s or S Swivel Base
	{
		for(int i=0;i<4;i++)
		{
			emStop();
			sBase = sBase - 48;
			sBase1 = sBase1*10 + sBase;
		}
		//Main code for swivel base
		TIM1 -> CR1 |= TIM_CR1_CEN;
		TIM1 -> CCER |= TIM_CCER_CC3NE;
		TIM1 -> CCER |= TIM_CCER_CC2NE;

		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_2;
		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_1;
		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_0;
		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_2;
		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_1;
		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_0;

		for(int i=0;i<2;i++)
		{
			emStop();
			sBase = USART1-> DR;
			sBase = sBase - 48;
			sBase1 = sBase1*10 + sBase;
		}

		sBase1 = sBase1-12;
		sBase1 = sBase1*1260;

		if(A=='s')//s forward
		{
			TIM1 -> CCR2 = 0;
			TIM1 -> CCR3 = sBase1;
		}
		else if(A=='S')//S backward
		{
			TIM1 -> CCR2 = 32768;
			TIM1 -> CCR3 = sBase1;
		}
	}

	if(A=='t' || A=='T')//DC Servo
	{
		for(int i=0;i<2;i++)
		{
			emStop();
			servoD = USART1 -> DR;
			servoD = servoD-48;
			servoD1 = servoD1*10 + servoD;
		}

		servoD1 = servoD1-12;
		//servoD1 = servoD1;

		if(A=='t')//t
		{
			//DC Servo forward A0 A1 A2 C15
			DCServoF(servoD1);
		}

		else if(A=='T')//T
		{
			//DC Servo backward
			DCServoB(servoD1);
		}
	}

	if(A=='o' || A=='O')//DC Servo
		{
			for(int i=0;i<2;i++)
			{
				emStop();
				servoD2 = USART1 -> DR;
				servoD2 = servoD2-48;
				servoD21 = servoD21*10 + servoD2;
			}

			servoD21 = servoD21-12;
			//servoD1 = servoD1;

			if(A=='o')//t
			{
				//DC Servo forward A8 B5 B6 B7
				DCServoF1(servoD21);
			}

			else if(A=='O')//T
			{
				//DC Servo backward
				DCServoB1(servoD21);
			}
		}

	if(A=='b' || A=='B')//B b actuator
	{
		if(A=='b')//b forward
		{
			GPIOC -> BSRR |= GPIO_BSRR_BS13;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
		}
		else if(A=='B')//B backward
		{
			GPIOC -> BSRR |= GPIO_BSRR_BS13;
			GPIOC -> BSRR |= GPIO_BSRR_BS14;
		}
	}

	if(A=='p' || A=='P')//Pitch p and P
	{
		if(A=='p')//forward
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
		}

		else if(A=='P')//Backward
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS4;
			GPIOA -> BSRR |= GPIO_BSRR_BS5;
		}
	}

	if(A=='g' || A=='G')//Roll q and Q
	{
		TIM3 -> CR1 |= TIM_CR1_CEN;
		TIM3 -> CCER |= TIM_CCER_CC1E;
		TIM3 -> CCER |= TIM_CCER_CC2E;

		TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_2;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_1;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_0;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_1;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_0;

		for(int i=0;i<2;i++)
		{
			emStop();
			roll = USART1-> DR;
			roll = roll - 48;
			roll1 = roll1*10 + roll;
		}

		roll1 = roll1 - 12;
		roll1 = roll1*1260;

		if(A=='g')//q forward
		{
			TIM3 -> CCR1 = 0;
			TIM3 -> CCR2 = roll1;
		}
		else if(A=='G')//Q backward
		{
			TIM3 -> CCR1 = 32768;
			TIM3 -> CCR2 = roll1;
		}
	}

	if(A=='q' || A=='Q')//Gripper G g
	{
		if(A=='q')//forward g
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS11;
			GPIOA -> BSRR |= GPIO_BSRR_BR12;
		}
		else if(A=='Q')//Backward G
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS11;
			GPIOA -> BSRR |= GPIO_BSRR_BS12;
		}
	}

	else if(A=='c')
	{
		TIM3 -> CCR4 = 0;//FL
		TIM3 -> CCR3 = 0;//FR
		stopArm();
	}
	sBase = 0;
	sBase1 = 0;
	roll = 0;
	roll1 = 0;
	servoD = 0;
	servoD1 = 0;
	servoD2 = 0;
	servoD21 = 0;
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
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;

	timerSetup();

	GPIOSetup();

	UARTSetup();

	UARTSetup1();

	uint16_t A = 0;
	uint16_t count = 0;
	uint16_t B = 0;

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
				stopArm();

				uint32_t x = 0;
				uint32_t y = 0;
				uint32_t x1 = 0;
				uint32_t y1 = 0;
				uint8_t z = 0;
				uint8_t z1 = 0;
				uint8_t w = 0;
				uint8_t w1 = 0;
				uint8_t c1=0;

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

			else if(A=='r')
			{
				TIM3 -> CCR4 = 0;//FL
				TIM3 -> CCR3 = 0;//FR

				emStop();
				A = USART1 -> DR;

				RoboticArm(A);
			}
		}

		if(count==1)
		{
			emStop1();
			ultrasonic(5000);
			B = USART2 -> DR;

			if(B=='l')
				count=0;

			if(B == 'a')
			{
				stopArm();

				uint32_t x = 0;
				uint32_t y = 0;
				uint32_t x1 = 0;
				uint32_t y1 = 0;
				uint8_t z = 0;
				uint8_t z1 = 0;
				uint8_t w = 0;
				uint8_t w1 = 0;
				uint8_t c1=0;

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

				motorCode(x1, y1, z1, w1, c1);

				x1=0,y1=0,z1=0,w1=0,c1=0;
			}
		}
	}
}
