#include "stm32f10x.h"
int servo1 = 1500;
int servo2 = 1500;
int servo3 = 1500;
int flag1=0;
int flag2=0;

void stopArm(void)
{
	TIM1 -> CCR2 = 0;
	TIM1 -> CCR3 = 0;
	TIM3 -> CCR4 = servo2;
	TIM3 -> CCR3 = servo1;
	TIM3 -> CCR2 = servo3;
	GPIOA -> BSRR |= GPIO_BSRR_BR12;
	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	GPIOA -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR13;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;
	GPIOB -> BSRR |= GPIO_BSRR_BR8;
}

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
			stopArm();
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
			stopArm();
		}
	}
	TIM2 -> CNT = 0;
}

void timerSetup(void)
{
	//SwivelBase and Roll Pins
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
	TIM1 -> DIER |= TIM_DIER_UIE;
	TIM1 -> ARR = 32768;
	TIM1 -> PSC = 0;
	TIM1 -> EGR |= TIM_EGR_UG;
	TIM1 -> CR1 &= ~(TIM_CR1_CEN);
	TIM1 -> BDTR |= TIM_BDTR_MOE;
	TIM1 -> CCR3 = 0;
	TIM1 -> CCR2 = 0;

	//Servo
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
	TIM3 -> ARR = 20000;
	TIM3 -> PSC = 72;
	TIM3 -> EGR |= TIM_EGR_UG;
	TIM3 -> CR1 &= ~(TIM_CR1_CEN);
}

void GPIOSetup(void)
{
	GPIOA -> CRL = 0xB3334B33;
	GPIOA -> CRH = 0x000304B3;
	GPIOB -> CRL = 0x333000BB;
	GPIOB -> CRH = 0xBB300003;
	GPIOC -> CRH = 0x33000000;
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
	//USART2 -> CR1 |= USART_CR1_TXEIE;
	//USART2 -> CR1 |= USART_CR1_TCIE;
	USART2 -> CR1 |= USART_CR1_IDLEIE;
	USART2 -> CR3 &= ~(USART_CR3_RTSE);
	//USART2 -> CR1 |= USART_CR1_TE;
	//us_delay(100);
}

void DCServoF(uint32_t aDelay)
{
	GPIOC -> BSRR |= GPIO_BSRR_BS14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;

	Delay(aDelay);
}

void DCServoB(uint32_t aDelay)
{
	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BR14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);

	GPIOC -> BSRR |= GPIO_BSRR_BS14;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;
	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;

	Delay(aDelay);
}

void DCServoF1(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	GPIOA -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	GPIOA -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BR13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BS5;
	GPIOA -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	GPIOA -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BS13;

	Delay(aDelay);
}

void DCServoB1(uint32_t aDelay)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS4;
	GPIOA -> BSRR |= GPIO_BSRR_BS5;
	GPIOA -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BR13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS4;
	GPIOA -> BSRR |= GPIO_BSRR_BR5;
	GPIOA -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BS13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS4;
	GPIOA -> BSRR |= GPIO_BSRR_BS5;
	GPIOA -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BS13;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR4;
	GPIOA -> BSRR |= GPIO_BSRR_BS5;
	GPIOA -> BSRR |= GPIO_BSRR_BS6;
	GPIOB -> BSRR |= GPIO_BSRR_BS13;

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

void us_delay(uint32_t j)
{
	for(uint32_t i=0;i<=(8*j);i++)
	{}
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
		for(int i=0;i<2;i++)
		{
			emStop();
			sBase = USART2 -> DR;
			sBase = sBase - 48;
			sBase1 = sBase1*10 + sBase;
		}
		//Main code for swivel base
		TIM1 -> CR1 |= TIM_CR1_CEN;
		TIM1 -> CCER |= TIM_CCER_CC2NE;

		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_2;
		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_1;
		TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_0;

		sBase1 = sBase1-12;
		sBase1 = sBase1*1260;

		if(A=='s')//s forward
		{
			GPIOA -> BSRR |= GPIO_BSRR_BR12;
			TIM1 -> CCR2 = sBase1;
		}
		else if(A=='S')//S backward
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS12;
			TIM1 -> CCR2 = sBase1;
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
			GPIOB -> BSRR |= GPIO_BSRR_BS5;
			GPIOB -> BSRR |= GPIO_BSRR_BR6;
		}
		else if(A=='B')//B backward
		{
			GPIOB -> BSRR |= GPIO_BSRR_BS5;
			GPIOB -> BSRR |= GPIO_BSRR_BS6;
		}
	}

	if(A=='g' || A=='G')//Roll q and Q
	{
		TIM1 -> CR1 |= TIM_CR1_CEN;
		TIM1 -> CCER |= TIM_CCER_CC3NE;

		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_2;
		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_1;
		TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_0;

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
			GPIOA -> BSRR |= GPIO_BSRR_BR8;
			TIM1 -> CCR3 = roll1;
		}
		else if(A=='G')//Q backward
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS8;
			TIM1 -> CCR3 = roll1;
		}
	}

	if(A=='q' || A=='Q')//Gripper G g
	{
		if(A=='q')//forward g
		{
			GPIOB -> BSRR |= GPIO_BSRR_BS7;
			GPIOB -> BSRR |= GPIO_BSRR_BS8;
		}
		else if(A=='Q')//Backward G
		{
			GPIOB -> BSRR |= GPIO_BSRR_BS7;
			GPIOB -> BSRR |= GPIO_BSRR_BR8;
		}
	}

	if(A=='p'||A=='P')
	{
		TIM3 -> CR1 |= TIM_CR1_CEN;
		TIM3 -> CCER |= TIM_CCER_CC2E;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_1;
		TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_0;

		if(A=='p')
		{
			servo3++;
			if(servo3>2500)
				servo1=2500;
		}
		if(A=='P')
		{
			servo3--;
			if(servo3<400)
				servo1=400;
		}
	}

	else if(A=='c')
	{
		stopArm();
		TIM3 -> CCR2 = servo3;
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

	timerSetup();

	GPIOSetup();

	UARTSetup();

	UARTSetup1();

	uint32_t A = 0;
	uint32_t B = 0;
	uint32_t count = 0;

	while(1)
	{
		if(count==0)
		{
			USART1 -> CR1 |= USART_CR1_RE;

			emStop();
			A = USART1 -> DR;

			if(A=='l')
				count=1;

			if(A == 'a')
			{
				stopArm();

				uint32_t x = 0;
				uint32_t c1=0;

				for(int i=0;i<11;i++)
				{
					emStop();
					x = USART1 -> DR;
				}

				emStop();
				c1 = USART1 -> DR;

				TIM3 -> CR1 |= TIM_CR1_CEN;
				TIM3 -> CCER |= TIM_CCER_CC3E;
				TIM3 -> CCER |= TIM_CCER_CC4E;

				TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2;
				TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_1;
				TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_0;
				TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_2;
				TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_1;
				TIM3 -> CCMR2 |= TIM_CCMR2_OC4M_0;

				if(c1=='m'||c1=='M'||c1=='c'||c1=='n'||c1=='N')
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
						TIM3 -> CCR3 = servo1;
						TIM3 -> CCR4 = servo2;
					}
					TIM3 -> CCR3 = servo1;
					TIM3 -> CCR4 = servo2;
				}
			}
			else if(A=='r')
			{
				emStop();
				A = USART1 -> DR;

				RoboticArm(A);
			}
		}
		else if(count==1)
		{
			USART2 -> CR1 |= USART_CR1_RE;

			emStop1();
			B = USART2 -> DR;

			if(B=='l')
				count=0;

			if(B == 'a')
				stopArm();

			else if(B=='r')
			{
				emStop1();
				B = USART2 -> DR;

				if(B=='g' || B=='G')//Roll q and Q
				{
					TIM1 -> CR1 |= TIM_CR1_CEN;
					TIM1 -> CCER |= TIM_CCER_CC3NE;

					TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_2;
					TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_1;
					TIM1 -> CCMR2 |= TIM_CCMR2_OC3M_0;

					if(B=='g')//q forward
					{
						GPIOA -> BSRR |= GPIO_BSRR_BR8;
						TIM1 -> CCR3 = 3840;
					}
					else if(B=='G')//Q backward
					{
						GPIOA -> BSRR |= GPIO_BSRR_BS8;
						TIM1 -> CCR3 = 3840;
					}
				}
			}
		}
	}
}
