## JARViE Power-Line Modem Demo Board
The JARViE PLM Demo Board offers users a simple and low-cost entry point into learning about Smart Home technology.  Couple this modem with a microcontroller to bi-directionally communicate with other devices or systems over AC or DC power lines. Applications include lighting control, home appliance control, and energy/heating control. 

The demo board highlights the NXP TDA5051A home automation modem. The TDA5051A is an amplitude shift key (ASK) power line modem that operates up to 1200 bits per second (bps) from a single +5VDC supply.  The receiver portion of the modem employs automatic gain control (AGC) at its input and the transmitter has output power overload protection. An 8-bit A-to-D converter and a narrow digital filter follow the AGC stage in the receiver. **The TDA5051A power line modem application solution is compliant with US FCC (Federal Communication Commission), Industry Canada, Japan MPT, and European CENELEC EN50065-1 regulations for signaling in the 125 kHz to 140 kHz and the 95 kHz to 125 kHz frequency bands.**  

![jarvie_plm_annotated](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/PLM_CCA_Annotated.jpg)

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

### DATA_IN to Tx Carrier Output Delay
![DATA_IN_Tx_Carrier_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/DATA_IN%20to%20Tx%20carrier%20output%20delay%20annotated.PNG)

### Rx Carrier Input to DATA_OUT Delay 
![Rx_Carrier_DATA_OUT_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Rx_carrier_input_to_DATA_OUT_delay_annotated.PNG)

### AC Zero Cross Detection
![ZC_Scope_Capture](https://github.com/DudeYarvie/JARVIE_TDA5051A_Arduino/blob/master/Reference%20Docs/Zero_Cross_Detection_Capture_Annotate1.PNG)

* **A –** 120 VAC zero cross point.  Signal begins to rise to maximum amplitude but H11AA1 bi-directional optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **B –**  120 VAC rises high enough to bias NPN transistor in optocoupler pulling the zero cross detection signal LOW (0V).
* **C –**  120 VAC zero cross point.  Signal begins to fall to minimum amplitude.  H11AA1 optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **D –**  120 VAC falls low enough to bias NPN transistor in bi-directional optocoupler pulling the zero cross detection signal LOW (0V).


## Typical Application
<p align="center">
  <img src="https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/JARViE_PLM_AC_Application.png">
</p>


## QUICK SETUP
1. Connect 120 or 240 AC power cord to PLM connector J1 per **Table 3**
2. Repeat step 1 for a second PLM demo board.
2. Download the latest version of the Arduino IDE for your OS from the Arduino website.
3. Download firmware from ***src*** directory of this repo.
4. Program an Arduino UNO or equivalent (e.g. OSEPP UNO, Adafruit Metro) with the ***Power_Line_Modem_Slave.ino***
5. Program a second Arduino UNO or equivalent with ***Power_Line_Modem_Master.ino***
6. Connect each Arduino UNO to a PLM per **Table 4**
7. Verify that power and ground connections between the Arduino UNO and PLM are correct. 
8. Obtain a USB A to micro B cable and a USB A wall adapter
9. Plug the micro B side of the USB cable into the micro USB
8. Verify that your PLM slave and master devices resemble the figure below.
9. Plug in the AC adapter a

### Table 1. PLM DIO pin descriptions
| Pin | Description |
|:---:|:---:|
| 1 | Zero cross detector |
| 2 | Power down (active HIGH) |
| 3 | GND |
| 4 | PLM EXT CLK |
| 5 | PLM DATA_IN (active LOW) |
| 6 | GND |
| 7 | PLM DATA_OUT (active LOW)|
| 8 | PLM CLK OUT|

### Table 2. Demo Board PWR pin descriptions
| Pin | Description |
|:---:|:---:|
| 1 | GND |
| 2 | +5V |
| 3 | GND |
| 4 | +5V |
| 5 | GND |
| 6 | +5V |
| 7 | GND |
| 8 | +5V |

### Table 3. Power Line Input pin descriptions
| Pin | Description |
|:---:|:---:|
| 1 | AC LINE/DC_IN+ |
| 2 | AC Neutral/DC_IN- |
| 3 | N/C |

### Table 4. Arduino UNO to PLM Pin Map
| Arduino Pin | PLM Connector Pin |
|:---:|:---:|
| +5V | J3 pin 2,4,6, or 8 |
| GND | J3 pin 1,3,5 or 7 |
| TX0 | J2 pin 5|
| RX0 | J2 pin 7|



## Arduino Library for JARVIE TDA5051A Power Line Modem Demo Board
C++ library is provided in src directory.  Below is a list of file descriptions.
