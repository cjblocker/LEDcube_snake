/*
This is the mapping of Voxels to ports on the AVR

        ________________________________________________________
PORTB = |  X   |  X   | (2,1)| (0,1)| (0,1)| (2,0)| (1,0)| (0,0)
			7	  6	  	  5  	 4 		3		2 	  1 	 0
        ________________________________________________________
PORTC = |  X   |  X   | (2,2)| (1,2)| (0,2)|!(z=2)|!(z=1)|!(z=0)
			7	  6	  	  5  	 4 		3		2 	  1 	 0
*/

#include "view.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define PRESCALE 1024UL
#define FREQ 250UL

typedef struct {
	char port1;
	char port2;
	char plane_mask;
} plane_t;

//display buffer
static plane_t cube[3];
//buffer index
static int curr_plane = 0;


// Setup Timers and outputs for the display
void init_view(void){
	//setup output ports
	//1 = output, 0 = input
    DDRB = 0b00111111; //All outputs
    DDRC = 0b00111111; //All outputs

    //setup timer interrupt to multiplex planes and keep display refreshed
	TCCR1B |= (1 << WGM12 ); // Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A ) ; // Enable CTC interrupt
	sei () ; // Enable global interrupts
	OCR1A = F_CPU/(PRESCALE*FREQ) - 1; // Set CTC compare value 
	TCCR1B |= ((1 << CS10 ) | (1 << CS12 )) ; // Start timer at Fcpu/1024

	//setup the display buffer
	for (int i = 0; i < MAX_Z; ++i)
	{
		cube[i].plane_mask = ~(1 << i) & 0b000111;
		cube[i].port1 = 0;
		cube[i].port2 = 0;
	}
}

//ISR called every 4ms to refresh new group of LEDs
ISR ( TIMER1_COMPA_vect ){
	refreshLEDs();
}

//the LEDs of PORTB can't all be on at the same time
// with the LEDs of PORTC. In order to accomodate this
// I've seperated PORTB and PORTC into their own refresh
// cycles and uped the refresh rate to 250Hz. So now
// there are 6 refresh cycles instead of 3.
void refreshLEDs(void){
	curr_plane = (curr_plane+1) % (MAX_Z*2);
	if (curr_plane % 2 == 0)
	{
		// oddly if you do these in the opposite order
		// then the x,y position of the previous plane
		// has a small amount of light
		PORTC = cube[curr_plane/2].plane_mask;
		PORTB = cube[curr_plane/2].port1;
	}
	else{
		PORTB = 0;
		PORTC = cube[curr_plane/2].port2 | cube[curr_plane/2].plane_mask;
	}
	
}

// Turn on or off a voxel in the display buffer
void setVoxel(int plane, char y, char x, char val){
	char pixel_num = x + 3*y;
	if (pixel_num == 0){
		pixel_num = 2;
	}
	else if (pixel_num == 2){
		pixel_num = 0;
	}
	if (pixel_num < 6){
		if (val){
			cube[plane].port1 |= 1 << pixel_num;
		}
		else{
			cube[plane].port1 &= ~(1 << pixel_num);
		}
	}
	else{
		if (val){
			cube[plane].port2 |= 1 << (pixel_num - 3);
		}
		else{
			cube[plane].port2 &= ~(1 << (pixel_num - 3));
		}
	}
}

// Load a model into the display buffer
void loadModel(char model[3][3][3]){
	for (int z = 0; z < MAX_Z; ++z)
	{
		for (int y = 0; y < MAX_Y; ++y)
		{
			for (int x = 0; x < MAX_X; ++x)
			{
				setVoxel(z,y,x,model[z][y][x]);
			}
		}
	}
}

// Turn off all Voxels
void clearAllVoxels(void){
	for (int i = 0; i < MAX_Z; ++i){
		cube[i].port1 = 0;
		cube[i].port2 = 0;
	}
}
