/**
PLM_Switch_Node.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Example showing how to setup the PLM Switch Node (Arduino UNO + Seeed Studio Relay Shield v3 + JARViE PLM Shield)
         to allow master/host to control its relays with commands sent over home AC or DC powerline
Date: 26-JAN-2020
References: 
            -TDA5051A datasheet
            -https://github.com/DudeYarvie/JARViE_Home_Automation_Modem
Releases: 
            1.0 - Intial release
**/

/*INCLUDES*/
#include "USART.h"
#include "PLM.h"
#include "Relay.h"


/*GLOBALS*/
#define MAX_BUF_SIZE 50
char msgBuffer[MAX_BUF_SIZE];                                     //Buffer to hold master/host message


/*PROTOTYPES*/
void PLM_init();
void USART_Init( unsigned int ubrr);
void PLM_read_msg(char *buf, int n);
uint16_t fletch_check( uint8_t *data, int count );
void RELAY_init();


void setup() {

  /*Init PLM IO*/
  PLM_init();                                                       

  /*Init Relay Shield IO*/
  RELAY_init();                                                     

  /*Init USART*/
  cli();                                                            //Stop interrupts
  USART_Init(MYUBRR);                                            
  sei();                                                            //Start interrupts
  delay(1000);                                                      //Delay

}


void loop() {
  
  /*Clear message buffer*/
  msgBuffer[MAX_BUF_SIZE]= "";
  delay(10);
    
  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);                

  /*Check if the RELAY cmd was received from Host*/
  if(strncmp(msgBuffer,"RELAY_O",strlen("RELAY_O"))==0){            //IF host cmd is "RELAY_O"
    PORTD |= (NO_RELAY << RELAY3);                                  //Sets relay to norm open state
    
  }
  if(strncmp(msgBuffer,"RELAY_C",strlen("RELAY_C"))==0){            //IF host cmd is "RELAY_C"
    PORTD &= ~(NO_RELAY << RELAY3);                                 //Sets relay to norm close state
  }        
}
