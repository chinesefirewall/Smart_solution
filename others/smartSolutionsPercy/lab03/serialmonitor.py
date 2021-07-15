#!/usr/bin/python3

import serial
import time
import sys

try:
    #open port /dev/ttyUSB0 at 9600 bps
    ser=serial.Serial('/dev/ttyUSB0', 9600)
    print(ser.name)
    
    while True:
        #read the buffer with newlines
        read_serial=ser.readline()
        #cut the newline and display
        print(read_serial.rstrip('\n'))
        
        time.sleep(2)

except KeyboardInterrupt:
    ser.close()
    print("Existing program successfully...")
    sys.exit()