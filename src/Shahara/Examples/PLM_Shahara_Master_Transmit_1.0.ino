/**
PLM_Shahara_Master_Transmit_1.0
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Example showing how to send a command to another JARViE PLM device (Demo Board, Shield, Shahara, etc.)
Date:27-MAY-2021
References: 
            -TDA5051A datasheet
            -https://github.com/DudeYarvie/JARViE_Home_Automation_Modem
Releases: 
            1.0 - Intial release


**/

/*INCLUDES*/
#include "USART.h"
#include "PLM.h"

/*GLOBALS*/
#define MAX_BUF_SIZE 50
char msgBuffer[MAX_BUF_SIZE];  // buffer to hold incoming packet

/*PROTOTYPES*/
void PLM_init();
void USART_Init( unsigned int ubrr);
uint16_t fletch_check( uint8_t *data, int count );
char *PLM_read_msg();
void PLM_send_msg( unsigned char data );


void setup() {

  /*Init local variables*/
  uint16_t checksum = 0;
  char msg[11] = "IDN?";
  char buf[6];
  char cmd[50];

  /*Init PLM IO*/
  PLM_init();

  /*Init USART*/
  cli();                                      //Disable interrupts
  USART_Init(MYUBRR);
  sei();                                      //Enable interrupts
  delay(1000);                                //delay

  /*Calculate message checksum*/
  checksum = fletch_check(msg, strlen(msg));  //Calculate Fletcher16 checksum
  //Serial.println(checksum);                 //Print checksum for debugging
  sprintf(buf," %u\n",checksum);              //Construct checksum buffer
  strcat (msg, buf);                          //Concatenate data message and checksum

  /*Transmit data to slave powerline modem*/
  while (1){

    
    for (int i = 0; i <= 4; i++){             //Blink DEBUG LED to visually indicate data message will be sent shortly
      PORTD ^= (1<<DEBUG_LED);                //Toggle DEBUG LED
      delay(500);                             //Delay
    }

    /*Send data to slave*/    
    for (int j = 0; j < strlen(msg); j++){    //Send message through USART
      PLM_send_msg(msg[j]);
      delay(10);
    }
    
    delay(8000);                              //Extremely long delay just because, not required    
      
  }
}


void loop() {
  //

}
