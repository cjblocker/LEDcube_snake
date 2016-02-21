
#include <avr/io.h>
#include <view.h>
#include <controller.h>

//Define functions
//======================
void ioinit(void);      //Initializes IO
void delay_ms(uint16_t x); //General purpose delay
void testLEDs(void);
void testMultiplexing(void);
void testPowerConsumption(void);
//======================

char model[3][3][3] = {
  {
    {0, 0, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  {
    {0, 0, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  }
};

int main (void)
{
    ioinit(); //Setup IO pins and defaults

    while(1){
      // for (int i = 0; i < 10; ++i)
      // {
      //   for (int z = 0; z < 3; ++z)
      //   {
      //     clearAllVoxels();
      //     for (int y = 0; y < 3; ++y)
      //     {
      //       for (int x = 0; x < 3; ++x)
      //       {
      //         setVoxel(z, y, x, 1);
      //       }
      //     }
      //     delay_ms(300);
      //   }
      // }
      // clearAllVoxels();
      // loadModel(model);
      // delay_ms(2000);
      // sphericalWave();
      roam();
      delay_ms(200);
    }
   
    return(0);
}

void ioinit (void)
{
    init_view();
    init_controller();
}

void roam(void){
  static int x = 0;
  static int y = 0;
  static int z = 0;

  if (down_pressed() && y < MAX_Y - 1)
  {
    y = y + 1;
  }
  else if (up_pressed() && y > 0)
  {
    y = y - 1;
  }
  else if (right_pressed() && x < MAX_X - 1)
  {
    x = x + 1;
  }
  else if (left_pressed() && x > 0)
  {
    x = x - 1;
  }
  else if (rise_pressed() && z < MAX_Z - 1)
  {
    z = z + 1;
  }
  else if (fall_pressed() && z > 0)
  {
    z = z - 1;
  }
  clearAllVoxels();
  setVoxel(z, y, x, 1);
}

void sphericalWave(void){
    for (int i = 0; i < 3; ++i)
    {
      clearAllVoxels();
      switch(i){
        case 0:
          setVoxel(0,0,0,1);
          break;
        case 1:
          setVoxel(0,0,1,1);
          setVoxel(0,1,0,1);
          setVoxel(0,1,1,1);
          setVoxel(1,0,0,1);
          setVoxel(1,0,1,1);
          setVoxel(1,1,0,1);
          setVoxel(1,1,1,1);
          break;
        case 2:
          loadModel(model);
          break;
      }
      delay_ms(300);
    }
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}