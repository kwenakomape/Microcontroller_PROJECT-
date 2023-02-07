//********************************************************************
//*                    EEE2046F C template                           *
//*==================================================================*
//* WRITTEN BY:    	                 		                         *
//* DATE CREATED:                                                    *
//* MODIFIED:                                                        *
//*==================================================================*
//* PROGRAMMED IN: Atollic True Studio                               *
//* TARGET:        STM32F0                                           *
//*==================================================================*
//* DESCRIPTION:                                                     *
//*                                                                  *
//********************************************************************
// INCLUDE FILES
//====================================================================
#include "stm32f0xx.h"
//====================================================================
// GLOBAL CONSTANTS
//====================================================================
#define DELAY1 = 13
#define DELAY2 = 65535
#define TRUE = 1
#define FALSE = 0
//====================================================================
// GLOBAL VARIABLES
//====================================================================
uint8_t bitpattern1 = 0b00000000;
uint8_t bitpattern2 = 0b11111111;
uint8_t bitpattern3 = 0b10101010;
uint8_t startFlag = 0;
uint8_t firstFlag =0;
uint8_t secondFlag =0;
uint8_t thirdFlag =0;
//====================================================================
// FUNCTION DECLARATIONS
void initGPIO(void);
void delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);
//====================================================================

//====================================================================
// MAIN FUNCTION
//====================================================================
int main (void)
{
	initGPIO();
	for(;;){
		checkPB();
	}



}
// End of main
void initGPIO(void){
	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN; //enabling clock for GPIOB

    // Clear mode register for the PB0-PB7
	GPIOB ->MODER &=~ (GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3|GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6|GPIO_MODER_MODER7);

	//Set PB0-PB7 to as output
	GPIOB ->MODER |= (GPIO_MODER_MODER0_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER1_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER2_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER3_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER4_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER5_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER6_0);
	GPIOB ->MODER |= (GPIO_MODER_MODER7_0);

	//Turn off LEDS(D0-D7)
	GPIOB->ODR &= ~(GPIO_ODR_0|GPIO_ODR_1|GPIO_ODR_2|GPIO_ODR_3|GPIO_ODR_4|GPIO_ODR_5|GPIO_ODR_6|GPIO_ODR_7);

	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN; // enabling clock for GPIOA
	//Set PA0-PA3 as to input
	GPIOA ->MODER &=~ (GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3);

	//Enable pull up resistor for PA0-PA3
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR0_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR1_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR2_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR3_0;

}
//====================================================================
// FUNCTION DEFINITIONS
//====================================================================
void delay(void){
	volatile int i,j;
	for(i=0;i<=13;i++){
		for(j=0;j<=65535;j++);
	}
}
void checkPB(void){
	if((GPIOA->IDR & GPIO_IDR_0)==0){
		startFlag = 1;
		firstFlag =0;
		secondFlag =0;
		thirdFlag =0;


	}
	else if((GPIOA->IDR & GPIO_IDR_1)==0){
		startFlag = 1;
		firstFlag =1;
		secondFlag =0;
		thirdFlag =0;
		display();
	}
	else if((GPIOA->IDR & GPIO_IDR_2)==0){
		startFlag = 1;
		firstFlag =0;
		secondFlag =1;
		thirdFlag =0;

	}
	else if((GPIOA->IDR & GPIO_IDR_3)==0){
		startFlag = 1;
		firstFlag =0;
		secondFlag =0;
		thirdFlag =1;

	}
	display();

}

void display(){
	if(startFlag==1){
		GPIOB->ODR &= ~(GPIO_ODR_0|GPIO_ODR_1|GPIO_ODR_2|GPIO_ODR_3|GPIO_ODR_4|GPIO_ODR_5|GPIO_ODR_6|GPIO_ODR_7);
		GPIOB->ODR|= GPIO_ODR_0;

	}
	if(startFlag==1 && firstFlag==1 ){
		firstDisplay();
	}

	if(startFlag==1 && secondFlag==1 ){
		secondDisplay();
	}

	if(startFlag==1 && thirdFlag==1 ){
		thirdDisplay();
	}

}

void firstDisplay(void){

	GPIOB->ODR &= ~(GPIO_ODR_0|GPIO_ODR_1|GPIO_ODR_2|GPIO_ODR_3|GPIO_ODR_4|GPIO_ODR_5|GPIO_ODR_6|GPIO_ODR_7);
	GPIOB->ODR = bitpattern1;
	delay();
	GPIOB->ODR = bitpattern2;
	delay();
	GPIOB->ODR = bitpattern3;
	delay();

}

void secondDisplay(void){
	GPIOB->ODR &= ~(GPIO_ODR_0|GPIO_ODR_1|GPIO_ODR_2|GPIO_ODR_3|GPIO_ODR_4|GPIO_ODR_5|GPIO_ODR_6|GPIO_ODR_7);
	GPIOB->ODR|= (GPIO_ODR_0);
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_0);
	GPIOB->ODR|= GPIO_ODR_1;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_1);
	GPIOB->ODR|= GPIO_ODR_2;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_2);
	GPIOB->ODR|= GPIO_ODR_3;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_3);
	GPIOB->ODR|= GPIO_ODR_4;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_4);
	GPIOB->ODR|= GPIO_ODR_5;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_5);
	GPIOB->ODR|= GPIO_ODR_6;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_6);
	GPIOB->ODR|= GPIO_ODR_7;
	delay();
	GPIOB->ODR &= ~(GPIO_ODR_7);

}
void thirdDisplay(){
	GPIOB->ODR &= ~(GPIO_ODR_0|GPIO_ODR_1|GPIO_ODR_2|GPIO_ODR_3|GPIO_ODR_4|GPIO_ODR_5|GPIO_ODR_6|GPIO_ODR_7);
	for (uint8_t bit =0b00000000;bit<0b11111111;bit++){
		GPIOB -> ODR = bit;
		delay();
	}
}
//********************************************************************
// END OF PROGRAM
//********************************************************************
