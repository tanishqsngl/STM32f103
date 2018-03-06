#include "stm32f10x.h"

int servo=1000;

void stopArm(void)
{
	TIM1 -> CCR2 = servo;
	// TIM1 -> CCR3 = 0;
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
	GPIOA -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR5;
	GPIOB -> BSRR |= GPIO_BSRR_BR6;
	GPIOB -> BSRR |= GPIO_BSRR_BR7;
	GPIOB -> BSRR |= GPIO_BSRR_BR8;
	GPIOB -> BSRR |= GPIO_BSRR_BR9;

}

void emStop(void)
{
	long t=0;

	while(!(USART1 -> SR & (1<<5)))
	{
		t++;
		if(t>=8000000)//1 second
		{
			TIM3 -> CCR4 = 2;//FL
			TIM3 -> CCR3 = 2;//FR
			stopArm();
		}
	}
}

void emStop1(void)
{
	long t=0;

	while(!(USART2 -> SR & (1<<5)))
	{
		t++;
		if(t>=8000000)//1 second
		{
			TIM3 -> CCR4 = 2;//FL
			TIM3 -> CCR3 = 2;//FR
			stopArm();
		}
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
	TIM1 -> ARR = 20000;
	TIM1 -> PSC = 72;
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
	GPIOA -> CRL |= GPIO_CRL_MODE1_0;
	GPIOA -> CRL |= (GPIO_CRL_MODE2_0);
	GPIOC -> CRH |= GPIO_CRH_MODE15_0;

	//UART Pins
	GPIOA -> CRH |= (GPIO_CRH_MODE9_0);
	GPIOA -> CRH |= GPIO_CRH_MODE9_1;
	GPIOA -> CRH |= GPIO_CRH_CNF9_1;
	GPIOA -> CRH |= (GPIO_CRH_CNF10_0);

	GPIOA -> CRL |= (GPIO_CRL_CNF3_0);

	//Actuator Pins
	GPIOC -> CRH |= (GPIO_CRH_MODE13_0);
	GPIOC -> CRH |= GPIO_CRH_MODE14_0;

	//Pitch Pins
	GPIOA -> CRL |= (GPIO_CRL_MODE4_0);
	GPIOA -> CRL |= GPIO_CRL_MODE5_0;

	//Roll Pins
	GPIOA -> CRL |= (GPIO_CRL_MODE6_0);
	GPIOA -> CRL |= GPIO_CRL_CNF6_1;
	GPIOA -> CRL |= GPIO_CRL_MODE7_0;
	GPIOA -> CRL |= GPIO_CRL_CNF7_1;

	//Gripper Pins
	GPIOA -> CRH |= (GPIO_CRH_MODE11_0);
	GPIOA -> CRH |= GPIO_CRH_MODE12_0;

	//Swivel Base Pins
	GPIOB -> CRH |= (GPIO_CRH_MODE14_0);
	GPIOB -> CRH |= GPIO_CRH_CNF14_1;
	GPIOB -> CRH |= GPIO_CRH_MODE15_0;
	GPIOB -> CRH |= GPIO_CRH_CNF15_1;

	//Wheel Motor Pins
	GPIOB -> CRL |= (GPIO_CRL_MODE0_0);
	GPIOB -> CRL |= GPIO_CRL_MODE0_1;
	GPIOB -> CRH |= GPIO_CRH_MODE10_0;
	GPIOB -> CRH |= (GPIO_CRH_MODE10_1);
	GPIOB -> CRL |= GPIO_CRL_CNF0_1;
	GPIOB -> CRL |= GPIO_CRL_MODE1_0;
	GPIOB -> CRL |= (GPIO_CRL_MODE1_1);
	GPIOB -> CRH |= GPIO_CRH_MODE11_0;
	GPIOB -> CRH |= (GPIO_CRH_MODE11_1);
	GPIOB -> CRL |= GPIO_CRL_CNF1_1;

	//Camera A8 B56789
	GPIOA -> CRH |= (GPIO_CRH_MODE8_0);
	GPIOB -> CRL |= GPIO_CRL_MODE5_0;
	GPIOB -> CRL |= GPIO_CRL_MODE6_0;
	GPIOB -> CRL |= GPIO_CRL_MODE7_0;
	GPIOB -> CRH |= GPIO_CRH_MODE8_0;
	GPIOB -> CRH |= GPIO_CRH_MODE9_0;
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
	volatile int i=0,j=0;

	time = time*100;
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
	else if(c1=='m'||c1=='M'||c1=='c'||c1=='n'||c1=='N')
	{
		if(c1=='c')
		{
			GPIOA -> BSRR |= GPIO_BSRR_BR8;
			GPIOB -> BSRR |= GPIO_BSRR_BR5;
			GPIOB -> BSRR |= GPIO_BSRR_BR6;
			GPIOB -> BSRR |= GPIO_BSRR_BR7;
		}
	}
}

void RoboticArm(uint32_t A)
{
	uint32_t roll = 0;
	uint32_t roll1 = 0;
	uint16_t servoD = 0;
	uint16_t servoD1 = 0;

	if(A=='s' || A=='S')//s or S Servo
	{
		if(A=='s')//s forward
		{
			servo++;
		}
		else if(A=='S')//S backward
		{
			servo++;
		}
		TIM1 -> CCR1 = servo;
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

	if(A=='b' || A=='B')//B b Up & Down
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

	if(A=='q' || A=='Q')//Rotate q and Q
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
		}
		else if(A=='Q')//Q backward
		{
			TIM3 -> CCR1 = roll1;
			TIM3 -> CCR2 = 32768;
		}
	}

	if(A=='g' || A=='G')//Gripper G g
	{
		if(A=='g')//forward g
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS11;
			GPIOA -> BSRR |= GPIO_BSRR_BR12;
		}
		else if(A=='G')//Backward G
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
	roll = 0;
	roll1 = 0;
	servoD = 0;
	servoD1 = 0;
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

	uint16_t A = 0;

	while(1)
	{
		USART1 -> CR1 |= USART_CR1_RE;

		emStop();
		A = USART1 -> DR;

		if(A == 'a')
		{
			uint32_t x = 0;
			uint32_t y = 0;
			uint32_t x1 = 0;
			uint32_t y1 = 0;
			uint8_t z = 0;
			uint8_t z1 = 0;
			uint8_t w = 0;
			uint8_t w1 = 0;
			uint8_t c1=0;

			stopArm();

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

			motorCode(x1, y1, z1, w1, c1);

			x1=0;
			y1=0;
			z1=0;
			w1=0;
			c1=0;
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
}
