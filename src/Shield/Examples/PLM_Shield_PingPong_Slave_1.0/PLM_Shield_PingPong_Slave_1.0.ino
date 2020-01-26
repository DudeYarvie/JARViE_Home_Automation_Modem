/**
  PLM_Shield_PingPong_Slave.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Example showing how to receive a command from another PLM Shield and send back a response
Date: 25-JAN-2020
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
char msgBuffer[MAX_BUF_SIZE];  //Buffer to hold incoming packet



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
  USART_Init(MYUBRR);     
  sei();                  //Start interrupts
  delay(500);             //Delay

}


void loop() {
  /*Clear message buffer*/
  msgBuffer[MAX_BUF_SIZE]="";

  
  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);  
  //Serial.println(msgBuffer);                                    //DEBUG: print cmd received from master

  
  /*Check Command from Master*/
  if(strncmp(msgBuffer,"TEMP",strlen("TEMP"))==0){                //IF host cmd is "TEMP"
    for (int i=0;i<strlen(msgBuffer);i++){                        //Blink the debug LED
      delay(250);  
      PORTD ^= (1<<DEBUG_LED);                                    //Toggle DEBUG LED
      delay(250);                                                 //Delay 
    }
    
    delay(10);                                                    //Short delay required to not drop any characters in slave response
    
    //Serial.print(strlen(msgBuffer));                            //DEBUG: print master cmd length 
    /*ECHO host cmd*/
    strcpy(msgBuffer,"ACK\n");                                    //Load ACK cmd and EOL character into message buffer
    for (int j=0;j<strlen(msgBuffer);j++){                        //Send slave ACK to host
      PLM_send_msg(msgBuffer[j]);
      delay(10);
    }
  }
}
