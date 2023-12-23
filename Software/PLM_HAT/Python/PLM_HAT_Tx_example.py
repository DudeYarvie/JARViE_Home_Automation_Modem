##			JARViE_PLM_Tx_example.py	
##Description:	Simple example showing how send messages on the powerline using the PLM HAT		
##Author:		Jarvis Hill (hilljarvis@gmail.com)
##Date:			22-DEC-2023

# The following code is needed to run this script automatically at Raspberry Pi boot.
#  /etc/init.d/JARViE_PLM_Tx_example.py
### BEGIN INIT INFO 
# Provides:             Serial.py 
# Required-Start:       $remote_fs $syslog 
# Required-Stop:        $remote_fs $syslog 
# Default-Start:        2 3 4 5 
# Default-Stop:         0 1 6  
# Short-Description     Start deamon at boot time 
# Description:          Enable service provided by daemon. 
### END INTI INFO 
#####################################################################################


##MODULES##
import serial
import os
from time import sleep


##MAIN##
def main():
	
	#Init serial port
	ser = serial.Serial("/dev/ttyS0", 1200)
	sleep(0.05)
	
	
	#Power-up PLM
	os.system(f'echo 6 > /sys/class/gpio/export')					#Select/export GPIO to use
	sleep(0.05)												        #delay	
	os.system(f'echo out > /sys/class/gpio/gpio6/direction')		#Set GPIO as output
	os.system(f'echo 0 > /sys/class/gpio/gpio6/value')				#Set GPIO output LOW
	sleep(1)
	
	#Send command on powerline via JARViE PLM HAT
	for i in range(0,10):
		ser.write(bytes("IDN?\n", 'ascii'))							#RPI sends command to HAT via serial bus. HAT then sends commands
																	#on powerline 
		sleep(8)													#Delay in seconds
	
	ser.close()
	sleep(0.05)
	os.system(f'echo in > /sys/class/gpio/gpio6/direction')			#Cleanup use of GPIO pin once done
	sleep(0.05)
	os.system(f'echo 6 > /sys/class/gpio/unexport')
	
	

if __name__ == '__main__':
	main()
