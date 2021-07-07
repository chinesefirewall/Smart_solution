'''import board
import neopixel

pixels = neopixel.NeoPixel(board.D18, 10)
pixels[1] = (0,100,0)
'''

#!/usr/bin/env python3
import serial
import time

#list were to append values
values = []

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    print("[INFO] Serial connected")
    ser.flush()
    numberofreads = 0
    
    #Takes 30 measurments
    while numberofreads<30:
        #send start message to make arduino read temperature
        print("[INFO] sending: ", "start")
        ser.write("start\n".encode('ascii'))
        
        #waits for arduino response
        if (ser.inWaiting()>0):
            print("[INFO] waiting for ARDUINO response")
            line = ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("[INFO] received: ", line)
            values.append(line)
            numberofreads = numberofreads + 1
        time.sleep(1)
        
        #writes all in text file
        file = open("temperatures.txt","w+")
        for item in values:
            file.write("%s\n"%item)
        file.close()
        


