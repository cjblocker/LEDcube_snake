void testLEDs(void){
  //visits each LED and turns them on
  //one at a time
  int level;
  for (int i = 0; i < 3; ++i){

    level = ~(1 << i) & 0b000111;
    for (int j = 0; j < 9; ++j){

      if (j > 5){
        int k = j - 3;
        PORTB = 0;
        PORTC = level | (1 << k);
      }
      else{
        PORTC = level;
        PORTB = (1 << j);            
      }
      delay_ms(300);
    }
  }
}

void testMultiplexing(void){
  //Creates a Diagonal Pattern that could
  //only be acheive through multiplexing
  for (int i = 0; i < 500; ++i)
  {
    PORTB = 0b000001;
    PORTC = 0b000110;
    delay_ms(5);
    PORTB = 0b010000;
    PORTC = 0b000101;
    delay_ms(5);
    PORTB = 0b000000;
    PORTC = 0b001011;
    delay_ms(5);
  }
}

void testPowerConsumption(void){
  //Turns every LED on at the same time
  PORTB = 0b111111;
  PORTC = 0b111000;
  delay_ms(2000);
}