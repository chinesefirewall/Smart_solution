import RPi.GPIO as GPIO    
import time  


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)



pins = [16, 18, 22, 32, 36, 37, 33, 31, 29, 15]


    
GPIO.setup(pins, GPIO.OUT, initial=GPIO.LOW)
#GPIO.setup(pin_out2, GPIO.OUT, initial=GPIO.LOW)

while True:
    for pin in pins:
        GPIO.output(pin, GPIO.HIGH)
        time.sleep(0.5)
        GPIO.output(pin, GPIO.LOW)


    for pin in pins[::-1]:
        GPIO.output(pin, GPIO.HIGH)
        time.sleep(0.5)
        GPIO.output(pin, GPIO.LOW)
        
        


GPIO.cleanup(pins)

