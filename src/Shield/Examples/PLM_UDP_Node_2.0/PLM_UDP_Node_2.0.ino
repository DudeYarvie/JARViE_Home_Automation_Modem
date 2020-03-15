/*
          PLM_UDP_Node.ino 
Author: Jarvis Hill (hilljarvis@gmail.com)
Purpose: Show how to control the PLM Shield via a UDP socket from Python or any other UDP capable source.  
Date: 14-MAR-2020

USAGE:   1. Create a PLM UDP Node using a Seeed Studio Ethernet Shield, Arduino UNO and PLM Shield.
         2. Upload this sketch/firmware to the Arduino board
         3. Connect Ethernet Shield to desired LAN (local area network) by plugging in ethernet cable to home internet
         3. Run the python script from PC/tablet/mobile connected to the same network as the Ethernet Shield
         4. The Python script sends a UDP message through a network socket, The Ethernet Shield reads it.  If a PLM
            Shield is attached the UDP message is forwarded out on the powerlines the PLM is connected to.
         
References: UDPSendReceiveString.ino authored by Michael Margolis on 21-AUG-2010.
Releases: 
          1.0 - Initial Release
          2.0 - Added timeout for PLM communications in PLM.cpp.  One can remove timeout if comms will only be sent from master to slave.  
                If bi-directional comms or handshaking between master and slave is desired, invoking a timeout is encouraged so the PLM bus 
                does not hang when comms are unsucessful.
*/


/*INCLUDES*/
#include <SPI.h>                 //Needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         //UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include "USART.h"
#include "PLM.h"


/*GLOBALS*/

/*PLM*/
uint16_t checksum = 0;
char msg[11] = "RELAY";
char buf[6];
byte read_flag= 0; 


/*Ethernet*/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

unsigned int localPort = 8888;                    //Local port to listen on

//Buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]="";        //Buffer to hold incoming packet
char  ReplyBuffer[UDP_TX_PACKET_MAX_SIZE]="";         // a string to send back

//An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


/*PROTOTYPES*/
void PLM_init();
void USART_Init( unsigned int ubrr);
uint16_t fletch_check( uint8_t *data, int count );
char *PLM_read_msg();
void PLM_send_msg( unsigned char data );


/*SETUP*/
void setup() {

  /*Init PLM IO*/
  PLM_init();

  /*Init USART*/
  cli();                                      //Disable interrupts
  USART_Init(MYUBRR);
  sei();                                      //Enable interrupts
  delay(1000);                                //Delay
 
  /*start the Ethernet and UDP:*/
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

}



/*MAIN PROGRAM*/
void loop() {
  
  /*Clear UDP buffer*/
  memset(packetBuffer,'\0',UDP_TX_PACKET_MAX_SIZE);
  
  /*if there's data available, read a packet*/
  int packetSize = Udp.parsePacket();
                                     
  
  if (packetSize) {
 
    /* read the packet into packetBufffer*/
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
       
    /*Calculate message checksum*/
    strcpy(msg,packetBuffer);                               //Copies UDP packet buffer into msg buffer
    checksum = fletch_check(msg, strlen(msg));              //Calculate Fletcher16 checksum
    sprintf(buf," %u\n",checksum);                          //Construct checksum buffer
    strcat (msg, buf);                                      //Concatenate data message and checksum
    
    /*Check if cmd requires a response*/
    read_flag=0;                                            //Clear read_flag
    if(strncmp(msg,"TEMP",strlen("TEMP"))==0) read_flag=1;       
    if(strncmp(msg,"HUM",strlen("HUM"))==0)   read_flag=1;       
    if(strncmp(msg,"GAS",strlen("GAS"))==0)   read_flag=1;       
    
    for (int i = 0; i <= 4; i++){                           //Blink DEBUG LED to visually indicate data message will be sent shortly
      PORTD ^= (1<<DEBUG_LED);                              //Toggle DEBUG LED
      delay(150);                                           //Delay
    }

    /*Send UDP string/command to PLM other device*/    
    UCSR0B &= ~(1<<RXEN0);                                  //Must Disable RX of MCU because PLM comms occur on the same wire 
                                                            //(PLM shield AC couples TX to RX)
    for (int j = 0; j < strlen(msg); j++){                  //Send message through USART
      PLM_send_msg(msg[j]);
      delay(10);
    }
    
    delay(100);                                             //Delay after last cmd byte is transmitted                           
    UCSR0B |= (1<<RXEN0);                                   //Enable UART RX
    delay(100);                                             //Required delay to let MCU UART RX circuit to setup


    //IF response required from PLM Node
    if(read_flag == 1){
      PLM_read_msg(ReplyBuffer, UDP_TX_PACKET_MAX_SIZE);
      delay(10);
      //if (strlen(ReplyBuffer) == 0) Serial.println("NAN");
      
      //Sends data through UDP socket if buffer is not empty
      if (strlen(ReplyBuffer) != 0){
        //Send a reply to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
      }
    }
  }
}
