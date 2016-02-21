/*
The Controller works as follows:

              __   
             |  | <-UP  
              --                  __   
                                 |  | <-RISE 
       __            __           --   
      |  | <-LEFT   |  | <-RIGHT 
       --            --  
                                 |  | <-FALL
              __                  -- 
             |  | <-DOWN
              --

where UP, DOWN are changes in Y
		LEFT, RIGHT are changes in X
		and RISE, FALL are changes in Z

Note that DOWN causes Y to increase due
	to the left handed coordinate system
*/


void init_controller(void);

int read_bit(int bit_num);

int up_pressed(void);
int down_pressed(void);
int left_pressed(void);
int right_pressed(void);
int rise_pressed(void);
int fall_pressed(void);