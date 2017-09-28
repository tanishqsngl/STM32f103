#include "stm32f10x.h"

void emStop(void)
{
	int b = 0;
    TIM2 -> CR1 |= TIM_CR1_ARPE;
    TIM2 -> PSC = 65535;
    TIM2 -> ARR = 1500;
    TIM2 -> CR1 &= ~(TIM_CR1_CEN);

	while(!(USART1 -> SR & (1<<5)))
	{
		TIM2 -> CR1 |= TIM_CR1_CEN;
		b = TIM2 -> CNT;
		if(b >= 1500)
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FR
			TIM1 -> CCR2 = 0;
			TIM1 -> CCR3 = 0;
			GPIOC -> BSRR |= GPIO_BSRR_BR13;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			TIM3 -> CCR1 = 0;
			TIM3 -> CCR2 = 0;
			GPIOA -> BSRR |= GPIO_BSRR_BR11;
			GPIOA -> BSRR |= GPIO_BSRR_BR12;
			GPIOA -> BSRR |= GPIO_BSRR_BR0;
			GPIOA -> BSRR |= GPIO_BSRR_BR1;
			GPIOA -> BSRR |= GPIO_BSRR_BR2;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;
		}
	}
	TIM2 -> CNT = 0;
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
}

void GPIOSetup(void)
{
	//DC Servo Pins
	GPIOA -> CRL |= (GPIO_CRL_MODE0_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE0_1);
	GPIOA -> CRL |= GPIO_CRL_MODE1_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE1_1);
	GPIOA -> CRL |= (GPIO_CRL_MODE2_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE2_1);
	GPIOC -> CRH |= GPIO_CRH_MODE15_0;
	GPIOC -> CRH &= ~(GPIO_CRH_MODE15_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF0_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_1);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF15_0);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF15_1);

	//UART Pins
	GPIOA -> CRH |= (GPIO_CRH_MODE9_0);
	GPIOA -> CRH |= GPIO_CRH_MODE9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOA -> CRH |= GPIO_CRH_CNF9_1;
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_MODE10_1);
	GPIOA -> CRH |= (GPIO_CRH_CNF10_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF10_1);

	//Actuator Pins
	GPIOC -> CRH |= (GPIO_CRH_MODE13_0);
	GPIOC -> CRH &= ~(GPIO_CRH_MODE13_1);
	GPIOC -> CRH |= GPIO_CRH_MODE14_0;
	GPIOC -> CRH &= ~(GPIO_CRH_MODE14_1);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF13_0);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF13_1);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF14_0);
	GPIOC -> CRH &= ~(GPIO_CRH_CNF14_1);

	//Pitch Pins
	GPIOA -> CRL |= (GPIO_CRL_MODE4_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE4_1);
	GPIOA -> CRL |= GPIO_CRL_MODE5_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE5_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF4_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF4_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF5_0);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF5_1);

	//Roll Pins
	GPIOA -> CRL |= (GPIO_CRL_MODE6_0);
	GPIOA -> CRL &= ~(GPIO_CRL_MODE6_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF6_0);
	GPIOA -> CRL |= GPIO_CRL_CNF6_1;
	GPIOA -> CRL |= GPIO_CRL_MODE7_0;
	GPIOA -> CRL &= ~(GPIO_CRL_MODE7_1);
	GPIOA -> CRL &= ~(GPIO_CRL_CNF7_0);
	GPIOA -> CRL |= GPIO_CRL_CNF7_1;

	//Gripper Pins
	GPIOA -> CRH |= (GPIO_CRH_MODE11_0);
	GPIOA -> CRH &= ~(GPIO_CRH_MODE11_1);
	GPIOA -> CRH |= GPIO_CRH_MODE12_0;
	GPIOA -> CRH &= ~(GPIO_CRH_MODE12_1);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF11_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF11_1);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF12_0);
	GPIOA -> CRH &= ~(GPIO_CRH_CNF12_1);

	//Swivel Base Pins
	GPIOB -> CRH |= (GPIO_CRH_MODE14_0);
	GPIOB -> CRH &= ~(GPIO_CRH_MODE14_1);
	GPIOB -> CRH &= ~(GPIO_CRH_CNF14_0);
	GPIOB -> CRH |= GPIO_CRH_CNF14_1;
	GPIOB -> CRH |= GPIO_CRH_MODE15_0;
	GPIOB -> CRH &= ~(GPIO_CRH_MODE15_1);
	GPIOB -> CRH &= ~(GPIO_CRH_CNF15_0);
	GPIOB -> CRH |= GPIO_CRH_CNF15_1;
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
	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	GPIOA -> BSRR |= GPIO_BSRR_BS2;
	GPIOC -> BSRR |= GPIO_BSRR_BR15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BR1;
	GPIOA -> BSRR |= GPIO_BSRR_BS2;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BS0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	GPIOA -> BSRR |= GPIO_BSRR_BR2;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;

	Delay(aDelay);

	GPIOA -> BSRR |= GPIO_BSRR_BR0;
	GPIOA -> BSRR |= GPIO_BSRR_BS1;
	GPIOA -> BSRR |= GPIO_BSRR_BS2;
	GPIOC -> BSRR |= GPIO_BSRR_BS15;

	Delay(aDelay);
}

uint16_t map(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e)
{
  return (a-b)*(e-d)/(c-b) + d;
}

void Delay(int time)
{
	volatile int i,j;

	time = time*100;
	for (i=0;i<time;i++)
		j++;
}

int main()
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
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

	uint16_t sBase = 0;
	uint16_t sBase1 = 0;
	uint32_t roll = 0;
	uint32_t roll1 = 0;
	uint16_t servoD = 0;
	uint16_t servoD1 = 0;
	uint16_t A = 0;
	//uint16_t act=0;

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_RE;

		emStop();
		A = USART1 -> DR;

		if(A=='r')
		{
			emStop();
			A = USART1 -> DR;

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
					TIM1 -> CCR2 = sBase1;
					TIM1 -> CCR3 = 0;

					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
				else if(A=='S')//S backward
				{
					TIM1 -> CCR2 = sBase1;
					TIM1 -> CCR3 = 32768;

					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
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
				servoD1 = servoD1*40;

				if(A=='t')//t
				{
					//DC Servo forward A0 A1 A2 C15
					DCServoF(servoD1);

					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
				}

				else if(A=='T')//T
				{
					//DC Servo backward
					DCServoB(servoD1);

					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
				}
			}

			if(A=='b' || A=='B')//B b
			{
				if(A=='b')//b forward
				{
					GPIOC -> BSRR |= GPIO_BSRR_BS13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;

					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
				}
				else if(A=='B')//B backward
				{
					GPIOC -> BSRR |= GPIO_BSRR_BS13;
					GPIOC -> BSRR |= GPIO_BSRR_BS14;

					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
				}
			}

			if(A=='p' || A=='P')//Pitch p and P
			{
				if(A=='p')//forward
				{
					GPIOA -> BSRR |= GPIO_BSRR_BS4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}

				else if(A=='P')//Backward
				{
					GPIOA -> BSRR |= GPIO_BSRR_BS4;
					GPIOA -> BSRR |= GPIO_BSRR_BS5;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
			}

			if(A=='q' || A=='Q')//Roll q and Q
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

				if(A=='q')//q forward
				{
					TIM3 -> CCR1 = roll1;
					TIM3 -> CCR2 = 0;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
				else if(A=='Q')//Q backward
				{
					TIM3 -> CCR1 = roll1;
					TIM3 -> CCR2 = 32768;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					GPIOA -> BSRR |= GPIO_BSRR_BR11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
			}

			if(A=='g' || A=='G')//Gripper G g
			{
				if(A=='g')//forward g
				{
					GPIOA -> BSRR |= GPIO_BSRR_BS11;
					GPIOA -> BSRR |= GPIO_BSRR_BR12;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
				else if(A=='G')//Backward G
				{
					GPIOA -> BSRR |= GPIO_BSRR_BS11;
					GPIOA -> BSRR |= GPIO_BSRR_BS12;

					TIM1 -> CCR2 = 0;
					TIM1 -> CCR3 = 0;
					GPIOC -> BSRR |= GPIO_BSRR_BR13;
					GPIOC -> BSRR |= GPIO_BSRR_BR14;
					GPIOA -> BSRR |= GPIO_BSRR_BR4;
					GPIOA -> BSRR |= GPIO_BSRR_BR5;
					TIM3 -> CCR1 = 0;
					TIM3 -> CCR2 = 0;
					GPIOA -> BSRR |= GPIO_BSRR_BR0;
					GPIOA -> BSRR |= GPIO_BSRR_BR1;
					GPIOA -> BSRR |= GPIO_BSRR_BR2;
					GPIOC -> BSRR |= GPIO_BSRR_BR15;
				}
			}
			sBase = 0;
			sBase1 = 0;
			roll = 0;
			roll1 = 0;
			servoD = 0;
			servoD1 = 0;
		}

		else
		{
			TIM3 -> CCR4 = 0;//FL
			TIM3 -> CCR3 = 0;//FR
			TIM1 -> CCR2 = 0;
			TIM1 -> CCR3 = 0;
			GPIOC -> BSRR |= GPIO_BSRR_BR13;
			GPIOC -> BSRR |= GPIO_BSRR_BR14;
			GPIOA -> BSRR |= GPIO_BSRR_BR4;
			GPIOA -> BSRR |= GPIO_BSRR_BR5;
			TIM3 -> CCR1 = 0;
			TIM3 -> CCR2 = 0;
			GPIOA -> BSRR |= GPIO_BSRR_BR11;
			GPIOA -> BSRR |= GPIO_BSRR_BR12;
			GPIOA -> BSRR |= GPIO_BSRR_BR0;
			GPIOA -> BSRR |= GPIO_BSRR_BR1;
			GPIOA -> BSRR |= GPIO_BSRR_BR2;
			GPIOC -> BSRR |= GPIO_BSRR_BR15;
		}
	}
}
