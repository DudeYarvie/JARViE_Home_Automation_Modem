## JARViE Power-Line Modem Demo Board
The JARViE PLM Demo Board offers users a simple and low-cost entry point into learning about Smart Home technology.  Couple this modem with a microcontroller to bi-directionally communicate with other devices or systems over AC or DC power lines. Applications include lighting control, home appliance control, and energy/heating control. 

The demo board highlights the NXP TDA5051A home automation modem. The TDA5051A is an amplitude shift key (ASK) power line modem that operates up to 1200 bits per second (bps) from a single +5VDC supply.  The receiver portion of the modem employs automatic gain control (AGC) at its input and the transmitter has output power overload protection. An 8-bit A-to-D converter and a narrow digital filter follow the AGC stage in the receiver. **The TDA5051A power line modem application solution is compliant with US FCC (Federal Communication Commission), Industry Canada, Japan MPT, and European CENELEC EN50065-1 regulations for signaling in the 125 kHz to 140 kHz and the 95 kHz to 125 kHz frequency bands.**  

![jarvie_plm_annotated](https://user-images.githubusercontent.com/27718143/45259303-4559ac00-b38f-11e8-8edd-c1154aa8aab7.png)

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

## Typical Application
<p align="center">
  <img src="https://github.com/DudeYarvie/JARVIE_TDA5051A_Arduino/blob/master/Reference%20Docs/Typical_App.PNG">
</p>


## QUICK SETUP
1. Connect Line to Line, and Neutral to Neutral.
2. Connect +5 V DC to pin 1.
3. Connect GND to pin 3 and pin 5.
4. Set pulse generator to square wave (0 V to 5 V), 1200 Hz, 50 % duty cycle.

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


## Arduino Library for JARVIE TDA5051A Power Line Modem Demo Board
C++ library is provided in src directory.  Below is a list of file descriptions.
