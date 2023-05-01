/*
 * L2Bot_Final_Code.c
 *
 * Created: 4/12/2023 12:40:18 PM
 * Author : aturner2
 */ 

//library files for LCD screen, motor, analog input, etc
#include "C:/Users/aturner2/Desktop/UR1/labFiles/F_cpu_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "C:/Users/aturner2/Desktop/UR1/labFiles/LCD_lib.h"
#include "C:/Users/aturner2/Desktop/UR1/labFiles/A2D_lib.h"
#include "C:/Users/aturner2/Desktop/UR1/labFiles/Serial_lib2.h"
#include "C:/Users/aturner2/Desktop/UR1/labFiles/Motor_PWM_lib.h"


//states and motor setup 
#define state_forward 001
#define state_slight_left 002
#define state_hard_left 003
#define state_slight_right 004
#define state_hard_right 005
#define state_stop 006 //default

int main(void)
{
	//initialization section 
	uint16_t adc_value = 0;
	char lcd_string_output[20];
	//uint8_t serial_char_input; 
	char serial_char_array_output[20];
	
	//On-board LED 
	DDRC |= 1 << PINC2; 
	
	//LCD 
	LCD_init();
	LCDGoToPosition(1,1);
	sprintf(lcd_string_output, "Hello World");
	LCDSendString(lcd_string_output);
	_delay_ms(1000);
	LCDClearScreen();
	
	//serial
	AD_init();
	USART_vInit();
	sei();
	LCDClearScreen();
	uint8_t serialInput; //for visual studios code to change states 
	
	//motor 
	HBridgeInit();
	
	//sides
	//side 0 should be the terminal closest to the power terminal on my micro board 
	uint8_t right = 0;
	uint8_t left = 1;
	
	//speed 
	uint8_t speed_forward = 50; //old speed = 50, new speed = 75
	uint8_t speed_slight_left = 30;
	uint8_t speed_slight_right = 30; //old speed = 25, new speed = 30
	uint8_t speed_hard_left = 75; //75 old speed 
	uint8_t speed_hard_right = 75; // 75 old speed
	uint8_t speed_stop = 0;
	
	//direction 
	uint8_t reverse = 0;
	uint8_t forward = 1;
	uint8_t stopped = NULL; //no direction since the motors are not moving at all 
	
	
	//state 
	uint8_t state = state_stop; //default state 
	
	
  
    while (1) 
    {
		//check if byte is sending - using if statement 
		if(serialCheckRxComplete() != 0)
		{
			serialInput = USART_vReceiveByte();
		}
		uart_putchar('\n', &mystdout);
		
		switch(state)
		{
			case state_stop: //default state -- no movement 
		
			LCDClearScreen();
			//stop both motors so not movement -- default state and at red line 
			//motors: side, speed, direction 
			HBridgeCommand(right, speed_stop, stopped); //right motor 
			HBridgeCommand(left, speed_stop, stopped); //left motor 
			
			//output the state onto the LCD screen 
			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "stop");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			//if and else if statements to switch from state to state 
			if (serialInput == 'f') //forward case 
			{
				state = state_forward; //changes state 
			}
			else if (serialInput == 'l') //slight left 
			{
				state = state_slight_left; 
			}
			else if (serialInput == 'r') //slight right 
			{
				state = state_slight_right;
			}
			else if (serialInput == 'a') //hard left 
			{
				state = state_hard_left;
			}
			else if (serialInput == 'd') //hard right 
			{
				state = state_hard_right;
			}
			
			break;
			
			//case for slight left 
			
			case state_forward:
			
			LCDClearScreen();
			//motors (side, speed, direction) -- half speed for slower motor rates 
			//going forward in a straight line 
			HBridgeCommand(right, speed_forward, forward); //right 
			HBridgeCommand(left, speed_forward, forward); //left  
			
			//what state the robot is in
			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "forward");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			//state changes 
			if (serialInput == 's') //stopping 
			{
				state = state_stop;
			}
			else if (serialInput == 'l') //slight left
			{
				state = state_slight_left;
			}
			else if (serialInput == 'r') //slight right
			{
				state = state_slight_right;
			}
			else if (serialInput == 'a') //hard left
			{
				state = state_hard_left;
			}
			else if (serialInput == 'd') //hard right
			{
				state = state_hard_right;
			}
			 
			break; 
			
			case state_slight_left:
			
			LCDClearScreen();
			
			//motor code -- left motor going slower than right to turn left 
			HBridgeCommand(right, speed_forward, forward);
			HBridgeCommand(left, speed_slight_left, forward);
			
			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "slight left");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			//state changes
			if (serialInput == 's') //stopping
			{
				state = state_stop;
			}
			else if (serialInput == 'f') //slight left
			{
				state = state_forward;
			}
			else if (serialInput == 'r') //slight right
			{
				state = state_slight_right;
			}
			else if (serialInput == 'a') //hard left
			{
				state = state_hard_left;
			}
			else if (serialInput == 'd') //hard right
			{
				state = state_hard_right;
			}
			
			break;
			
			case state_slight_right:
			
			LCDClearScreen();
			//motor code -- right motor less than left to turn right 
			HBridgeCommand(right, speed_slight_right, forward);
			HBridgeCommand(left, speed_forward, forward);
			
			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "slight right");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			if (serialInput == 'f') //forward case
			{
				state = state_forward; //changes state
			}
			else if (serialInput == 'l') //slight left
			{
				state = state_slight_left;
			}
			else if (serialInput == 'a') //hard left
			{
				state = state_hard_left;
			}
			else if (serialInput == 'd') //hard right
			{
				state = state_hard_right;
			}
			else if (serialInput == 's')
			{
				state = state_stop;
			}
			
			break;
			
			case state_hard_left:

			LCDClearScreen();
			//motor control -- fast on right motor, slower on the left motor so that the robot banks hard left 
			HBridgeCommand(right, speed_hard_right, forward);
			HBridgeCommand(left, speed_slight_left, forward);

			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "hard left");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			if (serialInput == 'f')
			{
				state = state_forward;
			}
			else if (serialInput == 'l')
			{
				state = state_slight_left;
			}
			else if (serialInput == 'r')
			{
				state = state_slight_right;
			}
			else if (serialInput == 's')
			{
				state = state_stop;
			}
			else if (serialInput == 'd')
			{
				state = state_hard_right;
			}
			
			break;
			
			case state_hard_right:
			
			LCDClearScreen();
			HBridgeCommand(right, speed_slight_right, forward);
			HBridgeCommand(left, speed_hard_right, forward);

			LCDGoToPosition(1,1);
			sprintf(lcd_string_output, "hard right");
			LCDSendString(lcd_string_output);
			
			LCDGoToPosition(1,2);
			sprintf(lcd_string_output, "%c", serialInput);
			LCDSendString(lcd_string_output);
			
			if (serialInput == 'f')
			{
				state = state_forward;
			}
			else if (serialInput == 'l')
			{
				state = state_slight_left;
			}
			else if (serialInput == 'r')
			{
				state = state_slight_right;
			}
			else if (serialInput == 's')
			{
				state = state_stop;
			}
			else if (serialInput == 'a')
			{
				state = state_hard_left;
			}

			break;
			
			default:	
			state = state_stop;
			
			break;
			
		}
		
		for (uint8_t i = 0; i < 20; i++)
		{
			uart_putchar(serial_char_array_output[i], &mystdout);
		}
		uart_putchar('\n', &mystdout);
		
    }
}

