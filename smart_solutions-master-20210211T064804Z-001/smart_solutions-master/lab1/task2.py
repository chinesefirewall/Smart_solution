import RPi.GPIO as GPIO
import time


leds = [29,31,33,35,37,40,38,36,32,22]
flipped_leds = [22,32,36,38,40,37,35,33,31,29]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

def light_pin(PIN,pause):
    
    GPIO.output(PIN,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(PIN,GPIO.LOW)
    

while True:
    for i in leds:
        light_pin(i,0.1)
    for i in flipped_leds:
        light_pin(i,0.1)
    
    
