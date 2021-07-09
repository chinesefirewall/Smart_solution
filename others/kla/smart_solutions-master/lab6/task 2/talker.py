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
    print("sending: ", "Hi!!!!")
    ser.write("Hi!!!!\n".encode('ascii'))

    while True:

        if (reply == True):
            msg = input("type in the message:  ")
            msg = msg+"\n"
            print("sending: ", msg)
            ser.write(msg.encode('ascii'))
            reply = False
        
        #waits for arduino response
        if (ser.inWaiting()>0):
            print("inwaiting")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("received: ", line)
            values.append(line)
            reply = True
        time.sleep(1)
        
