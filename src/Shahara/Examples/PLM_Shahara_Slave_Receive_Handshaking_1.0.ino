/**
  PLM_Shahara_Slave_Receive_Handshaking.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Example showing how to receive a command from another JARViE PLM devce (e.g. Demo, Shield, Shahara) and send back a response
Date: 19-FEB-2020
References: 
            -TDA5051A datasheet
            -https://github.com/DudeYarvie/JARViE_Home_Automation_Modem
Releases: 
            1.0 - Intial release
            2.0 -
**/

/*INCLUDES*/
#include "USART.h"
#include "PLM.h"


/*GLOBALS*/
#define MAX_BUF_SIZE 50
char msgBuffer[MAX_BUF_SIZE];  //Buffer to hold incoming packet
uint8_t ZERO_CROSS_FLAG = 0;



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

  //Sets zero cross detector pin (PD2) to input 
  pinMode(2, INPUT);   

}


void loop() {
  /*Clear message buffer*/
  msgBuffer[MAX_BUF_SIZE]="";

  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);  
  //Serial.println(msgBuffer);                                    //DEBUG: print cmd received from master

  /*Check Command from Master*/
  if(strncmp(msgBuffer,"IDN?",strlen("IDN?"))==0){                //IF host cmd is "TEMP"
 
    PORTD ^= (1<<DEBUG_LED);                                      //Toggle DEBUG LED
    
    /*Send data to slave*/    
    UCSR0B &= ~(1<<RXEN0);                                        //Must Disable RX of MCU because PLM comms occur on the same wire 
                                                                  //(PLM shield AC couples TX to RX)
                                                                  
    delay(2000);                                                  //Master requires 1 second after sending message before it can receive a message
    
    //Serial.print(strlen(msgBuffer));                            //DEBUG: print master cmd length 
    
    /*Send acknowledge cmd back to master*/
    
    strcpy(msgBuffer,"ACK\n");                                    //Load ACK cmd and EOL character into message buffer
    for (int j=0;j<strlen(msgBuffer);j++){                        //Send slave ACK to host
      
      //Wait for AC mains zero cross point
      while(1){
        ZERO_CROSS_FLAG = digitalRead(2);                         //read the zero cross detector
        if (ZERO_CROSS_FLAG == 1) break;
      }
      
      PLM_send_msg(msgBuffer[j]);                                 //Send next byte of data in "msgBuffer"
      delay(10);
      
    }
    
    delay(250);                                                   //Delay after last cmd byte is transmitted                           
    UCSR0B |= (1<<RXEN0);                                         //Enable UART RX
    delay(250);                                                   //Required delay to let MCU UART RX circuit to setup
  }
}
