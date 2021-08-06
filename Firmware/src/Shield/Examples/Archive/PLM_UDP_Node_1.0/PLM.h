#ifndef PLM_H
#define PLM_H


//PLM DIO
#define PD_DDR DDD7						//PLM power down
#define PD PIN7
#define DEBUG_LED_DDR DDD4	 //DEBUG LED
#define DEBUG_LED PIN4

//PLM Commands
#define ACK	  0x00	        //Acknowledge
#define RDY 	0x01	        //Ready
#define IDQ 	0x02	        //ID query
#define BRDC 	0x03	        //Broadcast


//! Inits Powerline Modem
//! @return void
void PLM_init(
			);


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

				  
					   

#endif  // PLM_H
