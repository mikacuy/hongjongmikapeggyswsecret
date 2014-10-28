/******************************************************************
 * Robotics team Software Tutorial 2015 #1						  *
 * Example : change state of LED(RED) when button(up) is triggered  *
 ******************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <delay.h>
#include <ticks.h>
#include "stm32f10x.h"

#define BUT_UP  GPIO_Pin_7 //find and replace (BUT_UP = GPIO_Pin_7)
#define BUT_DOWN GPIO_Pin_8
#define LED_ON 0
#define LED_OFF 1
#define LED_RED GPIO_Pin_6
#define LED_GREEN GPIO_Pin_7
#define LED_BLUE GPIO_Pin_7
#define MECH_SW GPIO_Pin_0
#define Light_Sensor GPIO_Pin_15

int counter = 1;
int time = 0;
int flash = 0;

//initialize joy stick
void button_init(void){

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//INPUT pin
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_InitStructure.GPIO_Pin = BUT_UP;
	//GPIO_InitStructure.GPIO_Pin = BUT_DOWN;
	//GPIO_InitStructure.GPIO_Pin = MECH_SW;
	GPIO_InitStructure.GPIO_Pin = Light_Sensor;

	//GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void led_init(void){

	GPIO_InitTypeDef LED_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	LED_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //OUTPUT pin
	LED_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	LED_InitStructure.GPIO_Pin = LED_RED|LED_GREEN;

	GPIO_Init(GPIOG, &LED_InitStructure);			// e.g. PG GPIO_Pin_6 = red

	GPIO_SetBits(GPIOG, LED_RED);        // Set Red LED off at default init state
	GPIO_SetBits(GPIOG, LED_GREEN);
}

void led_blue_init(void){

	GPIO_InitTypeDef LED_BLUE_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	LED_BLUE_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //OUTPUT pin
	LED_BLUE_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	LED_BLUE_InitStructure.GPIO_Pin = LED_BLUE;

	GPIO_Init(GPIOD, &LED_BLUE_InitStructure);

	GPIO_SetBits(GPIOD, LED_BLUE);
}


int main(void){

	ticks_init(); // for delay_ms()
	button_init();
	led_init();
	led_blue_init();


	/* Infinite loop */
	while(1){

		//        if(!GPIO_ReadInputDataBit(GPIOF,BUT_UP)){
		//        while(!GPIO_ReadInputDataBit(GPIOF,BUT_UP));    // Waiting button release

		/* Solution 1*/
		//					GPIO_ResetBits(GPIOG, LED_RED);                 // Red LED On
		//					_delay_ms(1000);                                // delay 1 seconds
		//					GPIO_SetBits(GPIOG, LED_RED);                   // Red LED Off

		/* Solution 2*/
		/*
					GPIO_WriteBit(GPIOG, LED_RED, 0);                // Red LED On
					_delay_ms(1000);  												 	  	 // delay 1 seconds
					GPIO_WriteBit(GPIOG, LED_RED, 1);                // Red LED off
		 */

		//        }

		/*
		if(!GPIO_ReadInputDataBit(GPIOF,BUT_DOWN)){
			while(!GPIO_ReadInputDataBit(GPIOF,BUT_DOWN));    // Waiting button release


			if (counter%2 != 0 ){
				GPIO_ResetBits(GPIOG, LED_GREEN);
				counter++;
			}
			//_delay_ms(1000);                                // delay 1 seconds

			else {
				GPIO_SetBits(GPIOG, LED_GREEN);                   // Red LED Off
				counter ++;
			}

		}
		 */
		/*
        else {
        	GPIO_SetBits(GPIOG, LED_GREEN);
        }

		 */
		/*
		if(!GPIO_ReadInputDataBit(GPIOE,MECH_SW)){
			_delay_ms(100);		//debounce
			while(!GPIO_ReadInputDataBit(GPIOE,MECH_SW));    // Waiting button release
			_delay_ms(100);  //debounce

			if (counter%2 == 0 ){
				GPIO_ResetBits(GPIOG, LED_RED);
				counter++;
			}
			//_delay_ms(1000);                                // delay 1 seconds

			else {
				GPIO_SetBits(GPIOG, LED_RED);                   // Red LED Off
				counter ++;
			}
		}
		 */
		if(!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)){
			switch(counter){
			//red
			case 1:
				GPIO_ResetBits(GPIOG, LED_RED);
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (time<=1000)){
					_delay_ms(1);
					time++;
				}
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)){ //don't do the checking from the beginning!
					GPIO_SetBits(GPIOG, LED_RED);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					GPIO_ResetBits(GPIOG, LED_RED);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					counter = 2;
				}
				time = 0;
				break;
				//green
			case 2:
				GPIO_ResetBits(GPIOG, LED_GREEN);
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (time<=1000)){
					_delay_ms(1);
					time++;
				}
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)){ //don't do the checking from the beginning!
					GPIO_SetBits(GPIOG, LED_GREEN);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					GPIO_ResetBits(GPIOG, LED_GREEN);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					counter = 3;
				}
				time = 0;
				break;
				//blue
			case 3:
				GPIO_ResetBits(GPIOD, LED_BLUE);
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (time<=1000)){
					_delay_ms(1);
					time++;
				}
				while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)){ //don't do the checking from the beginning!
					GPIO_SetBits(GPIOD, LED_BLUE);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					GPIO_ResetBits(GPIOD, LED_BLUE);
					while (!GPIO_ReadInputDataBit(GPIOE,Light_Sensor)&& (flash<=100)){
						_delay_ms(1);
						flash++;
					}
					flash = 0;
					counter = 1;
				}
				time = 0;
				break;
			}
		}
		else{
			GPIO_SetBits(GPIOG, LED_RED);	// Red LED Off
			GPIO_SetBits(GPIOG, LED_GREEN);
			GPIO_SetBits(GPIOD, LED_BLUE);
		}
	}
	return 0;
}
