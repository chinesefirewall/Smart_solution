#!/usr/bin/env python3
import serial
import time

## /dev/rfcomm0        
## /dev/ttyAMA0 

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    print("Hello...welcome ")
    ser.flush()

    while True:


        mess = input("write a msg: ")
        print("sending: ", mess)
        ser.write(mess.encode('ascii'))
        if (ser.inWaiting()>0):
            print("inwaiting")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received: ", line)
            
        time.sleep(1)