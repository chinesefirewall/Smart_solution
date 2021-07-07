#https://projectiot123.com/2019/01/27/home-automation-using-raspberry-pi-via-bluetooth/

import serial
from RPLCD import i2c
import time
import bluetooth
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
mode = GPIO.getmode()
GPIO.setwarnings(False)

GPIO.setup(40, GPIO.OUT)

ser = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1)
time.sleep(0.2)
led = False


if ser.isOpen():
    print("open")
    while True:
        while ser.inWaiting()==0: pass
        if ser.inWaiting()>0:
            asw = ser.readline()
            asw = (asw.decode()).rstrip()
            if asw == "on":
                print('asd')
                GPIO.output(40, GPIO.HIGH)
                led = True
            if asw == "off":
                GPIO.output(40, GPIO.LOW)
                led = False
            if asw == "info":
                print(led, "state")
                ser.write('state'.encode())
            
            print(asw)
            time.sleep(0.2)