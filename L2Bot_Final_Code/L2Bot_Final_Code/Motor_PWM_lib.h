/*
 * Motor_PWM_lib.h
 * Usage
 HBridgeInit(); // define ports and set up 16 bit timer TCNT1
 
 sei(); // enable interrupts
 
 HBridgeCommand(uint8_t side, uint8_t speed, uint8_t direction);
 
 // where side 0 = left motor, 1 = right
 // speed = 0-100
 // direction 0 = forward, 1 = reverse
 
 *
 * Created: 2/11/2013 10:32:44 AM
 *  Author: jkerns
 */ 


#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>


// prototype for PWM initialize
void HBridgeInit(); 
// prototype for H-Bridge control.
void HBridgeCommand(uint8_t side, uint8_t speed, uint8_t direction);


#endif /* MOTOR_PWM_H_ */