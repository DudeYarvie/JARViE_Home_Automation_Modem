##						UDPSend_PLM_Shield.py
##Purpose: Send UDP messages to device connected on the same/local internet network
##Written By:  Jarvis Hill, hilljarvis@gmail.com
##Date: 26-JAN-2020

import socket
import time


##MAIN PROGRAM##
def main():

    #Connect to UDP port created by Arduino UNO w/ Ethernet Shield
    UDP_IP = "192.168.1.177"						#Device to send UDP packets to
    UDP_PORT = 8888									#Device port
    MESSAGE = "RELAY_C"								#Message to send                             

    for i in range(0,1):
        print i
        print "UDP target IP:", UDP_IP
        print "UDP target port:", UDP_PORT
        #print "message:", MESSAGE					#Print UDP message for debugging
         
        sock = socket.socket(socket.AF_INET,      	# Internet
                               socket.SOCK_DGRAM) 	# UDP

        sock.settimeout(5)
            
        sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))    #Initialize data acquisition
        time.sleep(1)



if __name__ == '__main__':
    main()
