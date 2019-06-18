/**
Power_Line_Modem_Master.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Firmware for powerline modem slave device
Date:17-JUNE-2019
References: TDA5051A datasheet
**/

/*INCLUDES*/
#include "USART.h"

/*GLOBALS*/
//PLM DIO
#define PD_DDR DDD7
#define PD PIN7


/*PROTOTYPES*/
void init_io();
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
uint16_t fletch_check( uint8_t *data, int count );



/*******************************************************************************
 * init_io
 * Purpose: Init powerline modem I/O
 *******************************************************************************/
void init_io(){
  
  DDRD |= (1 << PD_DDR);      
  PORTD |= (1 << PD);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  
}


/*******************************************************************************
 * fletch_check
 * Purpose: Calcs Fletcher16 check sum of data 8-bit data buffer
 *******************************************************************************/
uint16_t fletch_check( uint8_t *data, int count )
{
   /*Init local variables*/
   uint16_t sum1 = 0;
   uint16_t sum2 = 0;
   int index;

   /*Calculate checksum bytes*/
   for( index = 0; index < count; ++index )
   {
      sum1 = (sum1 + data[index]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }

   /*Contsuct and return 16-bit checksum*/ 
   return (sum2 << 8) | sum1;
}


void setup() {

  /*Init local variables*/
  uint16_t checksum = 0;
  char msg[11] = "IDN?";
  char buf[6];
  char cmd[50];

  /*Init PLM IO*/
  init_io();

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

    
    for (int i = 0; i <= 3; i++){             //Blink Arduino LED to visually indicate data message will be sent shortly
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }

    /*Send data to slave*/    
    for (int j = 0; j < sizeof(msg); j++){    //Send message through USART
      USART_Transmit(msg[j]);
      delay(10);
    }
    
    delay(8000);                              
      
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
