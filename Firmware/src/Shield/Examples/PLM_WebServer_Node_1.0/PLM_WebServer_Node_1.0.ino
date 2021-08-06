/*
 PLM_WebServer_Node.ino
 Author: Jarvis Hill (hilljarvis@gmail.com)
 Purpose: Show how to control the PLM Shield via a UDP socket from Python or any other UDP capable source.  
 Date: 15-MAR-2020

 USAGE:  1. Create a WebServer Node using a Seeed Studio Ethernet Shield, Arduino UNO and JARViE PLM Shield.
         2. Upload this sketch/firmware to the Arduino board
         3. Connect Ethernet Shield to desired LAN (local area network) by plugging in ethernet cable to home internet
         3. Run the python script from PC/tablet/mobile connected to the same network as the Ethernet Shield
         4. The Python script sends a UDP message through a network socket, The Ethernet Shield reads it.  If a PLM
            Shield is attached the UDP message is forwarded out on the powerlines the PLM is connected to.
         5. If WAN access (external network access to website) is desired, one must enable port forwarding on their router 
            for the ip address of the node (e.g.192.168.1.177). 
            See the WebServer Node Setup Guide for instructions: https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/tree/master/Reference%20Docs

 Verions:
  1.0 - Initial Release 
  
 References: 
 Arduino WebServer Ethernet Example by David A. Mellis, Tom Igoe and Arturi Guadalupi
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
*/

#include <SPI.h>
#include <Ethernet.h>
#include "USART.h"
#include "PLM.h"
#include "string.h"


/*GLOBALS*/

/*Ethernet Shield*/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 187);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(84);

String readString;


/*PLM*/
uint16_t checksum = 0;
char msg[11]      = "RELAY_O";
char msg1[11]     = "RELAY_C";
char env_temp[11] = "TEMP";
char buf[6];
#define MAX_BUF_SIZE 50
char msgBuffer[MAX_BUF_SIZE];  // buffer to hold incoming packet


/*PROTOTYPES*/
void PLM_init();
void USART_Init( unsigned int ubrr);
uint16_t fletch_check( uint8_t *data, int count );
char *PLM_read_msg();
void PLM_send_msg( unsigned char data );


/*SETUP*/
void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  /*Init PLM IO*/
  PLM_init();

  /*Init USART*/
  cli();                                      //Disable interrupts
  USART_Init(MYUBRR);
  sei();                                      //Enable interrupts
  delay(1000);  

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    //Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    //Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();

  //Init Serial port
  //Serial.begin(9600);
  //Serial.print("server is at ");
  //Serial.println(Ethernet.localIP());
}


void loop() {
  
  //Init/clear temp cmd buffers
  char temp[11] = "";
  char temp1[11] = "";
  char sensorReading[MAX_BUF_SIZE] = "";
  
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }
        
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n') {
          //Serial.println(readString); //print to serial monitor for debuging
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          //Generate data page (could code below clean but didn't)
          if(readString.indexOf("cmd") >0){ //checks for 8

            /*Close Garage Door*/
            if(readString.indexOf("cmd_garage_switch") >0){

              /*Press garage door button*/
              //Calculate message checksum
              strcpy(temp,msg);
              checksum = fletch_check(temp, strlen(temp));    //Calculate Fletcher16 checksum
              sprintf(buf," %u\n",checksum);                  //Construct checksum buffer
              strcat(temp, buf);                              //Concatenate data message and checksum
              
              PORTD ^= (1<<DEBUG_LED);                        //Toggle DEBUG LED
              
              /*Press garage door button*/
              for (int j = 0; j < strlen(temp); j++){         //Send data to PLM Switch Node
                PLM_send_msg(temp[j]);                 
                delay(10);
              }

              delay(250);                                     //Delay 
              
              //Calculate message checksum
              strcpy(temp1,msg1);    
              checksum = fletch_check(temp1, strlen(temp1));  //Calculate Fletcher16 checksum
              sprintf(buf," %u\n",checksum);                  //Construct checksum buffer
              strcat(temp1, buf);                             //Concatenate data message and checksum

              //Send data to PLM Switch Node  
              for (int j = 0; j < strlen(temp1); j++){        //Send data to PLM Switch Node
                PLM_send_msg(temp1[j]);                 
                delay(10);
              }

            }

            /*Broadcast turn on battery charger cmd over PLM bus*/
            if(readString.indexOf("cmd_charger_on") >0){

              //Calculate message checksum
              strcpy(temp,msg);
              checksum = fletch_check(temp, strlen(temp));    //Calculate Fletcher16 checksum
              sprintf(buf," %u\n",checksum);                  //Construct checksum buffer
              strcat(temp, buf);                              //Concatenate data message and checksum
              
              PORTD ^= (1<<DEBUG_LED);                        //Toggle DEBUG LED
              
              /*Press garage door button*/
              for (int j = 0; j < strlen(temp); j++){         //Send data to PLM Switch Node
                PLM_send_msg(temp[j]);                 
                delay(10);
              }
            }

            /*Broadcast turn off battery charger cmd over PLM bus*/
            if(readString.indexOf("cmd_charger_off") >0){
              delay(250);                                     //Delay 
              
              //Calculate message checksum
              strcpy(temp1,msg1);    
              checksum = fletch_check(temp1, strlen(temp1));  //Calculate Fletcher16 checksum
              sprintf(buf," %u\n",checksum);                  //Construct checksum buffer
              strcat(temp1, buf);                             //Concatenate data message and checksum

              PORTD ^= (1<<DEBUG_LED);                        //Toggle DEBUG LED

              //Send data to PLM Switch Node  
              for (int j = 0; j < strlen(temp1); j++){        //Send data to PLM Switch Node
                PLM_send_msg(temp1[j]);                 
                delay(10);
              }

            }

            /*Read data from environment node*/
            if(readString.indexOf("cmd_update_env") >0){
              //Calculate message checksum
              strcpy(temp,env_temp);    
              checksum = fletch_check(temp, strlen(temp));  //Calculate Fletcher16 checksum
              sprintf(buf," %u\n",checksum);                //Construct checksum buffer
              strcat(temp, buf);                            //Concatenate data message and checksum

              PORTD ^= (1<<DEBUG_LED);                      //Toggle DEBUG LED
             
              /*Request Temperature from Environment Node*/    
              UCSR0B &= ~(1<<RXEN0);                        //Must Disable RX of MCU because PLM comms occur on the same wire 
                                                            //(PLM shield AC couples TX to RX)
              for (int j = 0; j < strlen(temp); j++){       //Send query message through USART
                PLM_send_msg(temp[j]);
                delay(10);
              }
      
              delay(100);                                   //Delay after last cmd byte is transmitted                           
              UCSR0B |= (1<<RXEN0);                         //Enable UART RX
              delay(100);                                   //Required delay to let MCU UART RX circuit to setup

              PLM_read_msg(msgBuffer, MAX_BUF_SIZE);        //Wait to receive evironment data
            
              strcpy(sensorReading,msgBuffer);              //Copy environment data into sensor reading buffer
           
              //Displays temperature of rooms listed below (the same temp is displayed for each room) 
              for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
              
                //int sensorReading = analogRead(analogChannel);
              
                switch (analogChannel){
                  case 0:
                    client.print ("Living Room ");
                    break;
                
                  case 1:
                    client.print ("Garage ");
                    break;
                
                  case 2:
                    client.print ("Attic ");
                    break;
                
                  case 3:
                    client.print ("Bedroom 1 ");
                    break;
  
                  case 4:
                    client.print ("Bedroom 2 ");
                    break;
                
                  case 5:
                    client.print ("Bedroom 3 ");
                    break;
  
                  default:
                    break;
                }
                client.print("Temperature: ");
                client.print(sensorReading);
                client.println("<br />");
              }
            }
            client.println("<HTML><HEAD>");
            client.println("<TITLE>Smart Home Status</TITLE>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<br></BODY></HTML>");
          }
          else
          {
            client.println("<HTML><HEAD><TITLE>Smart Home Status</TITLE>");  
            client.println("<H1>Smart Home Webpage Example</H1>");      
            
            // custom buttons
            client.print("Garage<BR>");
            client.print("&nbsp;&nbsp;&nbsp;&nbsp;<a href='http://192.168.1.187:84/cmd_garage_switch' target='DataBox' title=''xx''>OPEN/CLOSE</a><BR>");
            client.print("<BR>Battery Charger<BR>");
            client.print("&nbsp;&nbsp;&nbsp;&nbsp;<a href='http://192.168.1.187:84/cmd_charger_on' target='DataBox' title=''yy''>ON</a>");
            client.print("&nbsp;&nbsp;&nbsp;&nbsp;<a href='http://192.168.1.187:84/cmd_charger_off' target='DataBox' title=''zz''>OFF</a><BR>");
            client.print("<BR>Environment Dashboard<BR>");
            client.print("&nbsp;&nbsp;&nbsp;&nbsp;<a href='http://192.168.1.187:84/cmd_update_env' target='DataBox' title=''ww''>UPDATE DASHBOARD</a><BR>");
            
            //iframe
            client.print("<iframe src='http://192.168.1.187:84/cmd;' width='350' height='250' name='DataBox'>");
            client.print("</iframe><BR></HTML>");  
          }
          
          // give the web browser time to receive the data
          delay(1);
          
          // close the connection:
          client.stop();
          
          //clearing string for next read
          readString="";
        }
      }
    }
  }
}
