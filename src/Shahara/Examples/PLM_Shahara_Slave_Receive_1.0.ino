/**
PLM_Shahara_Slave_Receive.ino
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Example showing how to receieve a command from another JARViE PLM device (e.g. Demo, Shield, Shahara)
Date: 27-MAY-2021
References: 
            -TDA5051A datasheet
            -https://github.com/DudeYarvie/JARViE_Home_Automation_Modem
Releases: 
            1.0 - Init Release

**/

/*INCLUDES*/
#include "USART.h"
#include "PLM.h"


/*GLOBALS*/
#define MAX_BUF_SIZE 50
#define F_CPU 16000000UL
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
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);            //delay

}


void loop() {
  /*Clear message buffer*/
  msgBuffer[MAX_BUF_SIZE]="";
  
  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);  

  /*Check if the IDN? cmd was received from Host*/
  if(strncmp(msgBuffer,"IDN?",strlen("IDN?"))==0){                //IF host cmd is "IDN?"

    //Toggle AC relay and DEBUG LED
    PORTD ^= (1<<AC_RLY)|(1<<DEBUG_LED);
    //delay(250);                                                 //Allow relay to settle if needed 

    /*
    //Toggle DEBUG_LED
    for (int i=0;i<strlen(msgBuffer);i++){                        //Blink the debug LED
      
      PORTD ^= (1<<DEBUG_LED);                                    //Toggle DEBUG LED
      delay(250);
    }
    */
    //Serial.println(buf);                                        //Print cmd length for DEBUGGING
  }

}
