# JARViE Power Line Modem Demo Boards
The PLM Breakout Board, Shield, HAT and Shahara are compatible, simple and low-cost solutions for creating a DIY IOT project or developing consumer product using power line telecommunications. The breakout board and shield are compatible with Arduino development boards. The HAT is compatible with the Rasperrby Pi single board computer. The Shahara is a compact all-in-one solution combining MCU and powerline modem circuitry on one board. These power line modem solutions are compliant with US FCC (Federal Communication Commission), Industry Canada, Japan MPT, and European CENELEC EN50065-1 regulations for signaling in the 125 kHz to 140 kHz and the 95 kHz to 125 kHz frequency bands.

# Table of Contents
<details><summary>click to expand or hide</summary>

 1. [Demo Boards](#Demo_Boards)
      - [Breakout Board](#Breakout_Board)
      - [Arduino Shield](#Arduino_Shield)
      - [RPI HAT](#RPI_HAT)
      - [Shahara](#Shahara)   
 2. [Main Features](#Main_Features)
 3. [Applications](#Applications)
      - [Smart Home](#Smart_Home)
      - [PLM Repeater](#PLM_Repeater)
      - [DC Power Line](#DC_Power_Line)
      - [Custom User Interface](#Custom_User_Interface)
      - [Synchronizing Devices to the PLM Clock](#Synchronizing_Devices_to_the_Powerline_Modem_Clock)
 4. [Quick Setup](#Quick_Setup)
 5. [Electrical Specifications](#Electrical_Specifications)
      - [Powerline Communications Spectrum](#Powerline_Communications_Spectrum)
      - [Data Transmission](#Data_Transmission)
      - [Zero Cross Detection](#AC_Zero_Cross_Detection)   
      - [Pin Mappings and Pinouts](#Pin_Mappings_and_Pinouts)
 7. [How to Order Demo Boards](#How_to_Order_Development_Boards)
 8. [Request Custom Design Services](#Custom_Application_Development_Services)

</details>

<a name="Demo_Boards"></a>
# Demo Boards

<a name="Breakout_Board"></a>
### **Breakout Board**
The breakout board does just that, it breaks out power line modem control and power signals to a header. This provides flexibility to control PLM communications from something other than an Arduino. This PLM solution is also a cheaper, bear-bones alternate, to the shield because it does not possess the AC to DC converter.  This board functions similar to the NXP OM13313-598 Demo Kit but it's a fraction of the price.  Like the OM13313 Demo Kit, this board does not receive power from the same wires it communicates over.  The DC power required by the breakout board components must be supplied seperate from the power lines used for communications.  

![jarvie_plm_annotated](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/PLM_CCA_Annotated.jpg)

<a name="Arduino_Shield"></a>
### **Arduino Shield** 
Stack the shield on top of one of the many MCU development boards with the recognizable Arduino Shield footprint and you instantly have a ***smart*** node that can communicate to appliances, lighting, garage doors and sensors over thousands of feet of home 120/240 AC or DC power lines with no other wires required (nodes receive power from the same wires they communicate over). Nodes can be accessed over the internet via web browsers and or C++/Python/MATLAB/LabVIEW applications.

![JARViE_PLM_Shield](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/raw/master/Reference%20Docs/Pics/PLM_Shield_r2_Annotate.png)

<a name="RPI_HAT"></a>
### **RPI HAT** 
Plug this HAT onto any Raspberry Pi (RPI) with a 40-pin HDR (e.g. Pi 1,3,4 and Zero) and you instantly have a powerful PLM gateway to controll your powerline communications network. The HAT has an onboard +5V AC/DC converter that powers the RPI and HAT digital circuitry directly from the powerline. **The gateway is an on-board computer making it Python developer friendly; PLM communications can be achieved using Pytohn scripting.** The gateway can be accessed over the internet via a remote desktop or SSH connection.

![JARViE_PLM_RPI_HAT](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/blob/master/Reference%20Docs/Pics/PLM_RPI_HAT_Annotate.png)

<a name="Shahara"></a>
### **Shahara**
The Shahara is a standalone miniature PLM development board measuring 2" x 2"; perfect for embedding into DIY or prototype designs.  It houses an onboard ATmega328p MCU for custom firmware development to create your custom smart home platform and or powerline smart home network.  An onboard +5V AC/DC converter powers digital circuitry directly from the 120 or 240VAC input wires that the module(s) communicate over.  

![JARViE_PLM_Shahara](https://raw.githubusercontent.com/DudeYarvie/JARViE_Home_Automation_Modem/master/Reference%20Docs/Pics/PLM_Shahara_Annotated.png)

<a name="Main_Features"></a>
## Main Features
* Communicates over +35V max DC or home 120V/240V AC power lines using ASK carrier wave generation
* Provides power to MCU dev board and expansion shields from power line input (+7V @ 300 mA from VIN pin)
* AC Mains isolation via high-frequency transformer for safety
* Zero cross detection for system synchronization and or line frequency measurements
* 600 to 1200 bps UART bus between modem and MCU (Arduino TX0 and RX0)
* Modem baud rate adjustment via external clock input
* Modem output overload protection
* Automatic gain control at modem's receiver input
* Modem power down control to reduce power consumption

<a name="Applications"></a>
# Applications

<a name="Smart_Home"></a>
## Smart Home 
A DIY smart home system is one of the many things you can create with the PLM Shield. The figure below illustrates a smart home application. The **Switch Node** provides on/off control of appliances, lighting and or opening/closing of garage doors. The **Environment Node** can monitor the indoor air quality of areas within your home. The **Internet Node** can host a webpage that displays the environmental data, as well as, clickable buttons to control appliances, lighting or garage doors. The webpage can be accessed from any mobile phone, PC or tablet connected to the internet; allowing you to access your DIY smart home network from inside your house or while your away.

![Smart_Home_Diagram](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/raw/master/Reference%20Docs/Pics/JARViE_Smart_Home_Diagram.jpg)

### Node examples include but not limited to,
* **Internet Node:** Ardunio UNO + PLM Shield + Ethernet Shield creates a node that can be controlled from outside of your home over the internet, host server applications to report data to a website for remote monitoring.

* **Environment Node:** Ardunio UNO + PLM Shield + Adafruit BME680 Breakout creates a node that can monitor temperature, pressure, humidity and VOCs in a room/area within your home.

* **Switch Node:** Ardunio UNO + PLM Shield + Relay Shield creates a node that can switch on/off AC appliances (e.g. fan, light, motor or high current DC actuators like solenoid valve)

<a name="PLM_Repeater"></a>
## PLM Repeater
In homes, outlets are typically on different circuits and or on different legs of a center tapped transformer depending on the amount of AC voltage the outlet is meant to deliver.  Here's a video explaining the basics of [home electrical wiring](https://www.youtube.com/watch?v=fJeRabV5hNU&list=PLoL84bGi9zeo8Xd___DXu2QQaOqr_55Ph&index=32). Powerline communications cannot be achieved over an infinite distance, it has it's limitations, because of this one may find that communications may be achievable between two adjacent rooms but not between outlets that are in rooms further apart. The JARViE PLM Shahara is the solution to achieve powerline communications between outlets on electrical circuits seperated by longer lengths of wire. The diagram below illustrates how to implement the solution by forming a JARViE PLM repeater. 

![Smart_Home_Diagram](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/blob/master/Reference%20Docs/Pics/JARViE_PLM_Repeater.png)

<a name="DC_Power_Line"></a>
## DC Power Line 
The following diagram illustrates how the PLM Shield should be connected to a DC power line. In this diagram, the DC power source can be a switch-mode power supply, solar panels with converted DC output, batteries, super capacitor, etc. **The DC power source should not exceed +35 VDC.**

When using a switch-mode power supply, it is best to filter the output to achieve the best powerline telecommunications. **L1** = 100 uH and **C** = 470 uF is a low-pass filter that prevents power supply noise from interfering with powerline communications. The filtering components are likely not required when using batteries or capacitors as the power source. 

The impedance of **C** decreases as freq. increases so a choke (**L2** = 100 uH) is recommended to prevent the capacitor from overloading/shorting the 1200 Hz powerline communications.  Using batteries and capacitors as the DC power source will have the same overloading affect, so a choke is recommended for these sources as well.

![DC_Power_Line_Diagram](https://raw.githubusercontent.com/DudeYarvie/JARViE_Home_Automation_Modem/master/Reference%20Docs/Pics/PLM_Shield_DC_Power_Line_Diagram.png)

<a name="Custom_User_Interface"></a>
## Custom User Interface
Communicate to PLM Network by creating a user interface. The following UI is an example that was developed using Python.  The application communicates with any PLM device in the network that has an IP address and that can send/receive messages using UDP packets (User Datagram Protocol).  The Python application is located in this repo at Firmware->Shield->Examples.

<p align="center">
  <img width="596" height="650" src="https://raw.githubusercontent.com/DudeYarvie/JARViE_Home_Automation_Modem/master/Reference%20Docs/Pics/JARVIE%20PLM%20User%20Interface%20Example.PNG">
</p>

<a name="Synchronizing_Devices_to_the_Powerline_Modem_Clock"></a>
## Synchronizing Devices to the Powerline Modem Clock
The TDA5051 powerline modem on the JARViE demo boards provides a representation of its on-chip oscillation frequency (fosc) to its CLK OUT pin at a frequency of fosc/2. This signal can be supplied to the PLM host controller or external peripheral for system syncrhonization, PLM operating freuency verification, etc.

![Typical_On-Chip_CLK_Config](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/blob/master/Reference%20Docs/Pics/Typical%20On-chip%20Clock%20Configuration.PNG)


![PLM_CLK_OUT](https://github.com/DudeYarvie/JARViE_Home_Automation_Modem/blob/master/Reference%20Docs/Pics/PLM_CLK_OUT.png)

<a name="Quick_Setup"></a>
# Quick Setup 
### Breakout Board
1. Connect 120 or 240 AC power cord to PLM connector J1 per **Table 3**
2. Repeat step 1 for a second PLM demo board.
3. If you have the [PLM Demo Kit](https://www.tindie.com/products/jarvie/smart-home-power-line-modem-demo-board/) and the firmware hasn't been updated, skip to step 6.
2. Download the latest version of the Arduino IDE for your OS from the Arduino website.
3. Download firmware from ***src*** directory of this repo.
4. Program an Adafruit Metro or equivalent (e.g. OSEPP UNO, Arduino UNO) with the ***Power_Line_Modem_Slave.ino***.
5. Program a second Adafruit Metro or equivalent with ***Power_Line_Modem_Master.ino***.
6. Connect each Adafruit Metro to a JARViE PLM demo board per **Table 4** in [Pin Mappings and Pinouts](#Pin_Mappings_and_Pinouts).
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

<a name="Electrical_Specifications"></a>
# Electrical Specifications

<a name="Powerline_Communications_Spectrum"></a>
## Powerline Communications Spectrum
All JARViE boards are set to brodcast powerline communications at 125 kHz. Here's a spectrum capture of a PLM Shahara plugged into a home outlet in North America. Note the signal magnitude at 125 kHz.  Also realize the signal magnitudes at other frequencies relative to the communications frequency.  For good powerline communicaions, the SNR (signl-to-noise ratio) of the communications frequency compared to surrounding frequencies (communications +/- 200 kHz) should be as large as possible. 

![Shahara Spectrum Capture](https://raw.githubusercontent.com/DudeYarvie/JARViE_Home_Automation_Modem/master/Reference%20Docs/Pics/Shahara_PLM_Spectrum_Measurent_dBV_0to1MEG.PNG)

<a name="Data_Transmission"></a>
## Data Transmission
### DATA_IN to Tx Carrier Output Delay
The following image shows the DATA_IN to Tx carrier output delay. The blue trace is a 1 kHz square wave driving the PLM's TDA5051A modem DATA_IN input. The yellow trace is the modulated ASK carrier wave transmitted to all PLMs on the power line network. The capture shows that there is approximately a 170 microsecond delay between setting the DATA_IN input and Tx carrier wave generation.
![DATA_IN_Tx_Carrier_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/DATA_IN%20to%20Tx%20carrier%20output%20delay%20annotated.PNG)

### Rx Carrier Input to DATA_OUT Delay
The following image shows the Rx carrier input to DATA_OUT output delay. The blue trace is the modulated ASK signal received through the AC inputs on the JARViE PLM. The yellow trace is the digital TDA5051A DATAOUT signal that can be interpreted with an MCU or equivalent UART compliant device. The capture shows that there is approximately a 180 microsecond delay between Rx carrier wave reception and the DATAOUT output.
![Rx_Carrier_DATA_OUT_Delay](https://raw.githubusercontent.com/DudeYarvie/JARVIE_TDA5051A_Arduino/master/Reference%20Docs/Pics/Rx_carrier_input_to_DATA_OUT_delay_annotated.PNG)

<a name="AC_Zero_Cross_Detection"></a>
## AC Zero Cross Detection 
The main purpose of the PLM zero cross detection circuitry (ZCD) is to provide a method to synchronize devices to one another. The intent is to not have to share a clock between devices that are meters away. The output of the ZCD goes from 0 to +5V making it compatible with MCUs. By pairing the PLM with an MCU, the ZCD output can be used to trigger event timers, create task schedulers within a PLM network and or send messages when noise on the power line is smallest for best communication results (zero crossing point). The ZCD can also be used to measure the frequency of the AC power line.
![ZC_Scope_Capture](https://github.com/DudeYarvie/JARVIE_TDA5051A_Arduino/blob/master/Reference%20Docs/Pics/Zero_Cross_Detection_Capture_Annotate1.PNG)

* **A –** 120 VAC zero cross point.  Signal begins to rise to maximum amplitude but H11AA1 bi-directional optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **B –**  120 VAC rises high enough to bias NPN transistor in optocoupler pulling the zero cross detection signal LOW (0V).
* **C –**  120 VAC zero cross point.  Signal begins to fall to minimum amplitude.  H11AA1 optocoupler is off so zero cross signal remains HIGH (+5V) due to pull-up resistor.
* **D –**  120 VAC falls low enough to bias NPN transistor in bi-directional optocoupler pulling the zero cross detection signal LOW (0V).

<a name="Pin_Mappings_and_Pinouts"></a>
## Pin Mappings and Pinouts
### Table 1. Breakout Board ***PLM DIO*** pin descriptions
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

### Table 2. Breakout Board ***PWR*** pin descriptions
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

### Table 3.  Breakout Board Power Line Input connector J1 pin descriptions
| J1 Pin | AC/DC signal |
|:---:|:---:|
| 1 | AC LINE/DC_IN+ |
| 2 | AC Neutral/DC_IN- |
| 3 | N/C |

### Table 4. Adafruit Metro to PLM Breakout Board Pin Map
| Adafruit Metro Pin | PLM Breakout Board Connector Pin |
|:---:|:---:|
| +5V | J3 pin 2,4,6, or 8 |
| GND | J3 pin 1,3,5 or 7 |
| TX0 | J2 pin 5|
| RX0 | J2 pin 7|

<a name="How_to_Order_Development_Boards"></a>
## How to Order Development Boards
[Purchase demo board or full kit](https://www.tindie.com/products/jarvie/smart-home-power-line-modem-demo-board/)

<a href="https://www.tindie.com/stores/jarvie/?ref=offsite_badges&utm_source=sellers_JARViE&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>

<a name="Custom_Application_Development_Services"></a>
# Custom Application Development Services
Powerline modem technology is being used in the solar, oil and gas and irrigation industries just to list a few.  E-mail hilljarvis@gmail.com if you're interested and or need help planning, reviewing, designing, developing and or deploying a custom powerline modem device and or powerline communications system.
