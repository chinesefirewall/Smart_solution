import RPi.GPIO as GPIO    
import time  


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)

pin = 36

GPIO.setup(pin, GPIO.OUT, initial=GPIO.HIGH)


time.sleep(10)

GPIO.cleanup(pin) 