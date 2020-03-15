#include "Arduino.h"        //Allows DDRD, PORTD syntax 
#include "RELAY.h"


/*******************************************************************************
 * RELAY_init
 * Purpose: Init Seeed Studio Relay Shield v3 I/O
 *******************************************************************************/
void RELAY_init(){
  
  DDRD |= (1 << RELAY2_DDR) | (1 << RELAY3_DDR);      
  PORTD &= ~(1 << RELAY2) | ~(1 << RELAY3); 					//Set relays in normally open state

}




 
 
