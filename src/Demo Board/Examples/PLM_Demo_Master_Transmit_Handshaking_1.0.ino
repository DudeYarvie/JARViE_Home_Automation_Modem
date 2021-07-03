/**
PLM_Demo_Master_Transmit_Handshaking.ino
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Example showing how to send a command to another JARViE PLM board (demo or shield) and wait for a response.
Date:27-APR-2021
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
char msgBuffer[MAX_BUF_SIZE];                             //Buffer to hold incoming packet

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
  DDRB |= (1 << DDB5);                                    //Set Arduino LED pin D13 (PB5) as an output for PLM Demo Board only                                     
  
  /*Init USART*/
  cli();                                                  //Disable interrupts
  USART_Init(MYUBRR);                                     //Init UART
  sei();                                                  //Enable interrupts
  delay(1000);                                            //Delay

  /*Calculate message checksum*/
  checksum = fletch_check(msg, strlen(msg));              //Calculate Fletcher16 checksum
  //Serial.println(checksum);                             //DEBUG: print checksum for debugging
  sprintf(buf," %u\n",checksum);                          //Construct checksum buffer
  strcat (msg, buf);                                      //Concatenate data message and checksum

  /*Transmit data to slave powerline modem*/
  while (1){
    msgBuffer[MAX_BUF_SIZE]="";                           //Clear msgBuffer

    
    for (int i = 0; i <= 4; i++){                         //Blink DEBUG LED to visually indicate data message will be sent shortly
      PORTB |= (1<<PIN5);                         
      delay(150);                                         
      PORTB &= ~(1<<PIN5);
      delay(150);
    }


    /*Send data to slave*/    
    UCSR0B &= ~(1<<RXEN0);                                //Must Disable RX of MCU because PLM comms occur on the same wire 
                                                          //(PLM shield AC couples TX to RX)

    for (int j = 0; j < strlen(msg); j++){                //Send message through USART

      //Wait for AC mains zero cross point to
      //ensure least noise on AC power bus (comment out While loop if using DC power line)
      while(1){
        ZERO_CROSS_FLAG = digitalRead(2);                 //Read the input pin that PLM zecro cross detector output is connected to. Zero cross signal is active HIGH.
        if (ZERO_CROSS_FLAG == 1) break;                  
      }
      
      PLM_send_msg(msg[j]);
      delay(10);
    }
       
    delay(500);                                           //Delay after last cmd byte is transmitted                           
    UCSR0B |= (1<<RXEN0);                                 //Enable UART RX
    delay(500);                                           //Required delay to let MCU UART RX circuit to setup

    //Check if Slave acknowledged Master cmd
    PLM_read_msg(msgBuffer, MAX_BUF_SIZE);                //Read msg from Slave powerline modem
    //Serial.println(msgBuffer);                          //DEBUG: print data received from slave
    
    if(strncmp(msgBuffer,"ACK",strlen("ACK"))==0){        //Check to see if acknowledgement message is received 
      for (int k=0;k<8;k++){                              //Blink the debug LED to provide visual confirmation
        PORTB |= (1<<PIN5);                
        delay(500);                             
        PORTB &= ~(1<<PIN5);
        delay(500);
      }
    }
  }
}


void loop() {
  //

}
