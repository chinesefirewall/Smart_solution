import RPi.GPIO as GPIO    
import time  


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)


def show_num(pins, delay):
    
    GPIO.output(pins, GPIO.LOW)
    time.sleep(delay)
    GPIO.output(pins, GPIO.HIGH)



pins = [31, 16, 18, 36, 37, 33, 32, 22]
    
GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)


n0 = [22, 32, 33, 37, 36, 18]
n1 = [33, 32]
n2 = [22, 32, 16, 36, 37]
n3 = [16, 37, 33, 32, 22]
n4 = [16, 18, 33, 32]
n5 = [16, 18, 37, 33, 22]
n6 = [16, 18, 36, 37, 33, 22]
n7 = [33, 32, 22]
n8 = [16, 18, 36, 37, 33, 32, 22]
n9 = [16, 18, 37, 33, 32, 22]

nums = [n0, n1, n2, n3, n4, n5, n6, n7, n8, n9]


#GPIO.setup(pin_out2, GPIO.OUT, initial=GPIO.LOW)

while True:
    for num in nums:
        show_num(num, 1)
       


    for num in nums[::-1]:
        show_num(num, 1)
        
        


GPIO.cleanup(pins)


