/*
 * DigitalClock.c
 * Target Atmega16a 
 *LCD to display the time 
 *keypad to setup the time and to adjust the time 
   SEC - > PRESS 7 to increase , press 4 to decrease  
   MINUTES -> Press 9 to increase pres 6 to decrease 
   HOUR -> press 3 to increase press 1 to Decrease   
 * Created: 18/11/2021 07:41:34 م
 * Author : mohamed khaled
 */ 

#include <avr/io.h> 
#include <stdio.h>

#include "KEYBAD.h"
#include "LCD.h"

struct clock {
	int SEC ;
	int MIN ;
	int HOUR;
	char Mode;
	
} CLOCK ;

struct clock *P = &CLOCK ;

void LCD_UPDATE_SEC( int s);
void LCD_UPDATE_MIN( int m) ;
void LCD_UPDATE_HOUR( int h); 
void LCD_UPDATE_MODE (char M[]); 
void LCD_UPATE_CLOCK (void); 
void clock_EDITp (void);
void clock_EDITn (void); 


int main(void) {
	
	int i ;
	// interfaces
	LCD_INIT();
	KeyPadInit();
	
	// clock initializations 
	P->HOUR = 12 ;
	P->MIN = 59 ;
	P->SEC = 50; 
	P->Mode = "AM"; 
	// FLAGS TO ENTER THE DIFFERENT MODES
	char x , y ;
	
	while (1)
	{
		y = x = KeyPadgetkeypressed();
		
		
		// CLOCK MODE
		while ( x == 'A' )
		{
			x = KeyPadgetkeypressed();
			(P->SEC)++;
			LCD_UPATE_CLOCK ();
			
			if (P->SEC == 59)
			{
				(P->SEC) = 1 ;
				(P->MIN)++;
				LCD_UPATE_CLOCK ();
			} 
			
			// changing in minutes 
			if (P->MIN == 59)
			{
				(P->MIN) = 1 ; 
				(P->HOUR)++;
				if (P->HOUR >= 12) {
					P->HOUR = 1 ; 
					if (P->Mode == "PM") P->Mode = "AM";
				   else if (P->Mode == "AM") P->Mode = "PM";
					} 
					LCD_UPATE_CLOCK ();
				 
				
				LCD_UPATE_CLOCK ();
			} 
			
			// changing in hours 
			
			if (P->HOUR >= 12){ 
				P->HOUR = 1 ; 
				if (P->Mode =="PM") P->Mode = "AM";
				else if (P->Mode == "AM") P->Mode = "PM";
				LCD_UPATE_CLOCK ();
			} 
			
			 
			
			// flag to switch between to modes 
			if (x == '8') break;
			
		} 
		
		
		//-----------------------------------------------------------------------------------------------------------------//
		
		
		// EDIT MODE 
		while (y != '8')
		{
			y =KeyPadgetkeypressed();
			LCD_UPATE_CLOCK ();
			
			// EDIT SEC PRESS 7 to increase , press 4 to decrease  
			if (y == '7') {
				P->SEC++;
				clock_EDITp();
				LCD_UPATE_CLOCK();	
			}
			else if ( y == '4' )
			{
				P->SEC--;
				clock_EDITn();
				LCD_UPATE_CLOCK();
			}
			
			
			// EDIT MINUTES Pres 9 to increase pres 6 to decrease 
			if (y == '9') {
				
				P->MIN++; 
				clock_EDITp(); 
				LCD_UPATE_CLOCK();
				
			}
			else if ( y == '6' )
			{
				P->MIN--; 
				clock_EDITn(); 
				LCD_UPATE_CLOCK ();
			}
			
				
			//Edit Hours 3 to increase and 1 to decrease 
			if (y == '3'){ 
				(P->HOUR)++; 
				clock_EDITp(); 
			      LCD_UPATE_CLOCK ();
			} 

			
			 else if (y == '1'){
				(P->HOUR)--;
				clock_EDITn();
				LCD_UPATE_CLOCK ();
			}
				
			if (y == '8') break; 
			
			} 
			
	}
			
	
}



void LCD_UPDATE_SEC( int s) {

	LCD_GOTO_XY(0,6);
	
	LCD_SEND_INT(s);
}

void LCD_UPDATE_MIN( int m) {
	
	LCD_GOTO_XY(0,3);
	
	LCD_SEND_INT(m);
}

void LCD_UPDATE_HOUR( int h) {
	
	LCD_GOTO_XY(0,0);
	
	LCD_SEND_INT(h);
} 


void LCD_UPDATE_MODE (char M[]){ 
	LCD_GOTO_XY(0,9);
	LCD_SEND_A_STRING(M);
	
}




void LCD_UPATE_CLOCK (void){
	LCD_UPDATE_HOUR(P->HOUR);
	LCD_GOTO_XY(0,2);
	LCD_SEND_A_STRING(":");
	LCD_UPDATE_MIN(P->MIN);
	LCD_GOTO_XY(0,5);
	LCD_SEND_A_STRING(":");
	LCD_UPDATE_SEC(P->SEC);
	LCD_UPDATE_MODE(P->Mode); 
}  

// update the clock while  increasing 
void clock_EDITp (void) { 
	
	
	if (P->SEC == 60){
		(P->SEC) = 1 ;
		(P->MIN)++;  
	} 
	
	if (P->MIN == 60)
	{
		(P->MIN) = 1 ;
		(P->HOUR)++;
	} 
	
	if (P->HOUR >= 13) {
		P->HOUR = 1 ;
		if (P->Mode == "PM") P->Mode = "AM";
		else if (P->Mode == "AM") P->Mode = "PM";
	} 
	
	
  LCD_UPATE_CLOCK(); 
		
}
 
 
 // update the clock while dcrasing 
void clock_EDITn (void){
	
	if (P->SEC == 0){
		(P->SEC) = 59 ;
		(P->MIN)--; 
	}  
	
	if (P->MIN == 0){
		(P->MIN) = 59;
		(P->HOUR)--; 
	}
		
		
	if((P->HOUR ) == 0 ){
		P->HOUR = 12 ;
		if (P->Mode == "PM") P->Mode = "AM";
		else if (P->Mode == "AM") P->Mode = "PM"; 
	}
	
	LCD_UPATE_CLOCK(); 
	
	}

