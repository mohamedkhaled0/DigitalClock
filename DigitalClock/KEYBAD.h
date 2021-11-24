/*
 * KEYPAD.h
 *
 * Created: 22/08/2019 03:50:47 ص
 *  Author: mohamed khaled
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>

#define R0 0 
#define R1 1 
#define R2 2 
#define R3 3 
#define C0 4 
#define C1 5 
#define C2 6 
#define C3 7 

#define KeyPadPort PORTC
#define KeyPadDirection DDRC
#define KeyPadPin PINC 

void KeyPadInit (void); 
char KeyPadgetkeypressed (void);


#endif /* KEYPAD_H_ */