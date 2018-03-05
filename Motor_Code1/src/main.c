#include "stm32f10x.h"

int main(void)
{
	//uint32_t a = 0;
	//uint32_t pAddr = 0x4001244C;
	volatile uint16_t mAddr[2];
	uint32_t y = 0;
	//uint32_t b = 0;
	uint32_t x;

	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;

	//For PWM
	GPIOA -> CRL |= GPIO_CRL_MODE1_0; //setting high speed (and) output
	GPIOA -> CRL |= GPIO_CRL_MODE1_1;
	GPIOA -> CRL |= GPIO_CRL_MODE2_0;
	GPIOA -> CRL |= GPIO_CRL_MODE2_1;
	GPIOA -> CRL &= ~(GPIO_CRL_CNF1_0);//push pull
    GPIOA -> CRL |= GPIO_CRL_CNF1_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);
    GPIOA -> CRL |= GPIO_CRL_CNF2_1;
    GPIOA -> CRL |= GPIO_CRL_MODE0_0; //setting high speed (and) output
    GPIOA -> CRL |= GPIO_CRL_MODE0_1;
    GPIOA -> CRL |= GPIO_CRL_MODE3_0;
    GPIOA -> CRL |= GPIO_CRL_MODE3_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF0_0);//push pull
    GPIOA -> CRL |= GPIO_CRL_CNF0_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF3_0);
    GPIOA -> CRL |= GPIO_CRL_CNF3_1;
    GPIOA -> CRL &= ~(GPIO_CRL_MODE6_0);
    GPIOA -> CRL &= ~(GPIO_CRL_MODE6_1);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF6_0);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF6_1);
    GPIOA -> CRL &= ~(GPIO_CRL_MODE7_0);
    GPIOA -> CRL &= ~(GPIO_CRL_MODE7_1);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF7_0);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF7_1);
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
    AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
    AFIO -> MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0);
    GPIOA -> ODR = 0x00;
    TIM2 -> CR1 |= TIM_CR1_CEN;

//    //Timer Interrupt
//    TIM3 -> CR1 |= TIM_CR1_ARPE;
//    //TIM3 -> CR1 |= TIM_CR1_URS;
//    //TIM3 -> DIER |= TIM_DIER_TIE;
//    //TIM3 -> DIER |= TIM_DIER_UIE;
//    TIM3 -> PSC = 65535;
//    TIM3 -> ARR = 6553;

    //For ADC
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
    ADC1 -> SQR3 |= ADC_SQR3_SQ1_1;
    ADC1 -> SQR3 |= ADC_SQR3_SQ1_2;
    ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_3);
    ADC1 -> SQR3 &= ~(ADC_SQR3_SQ1_4);
    ADC1 -> SQR3 |= (ADC_SQR3_SQ2_0);
    ADC1 -> SQR3 |= ADC_SQR3_SQ2_1;
    ADC1 -> SQR3 |= ADC_SQR3_SQ2_2;
    ADC1 -> SQR3 &= ~(ADC_SQR3_SQ2_3);
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

    while (1)
    {
    	DMA1_Channel1 -> CCR &= ~(DMA_CCR1_EN);
    	DMA1_Channel1 -> CNDTR = 16;
    	ADC1 -> CR2 |= ADC_CR2_ADON;
    	ADC1 -> CR2 |= ADC_CR2_SWSTART;
    	DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
    	while(!(ADC1 -> SR & (1<<1)));
    	y = mAddr[0];
    	x = mAddr[1];
    	//a=x;
    	//b=y;
    	TIM3 -> CR1 |= TIM_CR1_CEN;
    	//TIM2 -> CCR3 = 2047;
    	//TIM2 -> CCR2 = 0;
    	//TIM2 -> CCR1 = 0;
    	//TIM2 -> CCR4 = 0;

    	//Motor Code
    	//center = 2048
    	if(x<2150 && y<2150 && x>1946 && y>1946)//centre
    	{
    		TIM2 -> CCR1 = 0;//FL
    		TIM2 -> CCR2 = 0;//FR
    		TIM2 -> CCR3 = 0;//BL
    		TIM2 -> CCR4 = 0;//BR
    	}
    	//2-Axis
    	else if(x<=2150 && x>=1946 && y>=2150)//forward
    	{
        	TIM2 -> CCR1 = y-2048;//FL
        	TIM2 -> CCR2 = y-2048;//FR
        	TIM2 -> CCR3 = 0;//BL
        	TIM2 -> CCR4 = 0;//BR
    	}
    	else if(x<=2150 && x>=1946 && y<1946)//backward
    	{
    	    TIM2 -> CCR1 = 0;//FL
    	    TIM2 -> CCR2 = 0;//FR
    	    TIM2 -> CCR3 = 2047-y;//BL
    	    TIM2 -> CCR4 = 2047-y;//BR
    	}
//    	else if(y>1946 && y<2150 && x<1946)//Left
//    	{
//    	    TIM2 -> CCR1 = 0;//FL
//    	    TIM2 -> CCR2 = 2047-x;//FR
//    	    TIM2 -> CCR3 = 2047-x;//BL
//    	    TIM2 -> CCR4 = 0;//BR
//    	}
//    	else if(y>1946 && y<2150 && x>2150)//Right
//    	{
//    	    TIM2 -> CCR1 = x-2048;//FL
//    	    TIM2 -> CCR2 = 0;//FR
//    	    TIM2 -> CCR3 = 0;//BL
//    	    TIM2 -> CCR4 = x-2048;//BR
//    	}
//    	else if(x>2150 && y>2150)//Upper-Right
//    	{
//    		if(y>x)//Right of F
//    		{
//    			x=y-x;
//    			//x=x-2048;
//    			TIM2 -> CCR1 = y-2048;//FL
//    			TIM2 -> CCR2 = x;//FR
//    			TIM2 -> CCR3 = 0;//BL
//    			TIM2 -> CCR4 = 0;//BR
//    		}
//    		else//Up of Right
//    		{
//    			y=x-y;
//    			//y=y-2048;
//    			TIM2 -> CCR1 = x-2048;//FL
//    			TIM2 -> CCR2 = 0;//FR
//    			TIM2 -> CCR3 = 0;//BL
//    			TIM2 -> CCR4 = y;//BR
//    		}
//    	}
//    	else if(x<1946 && y>2150)//Upper-Left
//    	{
//    		x=4095-x;
//    		//y=y-2048;
//    		if(y>x)//Left of F
//    		{
//    			x=y-x;
//    			TIM2 -> CCR1 = x;//FL
//    			TIM2 -> CCR2 = y-2048;//FR
//    			TIM2 -> CCR3 = 0;//BL
//    			TIM2 -> CCR4 = 0;//BR
//    		   }
//    		 else
//    		 {
//    			y=x-y;
//    		    TIM2 -> CCR1 = 0;//FL
//    		    TIM2 -> CCR2 = x;//FR
//    		    TIM2 -> CCR3 = y;//BL
//    		    TIM2 -> CCR4 = 0;//BR
//    		 }
//    	}
//    	else if(x<1946 && y<1946)//Bottom-Left
//    	{
//    	    x=4095-x;
//    	    y=4095-y;
//    	    if(y>x)//Left Back
//    	    {
//    	    	x=y-x;
//    	    	TIM2 -> CCR1 = 0;//FL
//    	    	TIM2 -> CCR2 = 0;//FR
//    	    	TIM2 -> CCR3 = y-2048;//BL
//    	    	TIM2 -> CCR4 = x;//BR
//    	    }
//    	    else //Bottom of Left
//    	    {
//    	    	y=x-y;
//    	    	TIM2 -> CCR1 = 0;//FL
//    	    	TIM2 -> CCR2 = y;//FR
//    	    	TIM2 -> CCR3 = x-2048;//BL
//    	    	TIM2 -> CCR4 = 0;//BR
//    	    }
//    	}
//    	else if(x>2150 && y<1946)//Bottom-Right
//    	{
//    	    y=4095-y;
//    	    if(y>x)//Right of Back
//    	    {
//    	    	x=y-x;
//    	    	TIM2 -> CCR1 = 0;//FL
//    	    	TIM2 -> CCR2 = 0;//FR
//    	    	TIM2 -> CCR3 = x;//BL
//    	    	TIM2 -> CCR4 = y-2048;//BR
//    	    }
//    	    else //Bottom of Right
//    	    {
//    	    	y=x-y;
//    	    	TIM2 -> CCR1 = y;//FL
//    	    	TIM2 -> CCR2 = 0;//FR
//    	    	TIM2 -> CCR3 = 0;//BL
//    	    	TIM2 -> CCR4 = x-2048;//BR
//    	    }
//    	}
//    	//if(TIM3 -> CNT > 6000 && (a==x || b==y))
//    	//{
//    	//	TIM2 -> CCR1 = 0;//FL
//    	//	TIM2 -> CCR2 = 0;//FR
//    	//	TIM2 -> CCR3 = 0;//BL
//    	//	TIM2 -> CCR4 = 0;//BR
//    	//}
   }
}
