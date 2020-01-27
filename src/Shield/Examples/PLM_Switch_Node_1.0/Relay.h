#ifndef RELAY_H
#define RELAY_H


//Relay DIO
/*
If using the JARViE PLM RELAY4 and RELAY1 can't be used.  
They conflict with PLM control signals.
#define PD_DDR DDD7				//PLM power down
#define PD PIN7
#define DEBUG_LED_DDR DDD4	 	//DEBUG LED
#define DEBUG_LED PIN4
*/
#define RELAY3_DDR DDD5
#define RELAY3 PIN5
#define RELAY2_DDR DDD6
#define RELAY2 PIN6

//Commands
#define NO_RELAY 1
#define NC_RELAY 0  



//! Inits Seeed Studio Relay Shield v3 I/O
//! @return void
void RELAY_init(
			);

/*
//! Calculates fletcher checksum on msg buffer contents
//! @return uint16_t
uint16_t fletch_check( uint8_t *data, int count     //data buffer and size to perofm checksum on
                     );



//! Receives powerline bus message and returns ACK
//! @return *char
char *PLM_read_msg(
			   );
			   
			   
			   
//! Sends data byte through USART
//! @return void
void PLM_send_msg( unsigned char data 				   //Data byte to transmit 
			   );
*/
				  
					   

#endif  // RELAY_H
