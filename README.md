## JARViE Power Line Modem Demo Board
The JARViE PLM Demo Board offers users a simple and low-cost entry point into learning about Smart Home technology.  Couple this modem with a microcontroller to bi-directionally communicate with other devices or systems over AC or DC power lines. Applications include lighting control, home appliance control, and energy/heating control. 

The demo board highlights the NXP TDA5051A home automation modem. The TDA5051A is an amplitude shift key (ASK) power line modem that operates up to 1200 bits per second (bps) from a single +5VDC supply.  The receiver portion of the modem employs automatic gain control (AGC) at its input and the transmitter has output power overload protection. An 8-bit A-to-D converter and a narrow digital filter follow the AGC stage in the receiver. **The TDA5051A power line modem application solution is compliant with US FCC (Federal Communication Commission), Industry Canada, Japan MPT, and European CENELEC EN50065-1 regulations for signaling in the 125 kHz to 140 kHz and the 95 kHz to 125 kHz frequency bands.**  

![jarvie_plm_annotated](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/PLM_CCA_Annotated.jpg)

## Features
* Communicates over DC or 120V/240V AC power buses
* Requires single +5V @ 100 mA max power supply
* Optically coupled zero cross detection
* 1200 baud data rate (default)
* External clock input for baud rate adjustment, from microcontroller or an external oscillator IC
* Full digital carrier generation and shaping
* High clock rate of 6-bit D/A (Digital to Analog) converter for rejection of aliasing components
* Fully integrated output power stage with overload protection
* Automatic Gain Control (AGC) at receiver input
* 8-bit A/D (Analog to Digital) converter and narrow digital filtering
* Digital demodulation delivering baseband data

## How to Order
[Purchase demo board or full kit](https://www.tindie.com/products/jarvie/smart-home-power-line-modem-demo-board/)

<a href="https://www.tindie.com/stores/jarvie/?ref=offsite_badges&utm_source=sellers_JARViE&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>


## Quick Setup
1. Connect 120 or 240 AC power cord to PLM connector J1 per **Table 3**
2. Repeat step 1 for a second PLM demo board.
3. If you have the [PLM Demo Kit](https://www.tindie.com/products/jarvie/smart-home-power-line-modem-demo-board/) and the firmware hasn't been updated, skip to step 6.
2. Download the latest version of the Arduino IDE for your OS from the [Arduino website](www.Arduino.cc).
3. Download firmware from ***src*** directory of this repo.
4. Program an Adafruit Metro or equivalent (e.g. OSEPP UNO, Arduino UNO) with the ***Power_Line_Modem_Slave.ino***.
5. Program a second Adafruit Metro or equivalent with ***Power_Line_Modem_Master.ino***.
6. Connect each Adafruit Metro to a JARViE PLM demo board per **Table 4**.
7. Verify that power and ground connections between the Adafruit Metro and PLM are correct. 
8. Obtain a USB A to micro B or equivalent cable and a USB A wall adapter.
9. Plug the micro B end of the USB cable into the Adafruit Metro. 
10. Plug the A side of the USB cable into the wall adatper. 
11. Verify that your PLM slave and master devices resemble the setup reference figure below.
12. Verify that the AC power cord voltages are rated appropriately for the outlet you plan on plugging the PLMs into! 
13. Plug the AC power cord and wall adatper of the master device into a home outlet.
14. Once powered, the Adafruit Metro of the master device should blink 4 times every 12 seconds. After the red LED blinks, the master transmits: ***ASCII command string "IDN?" + Fletcher16 16 bit checksum (5 ASCII characters) + "\n" EOL character*** to slave devices connected to the power line.  
15. Plug the AC power cord and wall adatper of the slave device into another home outlet.
16. Within 30 seconds, the red LED on the Adafruit Metro of the slave device will blink 12 times every 12 seconds. The red LED blinks only when the "IDN?" command is received from the master device.  Notice that if you disconnect the master from the power line, the red LED on the slave device will not blink as long as the master is disconnected.

## PLM Slave/Master Setup Reference
![jarvie_plm_annotated](https://raw.githubusercontent.com/DudeYarvie/JARViE_Home_Automation_Modem/master/Reference%20Docs/Pics/Quick_Connect_PLM.jpg)

## Pin Mappings and Pinouts
### Table 1. Demo Board ***PLM DIO*** pin descriptions
| PLM DIO Pin | Description |
|:---:|:---:|
| 1 | Zero cross detector |
| 2 | Power down (active HIGH) |
| 3 | GND |
| 4 | PLM EXT CLK |
| 5 | PLM DATA_IN (active LOW) |
| 6 | GND |
| 7 | PLM DATA_OUT (active LOW)|
| 8 | PLM CLK OUT|

### Table 2. Demo Board ***PWR*** pin descriptions
| PWR Pin | Description |
|:---:|:---:|
| 1 | GND |
| 2 | +5V |
| 3 | GND |
| 4 | +5V |
| 5 | GND |
| 6 | +5V |
| 7 | GND |
| 8 | +5V |

### Table 3.  Demo Board Power Line Input connector J1 pin descriptions
| J1 Pin | AC/DC signal |
|:---:|:---:|
| 1 | AC LINE/DC_IN+ |
| 2 | AC Neutral/DC_IN- |
| 3 | N/C |

### Table 4. Adafruit Metro to PLM Demo Board Pin Map
| Adafruit Metro Pin | PLM Demo Board Connector Pin |
|:---:|:---:|
| +5V | J3 pin 2,4,6, or 8 |
| GND | J3 pin 1,3,5 or 7 |
| TX0 | J2 pin 5|
| RX0 | J2 pin 7|

## PLM Tx, Rx & Zero Cross Detection
### Data Transmission (DATA_IN to Tx Carrier Output Delay)
The following image shows the DATA_IN to Tx carrier output delay. The blue trace is a 1 kHz square wave driving the PLM's TDA5051A modem DATA_IN input. The yellow trace is the modulated ASK carrier wave transmitted to all PLMs on the power line network. The capture shows that there is approximately a 170 microsecond delay between setting the DATA_IN input and Tx carrier wave generation.
![DATA_IN_Tx_Carrier_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/DATA_IN%20to%20Tx%20carrier%20output%20delay%20annotated.PNG)

### Data Reception (Rx Carrier Input to DATA_OUT Delay) 
The following image shows the Rx carrier input to DATA_OUT output delay. The blue trace is the modulated ASK signal received through the AC inputs on the JARViE PLM. The yellow trace is the digital TDA5051A DATAOUT signal that can be interpreted with an MCU or equivalent UART compliant device. The capture shows that there is approximately a 180 microsecond delay between Rx carrier wave reception and the DATAOUT output.
![Rx_Carrier_DATA_OUT_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/Rx_carrier_input_to_DATA_OUT_delay_annotated.PNG)

### AC Zero Cross Detection
The main purpose of the PLM zero cross detection circuitry (ZCD) is to provide a method to synchronize devices to one another. The intent is to not have to share a clock between devices that are meters away. The output of the ZCD goes from 0 to +5V making it compatible with MCUs. By pairing the PLM with an MCU, the ZCD output can be used to trigger event timers, create task schedulers within a PLM network and or send messages when noise on the power line is smallest for best communication results (zero crossing point). The ZCD can also be used to measure the frequency of the AC power line.
![ZC_Scope_Capture](https://github.com/DudeYarvie/JARVIE_TDA5051A_Arduino/blob/master/Reference%20Docs/Pics/Zero_Cross_Detection_Capture_Annotate1.PNG)

* **A –** 120 VAC zero cross point.  Signal begins to rise to maximum amplitude but H11AA1 bi-directional optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **B –**  120 VAC rises high enough to bias NPN transistor in optocoupler pulling the zero cross detection signal LOW (0V).
* **C –**  120 VAC zero cross point.  Signal begins to fall to minimum amplitude.  H11AA1 optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **D –**  120 VAC falls low enough to bias NPN transistor in bi-directional optocoupler pulling the zero cross detection signal LOW (0V).


## Typical Application
<p align="center">
  <img src="https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/JARViE_PLM_AC_Application.png">
</p>
