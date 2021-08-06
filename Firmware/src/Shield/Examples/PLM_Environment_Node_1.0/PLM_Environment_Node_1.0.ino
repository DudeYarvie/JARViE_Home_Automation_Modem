/**
PLM_Environment_Node.ino
Author: Jarvis Hill (hilljarvis@hotmail.com)
Purpose: Firmware for the JARViE PLM Environment Node
Date: 14-MAR-2020
References: TDA5051A datasheet
Releases: 
            1.0 - Intial release
            
**/

/*INCLUDES*/
#include "USART.h"
#include "PLM.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME680.h"


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

/*GLOBALS*/
#define MAX_BUF_SIZE 50
char msgBuffer[MAX_BUF_SIZE];                           // buffer to hold incoming packet

/*PROTOTYPES*/
void PLM_init();
void USART_Init( unsigned int ubrr);
void PLM_read_msg(char *buf, int n);
uint16_t fletch_check( uint8_t *data, int count );


void setup() {

  /*Init PLM IO*/
  PLM_init();

  /*Init USART*/
  cli();                                                          //Stop interrupts
  USART_Init(MYUBRR);                                             //Decide whether or not to include this in PLM_Init
  sei();                                                          //Start interrupts
  delay(500);                                                     //delay

  /*Init Environment Sensor*/
  bme.begin();
  
  delay(100);

  /*Set up oversampling and filter initialization*/
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

}


void loop() {
  
  /*Wait for command from master powerline modem*/
  PLM_read_msg(msgBuffer, MAX_BUF_SIZE);  

  //Turn on DEBUG LED when cmd received
  PORTD ^= (1 << DEBUG_LED_DDR);

  /*Read Environmental Sensor*/
  bme.performReading();
  delay(500);                                                                                               //Required delay to allow PLM NODE that sent message time to receive response

  /*Check if one of the environmental node cmds were received from Host*/
  if(strncmp(msgBuffer,"TEMP",strlen("TEMP"))==0) Serial.println(bme.temperature, 2);                       //Sends temperature
  if(strncmp(msgBuffer,"PRES",strlen("PRES"))==0) Serial.println(bme.pressure / 100.0);                     //Sends pressure
  if(strncmp(msgBuffer,"HUM",strlen("HUM"))==0)   Serial.println(bme.humidity);                             //Sends Humidity
  if(strncmp(msgBuffer,"GAS",strlen("GAS"))==0)   Serial.println(bme.gas_resistance / 1000.0);              //Sends GAS
  if(strncmp(msgBuffer,"ALT",strlen("ALT"))==0)   Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA));   //Sends altitude
     
}
