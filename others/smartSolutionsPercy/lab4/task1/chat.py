#!/usr/bin/env python3
import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/rfcomm0', 9600, timeout=1)
    print("Welcome to Raspberry...")
    ser.flush()

    while True:
        message = input("Enter msg: ")
        print("sending: ", message)
        ser.write(message.encode('ascii'))
        if (ser.inWaiting()>0):
            print("Message inwaiting")
            readline = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received: ", readline)
            
        time.sleep(1)