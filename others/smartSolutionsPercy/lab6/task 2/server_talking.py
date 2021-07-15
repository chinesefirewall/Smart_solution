#!/usr/bin/env python3
import serial
import time

#talking happens by one message syncronized
reply = True

if __name__ == '__main__':
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)
    ser.flush()
    numberofreads = 0
    #send Hi
    print("sending: ", "Welcome")
    ser.write("Hi!!!!\n".encode('ascii'))
    record_values = []

    while True:

        if (reply == True):
            message = input("type in the message:  ")
            message = message+"\n"
            print("sending message: ", message)
            ser.write(message.encode('ascii'))
            reply = False
        
        #waits for arduino response
        if (ser.inWaiting()>0):
            print("inwaiting")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received message: ", line)
            record_values.append(line)
            reply = True
        time.sleep(1)
        
