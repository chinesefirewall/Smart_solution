import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

LED1 = 8 

GPIO.setup(LED1, GPIO.OUT)

while True:
    GPIO.output(LED1, GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(LED1, GPIO.LOW)
    time.sleep(0.5)
    
GPIO.cleanup()
