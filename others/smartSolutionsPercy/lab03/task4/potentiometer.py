#!/usr/bin/env python3
import time
import sys
import serial
import board
import busio
import neopixel
import adafruit_character_lcd.character_lcd_rgb_i2c as character_lcd
from lcd_i2c import main


#led
led= neopixel.NeoPixel(board.D18,1)
send_status = False

if __name__ == '__main__':
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)
    print("connected")
    ser.flush()
    
    while True:
        if send_status == False:
            print("sending: ", "begin")
            ser.write("begin\n".encode('ascii'))
            send_status = True

        if (ser.inWaiting()>0):
            print("inwaiting mode")
            read_serial=ser.read(ser.inWaiting()).decode('ascii').rstrip()
            print("Message received: ", read_serial)
     
            # Sending to the lcd display
            main(str(read_serial))
            send_status = False      

        # waiting before sending new values
        time.sleep(1)


