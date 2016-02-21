/*
This is the mapping of Voxels to ports on the AVR

        ________________________________________________________
PORTD = | DOWN |  X   |   X  | LEFT | FALL | RIGHT | UP  | RISE  
			7	  6	  	  5  	 4 		3		2 	  1 	 0
*/
#include "controller.h"
#include <avr/io.h>

#define RISE 0
#define UP 1
#define RIGHT 2
#define FALL 3
#define LEFT 4
#define DOWN 7


void init_controller(void){
	//set pins as inputs
	DDRD  = 0b00000000;
	//activate pull-up resistors on pins
	// that we are using.
	PORTD = 0b10011111;
}

int read_bit(int bit_num){
	return !((PIND >> bit_num) & 0b1);
}

int up_pressed(void){
	return read_bit(UP);
}
int down_pressed(void){
	return read_bit(DOWN);
}
int left_pressed(void){
	return read_bit(LEFT);
}
int right_pressed(void){
	return read_bit(RIGHT);
}
int rise_pressed(void){
	return read_bit(RISE);
}
int fall_pressed(void){
	return read_bit(FALL);
}