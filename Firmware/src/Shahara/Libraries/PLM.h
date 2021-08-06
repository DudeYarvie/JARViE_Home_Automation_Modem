#ifndef PLM_H
#define PLM_H


//PLM DIO
#define DEBUG_LED_DDR    DDD4	 //DEBUG LED
#define DEBUG_IO_PD3_DDR DDD3  //DEBUG GPIO
#define DEBUG_IO_PD5_DDR DDD5  //DEBUG GPIO
#define AC_RLY_DDR       DDD7  //AC PWR Relay
#define DEBUG_IO_PC4_DDR DDC4  //DEBUG GPIO
#define DEBUG_IO_PC5_DDR DDC5  //DEBUG GPIO

#define DEBUG_LED     PIND4
#define DEBUG_IO_PD3  PIND3
#define DEBUG_IO_PD5  PIND5
#define AC_RLY        PIND7
#define DEBUG_IO_PC4  PINC4
#define DEBUG_IO_PC5  PINC5


//PLM Commands (command structure not used)
/*
#define ACK	  0x00	        //Acknowledge
#define RDY 	0x01	        //Ready
#define IDQ 	0x02	        //ID query
#define BRDC 	0x03	        //Broadcast
*/

//PLM MSG buffer
#define MAX_BUF_SIZE 50
extern char msgBuffer[MAX_BUF_SIZE];


//! Inits Powerline Modem
//! @return void
void PLM_init(
			);


//! Calculates fletcher checksum on msg buffer contents
//! @return uint16_t
uint16_t fletch_check( uint8_t *data, int count     //data buffer and size to perofm checksum on
                     );



//! Receives powerline bus message and returns ACK
//! @return void
void PLM_read_msg(char *buf, int n
			   );
			   
			   
			   
//! Sends data byte through USART
//! @return void
void PLM_send_msg( unsigned char data 				   //Data byte to transmit 
			   );

				  
					   

#endif  // PLM_H
