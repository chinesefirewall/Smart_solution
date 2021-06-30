import RPi.GPIO as GPIO    
import time  


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)

pin_out1 = 38
pin_out2 = 40



    
GPIO.setup(pin_out1, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(pin_out2, GPIO.OUT, initial=GPIO.LOW)

try:
    while True:
        print("LED1 is on")
        GPIO.output(pin_out1, GPIO.LOW)
        print("LED2 is off")
        GPIO.output(pin_out2, GPIO.HIGH)
        time.sleep(0.5)
        print("LED1 is off")
        GPIO.output(pin_out1, GPIO.HIGH)
        print("LED2 is on")
        GPIO.output(pin_out2, GPIO.LOW)
        time.sleep(0.5)


except KeyboardInterrupt:
    
    
    
    
    GPIO.cleanup((pin_out1, pin_out2))   

