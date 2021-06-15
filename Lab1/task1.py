import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

LED1 = [38,40] # 8 

GPIO.setup(LED1, GPIO.OUT)

while True:
    GPIO.output(LED1[1], GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(LED1[1], GPIO.LOW)
    time.sleep(0.5)
    GPIO.output(LED1[0], GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(LED1[0], GPIO.LOW)
    
GPIO.cleanup()
