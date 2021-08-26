import serial
import time

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
mode = GPIO.getmode()
GPIO.setwarnings(False)

GPIO.setup(40, GPIO.OUT)

ser = serial.Serial("/dev/serial0", baudrate=9600, timeout=1)

time.sleep(0.2)
led = False

counter = 0
try:
    if ser.isOpen():
        print("serial is open")
        while True:
            if ser.inWaiting()>0:
                print('waiting for data')
                serial_data = ser.readline()
                serial_data = (serial_data.decode()).rstrip()
                if serial_data == "on":
                    GPIO.output(40, GPIO.HIGH)
                    led = True
                if serial_data == "off":
                    GPIO.output(40, GPIO.LOW)
                    led = False
                    
                if led == True:
                    my_led = "led ON"
                if led == False:
                    my_led = "led OFF"
                    
                if serial_data == "info":
                    print(my_led)
                    ser.write(my_led.encode())
                    
                
                print(serial_data)
                time.sleep(0.2)
except KeyboardInterrupt:
    GPIO.output(40, GPIO.LOW)
