#!/usr/bin/env python3
import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    print("hi")
    ser.flush()

    while True:


        mess = input("write msg: ")
        print("sending: ", mess)
        ser.write(mess.encode('ascii'))
        if (ser.inWaiting()>0):
            print("inwaiting")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received: ", line)
            
        time.sleep(1)