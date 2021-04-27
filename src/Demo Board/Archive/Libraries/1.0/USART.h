#ifndef USART_H
#define USART_H


#define FOSC 16000000 //  Clock Speed
#define BAUD 1200
#define MYUBRR FOSC/16/BAUD-1


//! Inits SPI
//! @return void
void USART_Init( unsigned int ubrr						//register that sets baud rate
               );


//! Sends data byte through USART
//! @return void
void USART_Transmit( unsigned char data 				//Data byte to transmit 
				   );								
					  
					   

#endif  // USART_H
