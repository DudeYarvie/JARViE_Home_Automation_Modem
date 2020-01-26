#include "USART.h"
#include <HardwareSerial.h>


/*******************************************************************************
 * USART_Init
 * Purpose: Configures and enables USART 
 *******************************************************************************/
void USART_Init( unsigned int ubrr)
{
 
 /*Disable interrupts*/
 //cli();
 
 /*Set baud rate */
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
 /*Enable receiver and transmitter */
 UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0);
 /* Set asynchronous UART with frame format: 8data, 1stop bit */
 UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<USBS0)|(3<<UCSZ00);

 /*Enable global interrupts*/
 //sei();

 
}


/*******************************************************************************
 * USART_Transmit
 * Purpose: Sends specified data byte out through USART
 *******************************************************************************/
void USART_Transmit( unsigned char data )
{
 /* Wait for empty transmit buffer */
 while ( !( UCSR0A & (1<<UDRE0)) );
 /* Put data into buffer, sends the data */
 UDR0 = data;
}
