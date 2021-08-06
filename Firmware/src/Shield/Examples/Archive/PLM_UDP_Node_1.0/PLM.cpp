//#include <stdint.h>             //Standard C/C++ type header which defines uint8_t/16_t/etc.  
//#include <avr/iom328p.h>        //Provides definitions for Atmega328p GPIO registers (e.g. DDRD/DDRB)
//#include <avr/sfr_defs.h>       //The entire IO address space is made available as memory-mapped IO. Permits DDRD |= (1 << )
//#include <pins_arduino.h>       //Arduino pin mappings. Permits usage of PIN# references.
//#include <stdio.h>              //Header defines scanf, sprintf functions
//#include <string.h>             //Header defines string functions (e.g. strlen, strncmp) 
#include <Arduino.h>            //Includes all the above headers and the delay function
#include "PLM.h"
#include "USART.h"




/*******************************************************************************
 * PLM_init
 * Purpose: Init powerline modem I/O
 *******************************************************************************/
void PLM_init(){
  
  DDRD |= (1 << PD_DDR) | (1 << DEBUG_LED_DDR);      
  PORTD &= ~(1 << PD) | ~(1 << DEBUG_LED); 

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



/*******************************************************************************
 * PLM_read_msg
 * Purpose: Receives and interprets messages sent over powerline bus
 *******************************************************************************/
char *PLM_read_msg(){

  /*Init local variables*/
  char temp[100];
  char buf[100];
  char payload[100];
  int i=0;

  for (i = 0; i< 100; i++){
    temp[i]=0;
    buf[i]=0;
  }
  
  uint8_t char_count = 0;
  uint16_t rx_checksum = 0;
  uint16_t tx_checksum = 0;
  uint8_t r = 0;


  /*Wait for data from Host PLM*/
  while(1){
    while ( !(UCSR0A & (1<<RXC0)) );                               //Wait until a character is available
    r = UDR0;
    if (r < 127){                                                  //Filters out non-characters from messages
      temp[char_count++] = (char)r;                                //Store char received into buffer
    }
    else{
      continue;
    }
    if(temp[char_count-1] == '\n') break;                          //Break loop once EOL char received
  }
  
  temp[char_count]= 0;                                             //Add space at the end of the recevied buffer

  //Serial.print(temp);                                            //Print received buffer for debugging (uncommenting this line impedes PLM comms)

  /*Parse rx buffer for command and tx checksum*/
  sscanf(temp,"%s %u", payload, &tx_checksum);
  rx_checksum = fletch_check(payload, strlen(payload));            //Calculate Fletcher16 checksum of rx buffer                           
  sprintf(buf, "%s %u %u\n", payload, tx_checksum, rx_checksum);   //Construct string buffer that prints cmd, rx and tx checksum for debugging
  //Serial.print(buf);                                             //Print received buffer for debugging (uncommenting this line impedes PLM comms)                                    

  /*Check if the IDN? cmd was received from Host*/
  if(strncmp(temp,"IDN?",strlen("IDN?"))==0){                     //IF host cmd is "IDN?"
    for (int i=0;i<strlen(temp-1);i++){                           //Blink the debug LED
      
      PORTD ^= (1<<DEBUG_LED);                                    //Toggle DEBUG LED
      delay(250);                                                 //Delay
    }
    //Serial.println(strlen(buf));                                //Print cmd length for DEBUGGING
  }

  return buf;
}


/*******************************************************************************
 * PLM_send_msg
 * Purpose: Sends message over powerline bus
 *******************************************************************************/
void PLM_send_msg( unsigned char data ){
    USART_Transmit(data);
}
 
 
