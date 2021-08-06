/**
PLM_Shield_Slave_Receive.ino
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Example showing how to receieve a command from another PLM shield
Date: 25-JAN-2020
References: 
            -TDA5051A datasheet
            -https://github.com/DudeYarvie/JARViE_Home_Automation_Modem
Releases: 
            1.0 - Intial release
            2.0 - Added timeout for PLM communications in PLM.cpp.  One can remove timeout if comms will only be sent from master to slave.  
            If bi-directional comms or handshaking between master and slave is desired, invoking a timeout is encouraged so the PLM bus 
            does not hang when comms are unsucessful.
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
char *PLM_read_msg();
uint16_t fletch_check( uint8_t *data, int count );


void setup() {

  /*Init PLM IO*/
  PLM_init();

  /*Init USART*/
  cli();                  //Stop interrupts
  USART_Init(MYUBRR);     //Decide whether or not to include this in PLM_Init
  sei();                  //Start interrupts
  delay(1000);            //delay

}


void loop() {
  /*Clear message buffer*/
  msgBuffer[MAX_BUF_SIZE]="";
  
  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);  

  /*Check if the IDN? cmd was received from Host*/
  if(strncmp(msgBuffer,"IDN?",strlen("IDN?"))==0){                     //IF host cmd is "IDN?"
    for (int i=0;i<strlen(msgBuffer);i++){                           //Blink the debug LED
      
      PORTD ^= (1<<DEBUG_LED);                                    //Toggle DEBUG LED
      delay(250);                                                 //Delay 
    }
    //Serial.println(buf);                                //Print cmd length for DEBUGGING
  }

}
