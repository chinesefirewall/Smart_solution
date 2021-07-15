#!/usr/bin/env python3
try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("...error importing RPi.GPIO module")

import serial
import time


DISPLAY_LED1 = 40
status = ''

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(DISPLAY_LED1, GPIO.OUT)


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
    print("Welcome to Raspberry...")
    ser.flush()
    
    try:
        while True:
            print("waiting for incoming...")
            
            if (ser.in_waiting > 0):
                print("Message inwaiting")
                readline = ser.read(ser.inWaiting()).decode('ascii').rstrip()
                print("received: ", readline)
                
                if readline == "on":
                    GPIO.output(DISPLAY_LED1, GPIO.HIGH)
                    status = "LedIsOn"
                elif readline == "off":
                    GPIO.output(DISPLAY_LED1, GPIO.LOW)
                    status = "LedIsOff"
                elif readline == "status":
                    led_status = status
                    ser.write(led_status.encode('ascii'))
                
            time.sleep(1)
        
    except KeyboardInterrupt:
        GPIO.cleanup()
