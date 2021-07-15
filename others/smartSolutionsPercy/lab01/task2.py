try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("...error importing RPi.GPIO module")

import time


DISPLAY_LED1 = 40
DISPLAY_LED2 = 35

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(DISPLAY_LED1, GPIO.OUT)
GPIO.setup(DISPLAY_LED2, GPIO.OUT)
    
try:
    while True:
        GPIO.output(DISPLAY_LED1, GPIO.HIGH)
        GPIO.output(DISPLAY_LED2, GPIO.LOW)
        time.sleep(0.5)
        GPIO.output(DISPLAY_LED1, GPIO.LOW)
        GPIO.output(DISPLAY_LED2, GPIO.HIGH)
        time.sleep(0.5)
        print("Led on and off")
        
except KeyboardInterrupt:
    GPIO.cleanup()
