import RPi.GPIO as GPIO    
import time  


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)

pin_out = 40



    
GPIO.setup(pin_out, GPIO.OUT, initial=GPIO.LOW)

while True:
    print("LED is on")
    GPIO.output(pin_out, GPIO.HIGH)
    time.sleep(0.5)
    print("LED is off")
    GPIO.output(pin_out, GPIO.LOW)
    time.sleep(0.5)


    
    
    
    
GPIO.cleanup(pin_out)   
