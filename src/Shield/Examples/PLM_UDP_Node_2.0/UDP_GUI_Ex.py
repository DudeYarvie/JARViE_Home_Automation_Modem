#Modules
from Tkinter import *
from Tkinter import Tk, W, E       #library for Python GUIs
import tkMessageBox
from ttk import Frame, Button, Label, Style
from ttk import Entry
from datetime import date
import socket
import time


def send_UDP_msg(dev_ip, port, UDP_str):
   
    #Connect to UDP port created by Arduino UNO w/ Ethernet Shield
    UDP_IP = dev_ip						#Device to send UDP packets to
    UDP_PORT = int(port)									#Device port
    MESSAGE = UDP_str								#Message to send                             

    read_flag = 0                           #Init read_flag
    if (MESSAGE == "TEMP" or MESSAGE == "HUM" or MESSAGE == "GAS"):    
        read_flag = 1
    

    for i in range(0,1):
        #print i
        print "UDP target IP:", UDP_IP
        print "UDP target port:", UDP_PORT
        print "message:", MESSAGE					#Print UDP message for debugging
         
        sock = socket.socket(socket.AF_INET,      	# Internet
                               socket.SOCK_DGRAM) 	# UDP

        sock.settimeout(5)
            
        sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))    #Initialize data acquisition

        #Wait for response if read flag is set
        if (read_flag == 1):
            rcv_data, addr = sock.recvfrom(10)              # buffer size
            print(rcv_data)
            return rcv_data
        


        #time.sleep(1)


class Application(Frame):

    
    def __init__(window, parent):
        Frame.__init__(window,parent)
        window.parent = parent
        window.pack(fill = BOTH)            #Places widgets into top left of window
        window.parent = parent
        ##global arduino                    #defines serial object globally for use inside the app
        ##arduino = init_serial_comms()     #initialize serial comm with device
        window.createWidgets()              #Generate GUI 


    def get_user_UDP_str(window):
        device_ip_addr = window.ip_val.get()
        if (device_ip_addr == ''):
            tkMessageBox.showinfo("Error!", "Enter Device IP Address!")

        device_port = window.port_val.get()
        if (device_port == ''):
            tkMessageBox.showinfo("Error!", "Enter Device Port#!")
        msg=window.udp_str_val.get()
        send_UDP_msg(device_ip_addr, device_port, msg)


    def get_env_data(window):
        device_ip_addr = window.ip_val.get()
        if (device_ip_addr == ''):
            tkMessageBox.showinfo("Error!", "Enter Device IP Address!")

        device_port = window.port_val.get()
        if (device_port == ''):
            tkMessageBox.showinfo("Error!", "Enter Device Port#!")

        ##Retrieve environment data from Environment Node via UDP Node
        env_data = []
        env_cmds = ['TEMP','HUM','GAS']
        for item in env_cmds:
            env_data.append(send_UDP_msg(device_ip_addr, device_port, item))
            time.sleep(1)

        #Update data in GUI
        window.label0_val['text']=env_data[0][:-1]          #[:-1] removes newline from data
        window.label1_val['text']=env_data[1][:-1]
        window.label2_val['text']=env_data[2][:-1]


    def push_garage_button(window):
        device_ip_addr = window.ip_val.get()
        if (device_ip_addr == ''):
            tkMessageBox.showinfo("Error!", "Enter Device IP Address!")

        device_port = window.port_val.get()
        if (device_port == ''):
            tkMessageBox.showinfo("Error!", "Enter Device Port#!")
            
        app_cmds = ['RELAY_O','RELAY_C']
        for item in app_cmds:                                       #Trigger lifter to open garage
            send_UDP_msg(device_ip_addr, device_port, item)
            time.sleep(0.5)
              
        
    def createWidgets(window):
        window.master.title("JARViE Simple Smart Home UDP Example 1.0")             ## Add title to window

        Style().configure("TButton", padding=(0, 15, 0, 15), 
            font='serif 10')

        #Entry Fields
        window.udp_str = Label(window, text="Broadcast Message", font='serif 15')          ##User input for UDP string to send to device
        window.udp_str.grid(row=0,column=0, sticky=W)

        window.device_ip = Label(window, text="UDP Node IP Addr (ex.192.168.1.187)", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.device_ip.grid(row=1,column=0, sticky=E)
        window.ip_val = Entry(window)
        window.ip_val.grid(row=1,column=1,padx = 15, sticky=W)

        window.device_udp_port = Label(window, text="UDP PORT# (ex.8888)", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.device_udp_port.grid(row=2,column=0, sticky=E)
        window.port_val = Entry(window)
        window.port_val.grid(row=2,column=1,padx = 15, sticky=W)

        window.udp_str = Label(window, text="Message", font='serif 10')                                   ##User input for UDP string to send to device
        window.udp_str.grid(row=3,column=0, sticky=E)
        window.udp_str_val = Entry(window)
        window.udp_str_val.grid(row=3,column=1,padx = 15, sticky=W)

        window.sendUDP = Button(window, text="Broadcast", width=10, command=window.get_user_UDP_str)
        window.sendUDP.grid(row=3,column=2,rowspan =1)

        #Section Headers
        window.sub_hdr1 = Label(window, text="Home Appliances", font='serif 15')          ##User input for UDP string to send to device
        window.sub_hdr1.grid(row=4,column=0, sticky=W)

        window.app_label0 = Label(window, text="Garage Door", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.app_label0.grid(row=5,column=0, sticky=E)

        window.app_but0 = Button(window, text="OPEN", width=10, command=window.push_garage_button)
        window.app_but0.grid(row=5,column=1,rowspan =1)

        window.app_but1 = Button(window, text="CLOSE", width=10, command=window.push_garage_button)
        window.app_but1.grid(row=5,column=2,rowspan =1)

        window.app_label1 = Label(window, text="Coffee Pot", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.app_label1.grid(row=6,column=0, sticky=E)
        
        window.app_but2 = Button(window, text="ON", width=10, command='')
        window.app_but2.grid(row=6,column=1,rowspan =1)

        window.app_but3 = Button(window, text="OFF", width=10, command='')
        window.app_but3.grid(row=6,column=2,rowspan =1)


        #Lighting
        window.sub_hdr2 = Label(window, text="Home Lighting", font='serif 15')          ##User input for UDP string to send to device
        window.sub_hdr2.grid(row=7,column=0, sticky=W)
        
        window.app_label1 = Label(window, text="Living Room", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.app_label1.grid(row=8,column=0, sticky=E)

        window.app_label1 = Label(window, text="Guest Room", font='serif 10')     ##IP Addr of UDP device (JARViE UDP Node)
        window.app_label1.grid(row=9,column=0, sticky=E)

        global v
        v=IntVar()
        v.set(0)
        window.light_sel0 = Radiobutton(window, text="ON", variable=v, value=0)
        window.light_sel0.grid(row=8,column=1)
        window.light_sel1 = Radiobutton(window, text="OFF", variable=v, value=1)
        window.light_sel1.grid(row=8,column=2)

        global y
        y=IntVar()
        y.set(0)
        window.light_sel2 = Radiobutton(window, text="ON", variable=y, value=0)
        window.light_sel2.grid(row=9,column=1)
        window.light_sel3 = Radiobutton(window, text="OFF", variable=y, value=1)
        window.light_sel3.grid(row=9,column=2)



        #Environment Dashboard
        window.sub_hdr3 = Label(window, text="Environment", font='serif 15')                      ##User input for UDP string to send to device
        window.sub_hdr3.grid(row=10,column=0, sticky=W)
        window.env_but0 = Button(window, text="Update", width=10, command=window.get_env_data)
        window.env_but0.grid(row=10,column=1,rowspan =1)

        window.env_label0 = Label(window, text="Bedroom Temperature [C]", font='serif 10')          ##User input for UDP string to send to device
        window.env_label0.grid(row=11,column=0, sticky=E)
        window.label0_val = Label(window, text = '0.00')
        window.label0_val.grid (row=11, column=1)

        window.env_label1 = Label(window, text="Bathroom Humidity [RH]", font='serif 10')          ##User input for UDP string to send to device
        window.env_label1.grid(row=12,column=0, sticky=E)
        window.label1_val = Label(window, text = '0.00')
        window.label1_val.grid (row=12, column=1)

        window.env_label2 = Label(window, text="Home VOC Level", font='serif 10')                ##User input for UDP string to send to device
        window.env_label2.grid(row=13,column=0, sticky=E)
        window.label2_val = Label(window, text = '0.00')
        window.label2_val.grid (row=13, column=1)


  
        #Render entities to GUI window
        for row in xrange(13):
            window.grid_rowconfigure(row, minsize=35)
        window.pack()



#Main Program
def main ():
    #arduino=init_serial_comms()
    root = Tk()
    app = Application(root)
    root.mainloop()
    root.destroy()
    arduino.close()
    
if __name__ == '__main__':
    main()
