# JARVIE Arduino Library for JARVIE TDA5051A Power Line Modem Demo Board
The TDA5051A is a modem IC, specifically dedicated to ASK transmission by means of the home power supply network, at 600 baud or 1200 baud data rate. It operates from a single 5 V supply.

### Features
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


### JARVIE TDA5051A Power-Line Modem Demo Board
The JARVIE TDA5051A highlights the NXP TDA5051A home automation modem. Couple this modem with any microcontroller project to bi-directionally communicate with other devices or systems over a shared power-bus. Said another way, the modem enables communication over the same wires that are used to power the system.  
![jarvie_plm_annotated](https://user-images.githubusercontent.com/27718143/45259303-4559ac00-b38f-11e8-8edd-c1154aa8aab7.png)


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


### Connecting the board

### Test setup
1. Connect Line to Line, and Neutral to Neutral.
2. Connect +5 V DC to pin 1.
3. Connect GND to pin 3 and pin 5.
4. Set pulse generator to square wave (0 V to 5 V), 1200 Hz, 50 % duty cycle.
