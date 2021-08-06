#ifndef PLM_H
#define PLM_H


//PLM DIO
#define PD_DDR DDD7					//PLM power down
#define PD PIN7
#define DEBUG_LED_DDR DDD4	//DEBUG LED
#define DEBUG_LED PIN4

//PLM Commands
#define ACK	  0x00	        //Acknowledge
#define RDY 	0x01	        //Ready
#define IDQ 	0x02	        //ID query
#define BRDC 	0x03	        //Broadcast

//States
#define ON  1
#define OFF 0

//Flags
extern uint16_t ZERO_CROSS_FLAG;

//PLM MSG buffer
#define MAX_BUF_SIZE 50
extern char msgBuffer[MAX_BUF_SIZE];


//! Inits Powerline Modem
//! @return void
void PLM_init(
			);


//! Turns zero cross detection ON or OFF
//! @return void
void zero_cross_detection(uint8_t state             //state = ON detection is enabled, state = OFF detection is disabled
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
void PLM_send_msg( unsigned char data 				     //Data byte to transmit 
			   );

				  
					   

#endif  // PLM_H
