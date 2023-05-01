#ifndef Serial_LIB_H_
#define Serial_LIB_H_

//#define F_CPU  11059200ul  //8000000ul  set CPU clock speed here. 
#include "F_cpu_lib.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


/*
Usage:
 
int main(void) {
		USART_vInit(); // Initialize USART for serial communication. 

while(1)
{
        // recieving character from serial port 
	if (NewSerialData== 1) // character received. 
	{
		NewSerialData = 0;
                // use the character for ...
                }

        // sending character inside a array of char CharArray of length Array Size
    	    for(uint8_t i = 0; i < ArraySize; i++){
			uart_putchar(CharArray[i], &mystdout);
                        }


*/

// ***********  Select the correct value below for USART_UBBR_VALUE given the F_CPU clock frequency ***************

#define USART_UBBR_VALUE 51ul
// 71 UL for 11.059 MHz at 9600 baud
//51ul 9600 baud at 8mhz, 3ul 115.2K at 8 mhz clock, 8ul with U2X = 1 for 115.2 baud at 8 MHz




char PCData;	// character received from PC via serial port
extern uint16_t programEnabled;
//uint8_t NewSerialData = 0; // new data recieved from serial port

// Define baud rate for serial communication  
//#define USART_BAUD 9600ul// 115200ul


//prototypes for serial communication
extern int uart_putchar(char c, FILE *stream);
extern uint8_t serialCheckRxComplete(void);

extern FILE mystdout;

extern void USART_vInit();
extern void USART_vSendByte(uint8_t);
#endif