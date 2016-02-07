/*
The LED cube view uses a left-handed coordinate system
as shown below:
                                                   
         /|\  +Z              
          |                                         
          |                     
          |                       
          |                        
          |                        
          |                        
          | ________________\ +X   
         /                  /     
        /                                           
       /                          
      /                           
     /                            
   \// +Y                         

In the 3x3x3 matrix, this puts (0,0,0) in the far left 
bottom corner with the LEDs facing in the -X direction.

*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_Z 3
#define MAX_X 3
#define MAX_Y 3

// Setup Timers and outputs for the display
void init_view(void);

// Turns on the next refresh group of LEDs.
// this is normally only called by the ISR
void refreshLEDs(void);

// Turn on or off a voxel in the display buffer
void setVoxel(int, char, char, char);

// Load a model into the display buffer
void loadModel(char model[3][3][3]);

// Turn off all Voxels
void clearAllVoxels(void);