#!/usr/bin/env python3
import serial
import time

values = []

if __name__ == '__main__':
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)
    print("hi")
    ser.flush()
    numberofreads = 0

    while numberofreads<30:
        print("sending: ", "start")
        ser.write("start\n".encode('ascii'))
    
        if (ser.inWaiting()>0):
            print("inwaiting")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received: ", line)
            values.append(line)
            numberofreads = numberofreads + 1
        time.sleep(1)
        
        file = open("temperatures.txt","w+")
        for item in values:
            file.write("%s\n"%item)
        file.close()
        
