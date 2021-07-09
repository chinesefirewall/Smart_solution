import RPi.GPIO as GPIO
import time


LED1=35
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(LED1,GPIO.OUT)

while True:
    
    GPIO.output(LED1,GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(LED1,GPIO.LOW)
    time.sleep(0.5)
    
GPIO.cleanup()