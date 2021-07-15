#!/usr/bin/python3

import serial
import time
import sys

try:
    #open port /dev/ttyUSB0 at 9600 bps
    ser=serial.Serial('/dev/ttyS0', 9600, timeout=1)
    ser.flush()
    
    #Let's print port name
    print(ser.name)
    
    while True:
        command = input("Please enter ON-OFF or sensor: ")
        ser.write(command.encode())
        
        time.sleep(1)
        print(ser.in_waiting)
        #read the buffer with newlines and cut the newline and display
        read_serial=ser.readline().decode('ascii').rstrip('\n')
        print(read_serial)
        
        time.sleep(2)

except KeyboardInterrupt:
    ser.close()
    print("Existing program successfully...")
    sys.exit()
