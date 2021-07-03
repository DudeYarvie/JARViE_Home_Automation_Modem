/*  Measure_Line_Freq.ino
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Example code to measure PLM line freq  
Date: 03-AUG-2019           
*/


/*INCLUDES*/
#include "Timers.h"


/*GLOBALS*/

//UART
#define BAUD 2e6

//Timing 
volatile uint32_t CNTR_TICKS = 0;
volatile uint8_t EDGE_CNT = 0;
volatile boolean MEAS_COMPLETE = false;
uint32_t EDGE_TIMES[2] = {0x0000, 0x0000};
uint32_t ELAPSED_TIME = 0;
//float FREQ = 0.0;

//INTERRUPTS
#define ZERO_CROSS_PIN      PIN2       
#define ZERO_CROSS_DDR      DDD2    //Arduino D2



/*PROTOTYPES*/



/*INTERRUPTS*/
/**********************************************************************
 * TIMER0 COMPA Interrupt VECTOR
 * Purpose: Tracks 1ms ticks
 **********************************************************************/
SIGNAL(TIMER0_COMPA_vect) 
{
  CNTR_TICKS += 1;          //Increment tick counter.  Ticks every 200 microseconds

  //ensure CNTR_TICKS does not overflow
}


/**********************************************************************
 * External Interript 0 VECTOR
 * Purpose: Execute the following code when a rising edge occurs 
 **********************************************************************/
ISR(INT0_vect){

  //Store time of EDGE occurence into array
  if (EDGE_CNT == 0){
      EDGE_TIMES[0] = CNTR_TICKS;
      EDGE_CNT += 1;                            //Increment edge counter
  }
  else {
      EDGE_TIMES[1] = CNTR_TICKS;
      MEAS_COMPLETE = true;                     //Set measurement complete flag to true
      EDGE_CNT = 0;                             //Re-init edge count
  }
    
}


/*FUNCTIONS*/

/**********************************************************************
 * init__io
 * Purpose: Configure I/O for PLM line freq measurement
 **********************************************************************/
void init_io(){
  //Intialize IO
  DDRD |=  (0 << ZERO_CROSS_DDR);    //Sets pin I/O state
  PORTD |= (0 << ZERO_CROSS_PIN);    //Init pin logic levels (0=LOW, 1=HIGH)
}


/****************************************************************************
 * EN_zero_cross
 * Purpose: Enables rising-edge interrupts on INT0 for zero-cross detection
 ***************************************************************************/
void EN_zero_cross(){

  //stop interrupts
  //cli();

  //Configure external interrupt INT0 (Arduino digital pin 2) to trigger on rising edges 
  EICRA = (1 << ISC01) | (1 << ISC00);
  
  //Enable external interrupt INT0
  EIMSK =  (1 << INT0);  

  //Enable global interrupts  
  //sei();
  
}


/****************************************************************************
 * meas_line_freq
 * Purpose: Measure the frequency of the PLM AC power line
 ***************************************************************************/
 float meas_line_freq(){
  
  float FREQ = 0.0;
  
  sei();                                                              //Start interrupts
  while(!MEAS_COMPLETE);                                              //Wait for line freq measurement to be ready
  cli();                                                              //Stop interrupts
  
  //ELAPSED_TIME =  EDGE_TIMES[1] -  EDGE_TIMES[0];                   //Calc elapsed time between rising edges of PLM ZCD circuit
  FREQ = 1.0/(float(EDGE_TIMES[1] - EDGE_TIMES[0])*200e-6);           //Calc line freq
  //Serial.println(FREQ);                                             //Print line freq for debbuging
  MEAS_COMPLETE = false;                                              //Reset the measurement compelte flag
  return FREQ;

}

void PLM_delay(){
  for (uint16_t i = 0; i < 10000; i++){
    for(uint32_t j = 0; j < 1000000; j++){
      //continue;
    }
  }
}


void setup() {
  //stop interrupts
  cli();
  EN_zero_cross();                                                  //Enable zero cross detection
  config_timers();                                                  //Configure program timer(s)

  //Enable global interrupts  
  sei();  

  Serial.begin(BAUD);
  init_io();
  delay(100);

  /*Open Serial connection for debbuging*/
  //Serial.begin(115200);
  Serial.println("starting...");
  delay(100);

  for (int i = 0; i < 10; i++){
    Serial.println(meas_line_freq());
    //PLM_delay();            //delay not working.  need to be able to delay between a string of freq measurements.
  }   

}

void loop() {
//  Serial.println(meas_line_freq());
//  sei();                                                              //Start interrupts
//  while(!MEAS_COMPLETE);                                              //Wait for line freq measurement to be ready
//  cli();                                                              //Stop interrupts
//  
//  //ELAPSED_TIME =  EDGE_TIMES[1] -  EDGE_TIMES[0];                   //Calc elapsed time between rising edges of PLM ZCD circuit
//  FREQ = 1.0/(float(EDGE_TIMES[1] - EDGE_TIMES[0])*200e-6);           //Calc line freq
//  Serial.println(FREQ);                                               //Print line freq for debbuging
//  MEAS_COMPLETE = false;                                              //Reset the measurement compelte flag

}
