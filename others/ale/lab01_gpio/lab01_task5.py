import RPi.GPIO as GPIO    
import time  
import random

GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)



def track_state(channel):
    global count
    if GPIO.input(channel) == GPIO.HIGH:
        count += 1
    
            
        
def show_num(pins, delay):    
    GPIO.output(pins, GPIO.LOW)
    time.sleep(delay)
    GPIO.output(pins, GPIO.HIGH)

      
"""
segments
g = 16
f = 18
a = 22
b = 32

e = 36
d = 37
c = 33
h = 31

LOW = on
HIGH = off
"""

button = 11
pins = [31, 16, 18, 36, 37, 33, 32, 22]
GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(button, GPIO.IN)
GPIO.add_event_detect(button, GPIO.BOTH, callback=track_state)

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



# indexes represent numbers [0..9]
nums = [n0, n1, n2, n3, n4, n5, n6, n7, n8, n9]

current = 0
count = 0



try:
    while True:
        if count == 0:
            show_num(nums[current], 1)
            current = (current+1)%len(nums)
        
        elif count == 1:
            current = (current-1)%len(nums)
            show_num(nums[current], 1)
            
        elif count == 2:
            current = random.randint(0, 9)
            show_num(nums[current], 1)
        
        elif count > 2:
            count = 0

except KeyboardInterrupt:
    print("Programm ended")


GPIO.cleanup(pins)


