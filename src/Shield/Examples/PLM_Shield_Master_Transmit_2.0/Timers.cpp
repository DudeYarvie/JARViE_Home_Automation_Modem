#include "Timers.h"
#include <HardwareSerial.h>
#include <avr/interrupt.h >


/*******************************************************************************
 * congfig_timers
 * Purpose: Configures and enables Timer0 and interrupts  
 *******************************************************************************/
void config_timers(){
/*
  //Configure Timer0
  //cli();//stop interrupts

  //Set timer0 interrupt at 10kHz
  TCCR0A = 0;								// set entire TCCR0A register to 0
  TCCR0B = 0;								// same for TCCR0B
  TCNT0  = 0;								//initialize counter value to 0
  
  //Set compare match register for 5khz increments
  OCR0A = 200;     							// = [(16e6) / (freq*2*8)] - 1 (must be <256)
  //OCR0B = 200;  							// = (16*10^6) / (freq*2*8) - 1 (must be <256)
  
  //Turn on CTC (clear timer after compare match) mode
  TCCR0A |= (1 << WGM01);
  
  //Set CS01 and CS00 bits for 8 clock prescaler (clk/prescaler)
  TCCR0B = (1 << CS01) | (0 << CS00);   
  
  //Disable timer compare interrupt for Timer/Counter0 Output Compare Match A
  TIMSK0 &= ~(1 << OCIE0A);
*/
  
  //Set timer2 interrupt at 5kHz
  TCCR2A = 0;								// set entire TCCR2A register to 0
  TCCR2B = 0;								// same for TCCR2B
  TCNT2  = 0;								//initialize counter value to 0
  
  //Set compare match register for 5khz increments or 1 TICK = 10 microseconds
  OCR2A = 200;								// = (16*10^6) / (8000*8) - 1 (must be <256)
  
  //Turn on CTC mode
  TCCR2A |= (1 << WGM21);
  
  //Set CS21 bit for 8 prescaler
  TCCR2B = (1 << CS21)|(0 << CS20);   
  
  //Enable timer compare interrupt
  TIMSK2 &= ~(1 << OCIE2A);

  
  
  //Enable global interrupts  
  //sei();//allow interrupts
  
}
