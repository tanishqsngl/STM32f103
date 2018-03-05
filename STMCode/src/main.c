#include "stm32f10x.h"

	void clock();
	void gpio();
	void usartinit();
	void timersetup();
	void timerenable();
	void delay(int time);
	void roboticarm();
	void motorcodecytron1();
	void motorcodecytron2();
	void motorcodecytronv2(int xval,int yval,int gear_final,int val360);
	void stepper(int dir,int gear_stepper);//a=step selection, direction = 1(anti-clockwise), 2(clockwise)
	void ultrasonic3();
	void transmit1(char data);
	void transmit2(char data);
	void off();
	uint16_t receive1();
	uint16_t receive2();


	//motorcode
	uint16_t xval,yval;
	double rightm,leftm;
	uint16_t gear[2],gear_final;
	uint16_t val360=2;

	//usart
	uint16_t bit[8];
	uint16_t bita,val;
	int j=0;
	uint16_t ch3,ch4;

	//ultrasonic
	int count1=0,count2=0,value;

	//autonomous
	int flag = 0;

int main(void)
{
	clock();
	gpio();
	usartinit();
	timersetup();
	timerenable();
	delay(500000);
    while(1)
    {

    	if(flag == 0)
    	{
    		val = receive1();
    		if(val == 'A')
    		{
    			motorcodecytron1();
    		}
    		else if(val == 'G')
    		{
    			roboticarm();
    		}
    		else if(val == 'N')
    		{
    			GPIOB->BRR = 1<<10;
    			GPIOB->BRR = 1<<11;
    			TIM3->CCR3 = 1; TIM3->CCR4 = 1;
    			flag = 1;
    		}
    	}
    	else if(flag == 1)
    	{
    		val = receive2();
    		if(val == 'A')
       		{
      			motorcodecytron2();
      		}
    		else if(val == 'N')
    		{
    			flag = 0;
    		}
    	}
   	}
}

void off()
{
	//DC Servo OFF checked
	GPIOA->BRR = 1<<0;
	GPIOA->BRR = 1<<1;
	GPIOA->BRR = 1<<2;
	GPIOC->BRR = 1<<15;

	//Pitch
	GPIOA->BRR = 1<<4;
	GPIOA->BRR = 1<<5;

	//Swivel
	TIM3->CCR1 = 1;//A6
	TIM3->CCR2 = 1;//A7

	//Camera M1
	GPIOA->BRR = 1<<8;
	GPIOB->BRR = 1<<5;

	//Gripper
	GPIOA->BRR = 1<<11;
	GPIOA->BRR = 1<<12;

	//Camera M2
	GPIOB->BRR = 1<<6;
	GPIOB->BRR = 1<<7;

	//Camera M3
	GPIOB->BRR = 1<<8;
	GPIOB->BRR = 1<<9;

	//Roll
	GPIOB->BRR = 1<<14;
	GPIOB->BRR = 1<<15;

	//Actuator
	GPIOC->BRR = 1<<13;
	GPIOC->BRR = 1<<14;
}

void roboticarm()
{//PA4,5,,11,12,, PD2,3,  PC11,12  PD0,1

	gear[1] = receive1() - 48;
	gear[0] = receive1() - 48;
	bita = receive1();
	gear_final =  89 - ((gear[1]*10) + gear[0] - 10);
		if(gear_final<0)//safety of dividing by zero or negatives
			gear_final = 0;
		if(gear_final>89)
			gear_final = 89;

	if(bita == 's')
	{
		off();
	}
	if(bita == 'f')//1st tested
	{
		//Roll
		GPIOB->BSRR = 1<<14;
		GPIOB->BRR = 1<<15;
	}
	if(bita == 'F')
	{
		//Roll
		GPIOB->BRR = 1<<14;
		GPIOB->BSRR = 1<<15;
	}
	if(bita == 'q')//2nd tested
	{
		//Gripper
		GPIOA->BSRR = 1<<11;
		GPIOA->BRR = 1<<12;
	}
	if(bita == 'Q')
	{
		//Gripper
		GPIOA->BRR = 1<<11;
		GPIOA->BSRR = 1<<12;
	}
	if(bita == 'o')//3rd DC Servo
	{
		for(int j=0;j<2;j++)
		{
			stepper(1,gear_final);
		}
	}
	if(bita == 'O')
	{
		for(int k=0;k<2;k++)
		{
			stepper(2,gear_final);
		}
	}
	if(bita == 'm')//4th
	{
		//Pitch
		GPIOA->BSRR = 1<<4;
		GPIOA->BRR = 1<<5;
	}
	if(bita == 'M')
	{
		//Pitch
		GPIOA->BRR = 1<<4;
		GPIOA->BSRR = 1<<5;
	}
	if(bita == 'i')//5th
	{
		//Actuator
		GPIOC->BSRR = 1<<13;
		GPIOC->BRR = 1<<14;
	}
	if(bita == 'I')
	{
		//Actuator
		GPIOC->BRR = 1<<13;
		GPIOC->BSRR = 1<<14;
	}
	if(bita == 'k')//5th
	{
		//Swivel
		TIM3->CCR1 = 736*gear_final;;//A6
		TIM3->CCR2 = 1;//A7
	}
	if(bita == 'K')
	{
		//Swivel
		TIM3->CCR1 = 1;//A6
		TIM3->CCR2 = 736*gear_final;;//A7
	}

	//camera
	if(bita == 'U')
	{
		//Camera 1
		GPIOA->BSRR = 1<<8;
		GPIOB->BRR = 1<<5;
	}
	if(bita == 'D')
	{
		//Camera 1
		GPIOA->BRR = 1<<8;
		GPIOB->BSRR = 1<<5;
	}
	if(bita == 'L')
	{
		//Camera 2
		for(int p=0;p<50;p++)
		{
			GPIOB->BSRR = 1<<6;
			GPIOB->BRR = 1<<7;
			delay(2000);
			GPIOB->BRR = 1<<6;
			delay(1000);
		}
	}
	if(bita == 'R')
	{
		//Camera 3
		for(int p=0;p<50;p++)
		{
			GPIOB->BRR = 1<<6;
			GPIOB->BSRR = 1<<7;
			delay(2000);
			GPIOB->BRR = 1<<7;
			delay(1000);
		}
	}
}

void motorcodecytronv2(int xval,int yval,int gear_final,int val360)
{
	if((xval<2300) && (xval>1700) && (yval<2300) && (yval>1700))//CENTRE
	{
		if(val360 == 2)
		{
			GPIOB->BRR = 1<<10;
			GPIOB->BRR = 1<<11;
			TIM3->CCR3 = 1; TIM3->CCR4 = 1;
		}
		else
		{
			if(val360 == 1)
			{
				GPIOB->BRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
			else if(val360 ==3)
			{
				GPIOB->BSRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
		}
	}
	else
	{
		if(yval>2048)
		{
			if(xval>1700&&xval<2350)
			{
				leftm = ((yval-2048)*0.7187);
				rightm =((yval-2048)*0.7187);
				GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
		else
		{
			if(xval>2048)				//Quadrant 1
			{
				if(yval>xval)
				{
					leftm = ((yval-2048)*0.7187);
					rightm = ((yval-2048)*0.7187) - ((xval-2048)*0.5703);
				}
				else
				{
					leftm = ((xval-2048)*0.7187);
					rightm =((yval-2048)*0.1483);
				}

				GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
				else						//Quadrant 2
				{
					if((yval-2048)>(2048-xval))
					{
						leftm = ((yval-2048)*0.7187) - ((2048-xval)*0.5703);
						rightm = ((yval-2048)*0.7187);
					}
					else
					{
						leftm = ((yval-2048)*0.1483);
						rightm =((2048-xval)*0.7187);
					}
					GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
					TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
			}
		}
		else
		{
			if(xval>1800&&xval<2200)				//Quadrant 3 & 4
			{
				leftm = ((2048-yval)*0.7187);
				rightm = ((2048-yval)*0.7187);

				GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
			else
			{
				if(xval>2199)
				{
					if((xval-2048)<(2048-yval))
					{
						leftm = ((2048-yval)*0.7187);
						rightm = ((2048-yval)-(xval-2048))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
				}
				else if(xval<1801)
				{
					if((2048-xval)<(2048-yval))
					{
						rightm = ((2048-yval)*0.7187);
						leftm = ((2048-yval)-(2048-xval))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
				}
				else
				{
					GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
					TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
				}
			}
		}
	}
}


void motorcodecytron1()
{
	/*
	PB10 = left
	PB11 = right
	Timer 3 Channel 3 : left
	Timer 3 Channel 4 : right
	*/
		//DATA RECEPTION
	bit[7] = receive1() - 48;
	bit[6] = receive1() - 48;
	bit[5] = receive1() - 48;
	bit[4] = receive1() - 48;

	bit[3] = receive1() - 48;
	bit[2] = receive1() - 48;
	bit[1] = receive1() - 48;
	bit[0] = receive1() - 48;

	gear[1] = receive1() - 48;
	gear[0] = receive1() - 48;
	val360 = receive1() - 48;

	xval = (bit[7]*1000)+(bit[6]*100)+(bit[5]*10)+bit[4];
	yval = (bit[3]*1000)+(bit[2]*100)+(bit[1]*10)+bit[0];
	gear_final =  89 - ((gear[1]*10) + gear[0] - 10);
	if(gear_final<0)//safety of dividing by zero or negatives
		gear_final = 0;
	if(gear_final>89)
		gear_final = 89;


	if((xval<2200) && (xval>1700) && (yval<2200) && (yval>1700))//CENTRE
	{
		if(val360 == 2)
		{
			GPIOB->BRR = 1<<10;
			GPIOB->BRR = 1<<11;
			TIM3->CCR3 = 1; TIM3->CCR4 = 1;
		}
		else
		{
			if(val360 == 1)
			{
				GPIOB->BRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
			else if(val360 ==3)
			{
				GPIOB->BSRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
		}
	}
	else
	{
		if(yval>2048)
		{
			if(xval>1800&&xval<2200)
			{
				leftm = ((yval-2048)*0.7187);
				rightm =((yval-2048)*0.7187);
				GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
			else
			{
				if(xval>2048)				//Quadrant 1
				{
					if(yval>xval)
					{
						leftm = ((yval-2048)*0.7187);
						rightm = ((yval-2048)*0.7187) - ((xval-2048)*0.5703);
					}
					else
					{
						leftm = ((xval-2048)*0.7187);
						rightm =((yval-2048)*0.1483);
					}

					GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
					TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
				else						//Quadrant 2
				{
					if((yval-2048)>(2048-xval))
					{
						leftm = ((yval-2048)*0.7187) - ((2048-xval)*0.5703);
						rightm = ((yval-2048)*0.7187);
					}
					else
					{
						leftm = ((yval-2048)*0.1483);
						rightm =((2048-xval)*0.7187);
					}
					GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
					TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
			}
		}
		else
		{
			if(xval>1800&&xval<2200)				//Quadrant 3 & 4
			{
				leftm = ((2048-yval)*0.7187);
				rightm = ((2048-yval)*0.7187);

				GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
			else
			{
				if(xval>2199)
				{
					if((xval-2048)<(2048-yval))
					{
						leftm = ((2048-yval)*0.7187);
						rightm = ((2048-yval)-(xval-2048))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
					else
					{
						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
					}
				}
				else if(xval<=1800)
				{
					if((2048-xval)<(2048-yval))
					{
						rightm = ((2048-yval)*0.7187);
						leftm = ((2048-yval)-(2048-xval))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
					else
					{
						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
					}
				}
				else
				{
					GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
					TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
				}
			}
		}
	}
}


void motorcodecytron2()
{
	/*
	PB10 = left
	PB11 = right
	Timer 3 Channel 3 : left
	Timer 3 Channel 4 : right
	*/
		//DATA RECEPTION
	bit[7] = receive2() - 48;
	bit[6] = receive2() - 48;
	bit[5] = receive2() - 48;
	bit[4] = receive2() - 48;

	bit[3] = receive2() - 48;
	bit[2] = receive2() - 48;
	bit[1] = receive2() - 48;
	bit[0] = receive2() - 48;

	gear[1] = receive2() - 48;
	gear[0] = receive2() - 48;
	val360 = receive2() - 48;

	xval = (bit[7]*1000)+(bit[6]*100)+(bit[5]*10)+bit[4];
	yval = (bit[3]*1000)+(bit[2]*100)+(bit[1]*10)+bit[0];
	gear_final =  89 - ((gear[1]*10) + gear[0] - 10);
	if(gear_final<0)//safety of dividing by zero or negatives
		gear_final = 0;
	if(gear_final>89)
		gear_final = 89;


	if((xval<2200) && (xval>1800) && (yval<2200) && (yval>1800))//CENTRE
	{
		if(val360 == 2)
		{
			GPIOB->BRR = 1<<10;
			GPIOB->BRR = 1<<11;
			TIM3->CCR3 = 1; TIM3->CCR4 = 1;
		}
		else
		{
			if(val360 == 1)
			{
				GPIOB->BRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
			else if(val360 ==3)
			{
				GPIOB->BSRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = 736*gear_final; 	TIM3->CCR4 = 736*gear_final;
			}
		}
	}
	else
	{
		if(yval>2048)
		{
			if(xval>1800&&xval<2200)
			{
				leftm = ((yval-2048)*0.7187);
				rightm =((yval-2048)*0.7187);
				GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
			else
			{
				if(xval>2048)				//Quadrant 1
				{
					if(yval>xval)
					{
						leftm = ((yval-2048)*0.7187);
						rightm = ((yval-2048)*0.7187) - ((xval-2048)*0.5703);
					}
					else
					{
						leftm = ((xval-2048)*0.7187);
						rightm =((yval-2048)*0.1483);
					}

					GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
					TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
				else						//Quadrant 2
				{
					if((yval-2048)>(2048-xval))
					{
						leftm = ((yval-2048)*0.7187) - ((2048-xval)*0.5703);
						rightm = ((yval-2048)*0.7187);
					}
					else
					{
						leftm = ((yval-2048)*0.1483);
						rightm =((2048-xval)*0.7187);
					}
					GPIOB->BSRR = 1<<10;			GPIOB->BSRR = 1<<11;
					TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
				}
			}
		}
		else
		{
			if(xval>1900&&xval<2200)				//Quadrant 3 & 4
			{
				leftm = ((2048-yval)*0.7187);
				rightm = ((2048-yval)*0.7187);

				GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
				TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
			}
			else
			{
				if(xval>2199)
				{
					if((xval-2048)<(2048-yval))
					{
						leftm = ((2048-yval)*0.7187);
						rightm = ((2048-yval)-(xval-2048))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
					else
					{
						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
					}
				}
				else if(xval<=1900)
				{
					if((2048-xval)<(2048-yval))
					{
						rightm = ((2048-yval)*0.7187);
						leftm = ((2048-yval)-(2048-xval))*0.7187;

						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = leftm*gear_final; 	TIM3->CCR4 = rightm*gear_final;
					}
					else
					{
						GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
						TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
					}
				}
				else
				{
					GPIOB->BRR = 1<<10;			GPIOB->BRR = 1<<11;
					TIM3->CCR3 = 1; 	TIM3->CCR4 = 1;
				}
			}
		}
	}
}
void ultrasonic3()
 {
	//iteration1 PA0 PB12
	//left side ultrasonic
	int flag1 = 0,flag2 = 0;
	GPIOA->BSRR = 1<<0;
	delay(70);
	GPIOA->BRR = 1<<0;
	count1 = 0;

	while(!((GPIOB->IDR)&(1<<12)))
	{
	}

	while(((GPIOB->IDR)&(1<<12)))
	{
	    count1++;
	}

	if(count1<6000)//controls the range
	{
		flag1 = 1;
	}

	if(count1>=6000)
	{
		flag1 = 0;
	}

	//iteration2 PA1 PB13
	//right side ultrasonic
	GPIOA->BSRR = 1<<1;
	delay(70);
	GPIOA->BRR = 1<<1;
	count2=0;

	while(!((GPIOB->IDR)&(1<<13)))
	{
	}
	while(((GPIOB->IDR)&(1<<13)))
	{
		count2++;
	}
	if(count2<6000)//controls the range
	{
		flag2 = 1;
	}
	if(count2>=6000)
	{
		flag2 = 0;
	}

	if(flag1 == 1)
	{
		motorcodecytronv2(2048,2048,2,3);
		delay(3000000);
	}
	else if(flag2 == 1)
	{
		motorcodecytronv2(2048,2048,2,1);
		delay(3000000);
	}
	else
	{
		motorcodecytronv2(2048,2800,3,2);
		delay(3000000);
	}
}

void stepper(int dir,int gear_stepper)
{
	if(dir==1)
	{
		GPIOA->BSRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BSRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BRR = 1<<0;
		GPIOA->BSRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BSRR = 1<<15;

		delay(100*gear_stepper);
	}
	else if(dir==2)
	{
		GPIOA->BRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BSRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BRR = 1<<0;
		GPIOA->BSRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BSRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

		GPIOA->BSRR = 1<<0;
		GPIOA->BRR = 1<<1;
		GPIOA->BRR = 1<<2;
		GPIOC->BRR = 1<<15;

		delay(100*gear_stepper);

	}
}

void clock()//finalized
{
	RCC->APB2ENR|=(1<<0)|(1<<2)|(1<<3)|(1<<4);//AFIO,IOPA,B,C
	RCC->APB2ENR|=(1<<11)|(1<<14);//TIM1,USART1
	RCC->APB1ENR|=(1<<1)|(1<<2)|(1<<17);//TIM3,TIM4,USART2
}

void gpio()
{
	GPIOA->CRL = 0xBB338333;
	GPIOA->CRH = 0x000338B3;
	GPIOB->CRL = 0x333333BB;
	GPIOB->CRH = 0x33883333;
	GPIOC->CRH = 0x33333333;
}
void usartinit()
{
	USART1->CR1|=(1<<13);
	delay(100);
	//assigns a baud rate of 9600
	USART1->BRR=SystemCoreClock/9600;
	//1 start/stop bit, 8 data bits
	USART1->CR1&=~(1<<12);
	USART1->CR2&=~(1<<12)&~(1<<13);
	//receiver enable
	USART1->CR1|=(1<<2)|(1<<3);

	USART2->CR1|=(1<<13);
	delay(100);
	//assigns a baud rate of 9600
	USART2->BRR=SystemCoreClock/19200;
	//1 start/stop bit, 8 data bits
	USART2->CR1&=~(1<<12);
	USART2->CR2&=~(1<<12)&~(1<<13);
	//receiver enable
	USART2->CR1|=(1<<2)|(1<<3);
}

void timersetup1()
{
	TIM3->CR1|=(1<<7);
		TIM3->CR1&=~(1<<1);

		//sets channel 1,2,3,4 as output
	//	TIM3->SMCR |=(1<<14);//external clock
		TIM3->CCMR1|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
		TIM3->CCMR1&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
		TIM3->CCMR2|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
		TIM3->CCMR2&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
		TIM3->PSC = 0;

		//generates waveform on pin
		TIM3->CCER|=(1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<9)|(1<<8)|(1<<12)|(1<<13);

	TIM4->CR1|=(1<<7);
	TIM4->CR1&=~(1<<1);

	//sets channel 1,2,3,4 as output
	//TIM3->SMCR |=(1<<14);//external clock
	TIM4->CCMR1|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM4->CCMR1&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM4->CCMR2|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM4->CCMR2&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM4->PSC = 21;

	//generates waveform on pin
	TIM4->CCER|=(1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<9)|(1<<8)|(1<<12)|(1<<13);

}

void timersetup()
{
	TIM3->CR1|=(1<<7);
	TIM3->CR1&=~(1<<1);
	//sets channel 1,2,3,4 as output
	//TIM3->SMCR |=(1<<14);//external clock
	TIM3->CCMR1|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM3->CCMR1&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM3->CCMR2|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM3->CCMR2&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM3->PSC = 0;
	//generates waveform on pin
	TIM3->CCER|=(1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<9)|(1<<8)|(1<<12)|(1<<13);

	TIM4->CR1|=(1<<7);
	TIM4->CR1&=~(1<<1);
	//sets channel 1,2,3,4 as output
	//TIM3->SMCR |=(1<<14);//external clock
	TIM4->CCMR1|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM4->CCMR1&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM4->CCMR2|=(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
	TIM4->CCMR2&=~(1<<8)&~(1<<9)&~(1<<0)&~(1<<1);
	TIM4->PSC = 21;
	//generates waveform on pin
	TIM4->CCER|=(1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<9)|(1<<8)|(1<<12)|(1<<13);

}

void timerenable()
{
	TIM3->CR1|=(1<<0);
	TIM4->CR1|=(1<<0);
}

void transmit1(char data)
{
	USART1->DR = data;

	while(!((USART1->SR)&(1<<7)))
	{}
}

void transmit2(char data)
{
	USART2->DR = data;

	while(!((USART2->SR)&(1<<7)))
	{}
}

uint16_t receive1()
{

	j=0;
	ch3 = TIM3->CCR3;
	ch4 = TIM3->CCR4;

	while(!((USART1->SR)&(1<<5)))
	{

		j++;

		if(j==4000000)
		{
			off();
			while((ch3>1) && (ch4>1))
			{
				ch3 = ch3/2;ch4 = ch4/2;

				TIM3->CCR3 = ch3; TIM3->CCR4 = ch4;
				delay(500000);

			}
			j=0;
		}

	}
	value =(USART1->DR);

	return value;
}

uint16_t receive2()
{
	j = 0;

	ch3 = TIM3->CCR3;
	ch4 = TIM3->CCR4;

	while(!((USART2->SR)&(1<<5)))
	{
		j++;
		if(j==4000000)
		{
			while((ch3>1) && (ch4>1))
			{
				ch3 = ch3/2;ch4 = ch4/2;

				TIM3->CCR3 = ch3; TIM3->CCR4 = ch4;
				delay(500000);
			}
			j=0;
		}
	}
	value =(USART2->DR);

	return value;
}


void delay(int time)//8000000=1sec
{
	for(int i=0;i<time;i++)
	{}
}


