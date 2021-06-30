import RPi.GPIO as GPIO
import time


LED1=35
LED2=37

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(LED1,GPIO.OUT)
GPIO.setup(LED2,GPIO.OUT)


while True:
    
    GPIO.output(LED1,GPIO.HIGH)
    GPIO.output(LED2,GPIO.LOW)
    
    time.sleep(0.5)
