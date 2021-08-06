#include <Arduino.h>            //Includes all the above headers and the delay function
#include "PLM.h"
#include "USART.h"
#include "Timers.h"


/*DECLARATIONS*/
volatile uint32_t CNTR_TICKS = 0;                 //Counter for TIMER0 ticks
uint16_t ZERO_CROSS_FLAG = 0;                     //Zero cross detection flag TRUE when INT0 is active and AC mains has crossed zero


/*INTERRUPTS*/
/**********************************************************************
 * TIMER2 COMPA Interrupt VECTOR
 * Purpose: Tracks 1ms ticks
 **********************************************************************/
SIGNAL(TIMER2_COMPA_vect) 
{

  CNTR_TICKS += 1;                                 //Increment tick counter.  Ticks every 200 microseconds

}


/**********************************************************************
 * External Interript 0 VECTOR
 * Purpose: Execute the following code when a rising edge occurs 
 **********************************************************************/
ISR(INT0_vect){

    ZERO_CROSS_FLAG = 1;                           //Set manual shutdown switch pressed flag
}


/****************************************************************************
 * zero_cross_detection
 * Purpose: Turns zero cross detection ON or OFF
 ***************************************************************************/
void zero_cross_detection(uint8_t state){
  
  //Configure external interrupt INT0 (Arduino digital pin 2) to trigger on any rising edge
  EICRA |= (1<<ISC01)|(1 << ISC00);

  ZERO_CROSS_FLAG = 0;                            //Reset zero cross flag to 0
  
  if (state == ON) EIMSK  |=   (1 << INT0);       //Enable external interrupt INT0
  if (state == OFF) EIMSK &= ~(1 << INT0);        //Disable external interrupt INT0  
  
}


/*******************************************************************************
 * PLM_init
 * Purpose: Init powerline modem I/O
 *******************************************************************************/
void PLM_init(){
  
  //Setup PLM Shield I/O
  DDRD |= (1 << PD_DDR) | (1 << DEBUG_LED_DDR);      
  PORTD &= ~(1 << PD) | ~(1 << DEBUG_LED); 

  //Clear external interrupt control register (e.g. INT0, INT1, etc.)
  EICRA = 0;      

  //Setup TIMER0 in order to imployment timeouts during PLM comms
  config_timers();

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
void PLM_read_msg(char *buf, int n){

  /*Init local variables*/
  char temp[n];
  char payload[n];
  int i=0;

  for (i = 0; i< n; i++){
    temp[i]=0;
    buf[i]=0;
  }
  
  uint8_t char_count = 0;
  uint16_t rx_checksum = 0;
  uint16_t tx_checksum = 0;
  uint8_t r = 0;

  /*Wait for data from Host PLM*/
  TIMSK2 |= (1 << OCIE2A);                                         //Enable timer compare interrupt for Timer/Counter0 Output Compare Match A
  while(1){
    while ( !(UCSR0A & (1<<RXC0)) && (CNTR_TICKS < 50000));        //Wait until a character is available or comm timeout is reached

    if (CNTR_TICKS >= 50000) break;                                //Exit loop if 5 sec timout occurs or reset timer if char received

    r = UDR0;                                                      
    if (r < 127){                                                  //Filters out non-characters from messages (might need to filter for aA-zZ and 0-9 digits only)
      CNTR_TICKS = 0;
      temp[char_count++] = (char)r;                                //Store char received into buffer
    }
    else{
      continue;
    }
    if(temp[char_count-1] == '\n') break;                          //Break loop once EOL char received
  }
  TIMSK2 &= ~(1 << OCIE2A);                                        //Disable timer compare interrupt for Timer/Counter0 Output Compare Match A
  CNTR_TICKS = 0;                                                  //Reset tick counter

  memcpy(buf,temp,n);                                              //Copy received message into global message buffer
                                 
}


/*******************************************************************************
 * PLM_send_msg
 * Purpose: Sends message over powerline bus
 *******************************************************************************/
void PLM_send_msg( unsigned char data ){
    USART_Transmit(data);
}





/*MISC. CODE*/
  /*Parse rx buffer for command and tx checksum*/
  //sscanf(temp,"%s %u", payload, &tx_checksum);
  //rx_checksum = fletch_check(payload, strlen(payload));            //Calculate Fletcher16 checksum of rx buffer                           
  //sprintf(buf, "%s %u %u\n", payload, tx_checksum, rx_checksum); //Construct string buffer that prints cmd, rx and tx checksum for debugging
  //Serial.print(buf);                                             //Print received buffer for debugging (uncommenting this line impedes PLM comms)                                    

//  /*Check if the IDN? cmd was received from Host*/
//  if(strncmp(buf,"IDN?",strlen("IDN?"))==0){                     //IF host cmd is "IDN?"
//    for (int i=0;i<strlen(buf);i++){                             //Blink the debug LED
//      
//      PORTD ^= (1<<DEBUG_LED);                                    //Toggle DEBUG LED
//      delay(250);                                                 //Delay 
//    }
//    //Serial.println(buf);                                //Print cmd length for DEBUGGING
//  }
 
