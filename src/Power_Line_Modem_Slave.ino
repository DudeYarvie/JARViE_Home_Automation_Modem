/**
Power_Line_Modem_Slave.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Firmware for powerline modem slave device
Date: 14-JUNE-2019
References: TDA5051A datasheet
**/

/*INCLUDES*/
#include "USART.h"


/*GLOBALS*/
//PLM DIO
#define PD_DDR  DDD7
#define PD      PIN7
#define LED_DDR DDB5
#define LED     PIN5


/*PROTOTYPES*/
void init_io();
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
uint16_t fletch_check( uint8_t *data, int count );
char *recv_cmd();

/*******************************************************************************
 * init_io
 * Purpose: Init powerline modem I/O
 *******************************************************************************/
void init_io(){
  
  DDRD  |= (1 << PD_DDR);      
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


/*******************************************************************************
 * recv_cmd
 * Purpose: Receives and interprets commands from master powerline modem
 *******************************************************************************/
char *recv_cmd(){

  /*Init local variables*/
  char temp[100];
  char buf[100];
  char payload[100];
  int i=0;

  for (i = 0; i< 100; i++)
    temp[i]=0;
    buf[i]=0;

  uint8_t char_count = 0;
  uint16_t rx_checksum = 0;
  uint16_t tx_checksum = 0;
  uint8_t r = 0;


  /*Wait for data from Host PLM*/
  while(1){
    while ( !(UCSR0A & (1<<RXC0)) );                               //Wait until a character is available
    r = UDR0;
    if (r < 127){                                                  //Filters out extra character received at start of cmd string
      temp[char_count++] = (char)r;                                //Store char received into buffer
    }
    else{
      continue;
    }
    if(temp[char_count-1] == '\n') break;                          //Break loop once EOL char received
  }
  
  temp[char_count]= 0;                                             //Add space at the end of the recevied buffer

  //Serial.print(temp);                                            //Print received buffer for debugging

  /*Parse rx buffer for command and tx checksum*/
  sscanf(temp,"%s %u", payload, &tx_checksum);
  rx_checksum = fletch_check(payload, strlen(payload));            //Calculate Fletcher16 checksum of rx buffer                           
  sprintf(buf, "%s %u %u\n", payload, tx_checksum, rx_checksum);   //Construct string buffer that prints cmd, rx and tx checksum for debugging
  Serial.print(buf);                                            

  /*Check if the IDN? cmd was received from Host*/
  if(strncmp(temp,"IDN?",strlen("IDN?"))==0){                     //IF host cmd is "IDN?"
    for (int i=0;i<strlen(temp-1);i++){                           //Blink the debug LED
      
      digitalWrite(13, LOW);
      delay(250);
      digitalWrite(13, HIGH);
      delay(250);
      
    }
    //Serial.println(strlen(buf));                              //Print cmd length for DEBUGGING
  }

  return buf;
}


void setup() {

  /*Init PLM IO*/
  init_io();

  /*Init USART*/
  cli();                  //Stop interrupts
  USART_Init(MYUBRR);
  sei();                  //Start interrupts
  delay(1000);            //delay

}


void loop() {

  /*Wait for command from master powerline modem*/
  recv_cmd();

}
