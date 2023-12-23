##			GPIO_example.py	
##Description:	Simple example showing how to control Raspberry Pi GPIO	
##Author:		Jarvis Hill (hilljarvis@gmail.com)
##Date:			22-DEC-2023


##Modules##
import os
from time import sleep


##MAIN##
def main():
	
	#Power-up PLM
	os.system(f'echo 6 > /sys/class/gpio/export')					#Select/export GPIO to use
	sleep(0.05)												        #delay	
	os.system(f'echo out > /sys/class/gpio/gpio6/direction')		#Set GPIO as output
	os.system(f'echo 0 > /sys/class/gpio/gpio6/value')				#Set GPIO output LOW
	sleep(1)
	
	os.system(f'echo 14 > /sys/class/gpio/export')					#Select/export GPIO to use
	sleep(0.05)												        #delay	
	os.system(f'echo out > /sys/class/gpio/gpio14/direction')		#Set GPIO as output
	
	#Generate square wave
	for i in range(0,2000):
		os.system(f'echo 1 > /sys/class/gpio/gpio14/value')			#Set GPIO output HIGH
		sleep(.1)
		os.system(f'echo 0 > /sys/class/gpio/gpio14/value')			#Set GPIO output LOW
		sleep(.1)
	
	#Cleanup GPIO
	os.system(f'echo in > /sys/class/gpio/gpio14/direction')		#Cleanup use of GPIO pin once done
	sleep(0.05)
	os.system(f'echo 14 > /sys/class/gpio/unexport')
	sleep(0.05)
	os.system(f'echo in > /sys/class/gpio/gpio6/direction')			#Cleanup use of GPIO pin once done
	sleep(0.05)
	os.system(f'echo 6 > /sys/class/gpio/unexport')
		


if __name__ == '__main__':
	main()

