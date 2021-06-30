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

nums = [[1, 1, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 0, 0, 1],
        [1, 0, 1, 0, 0, 1, 0, 0],
        [1, 0, 1, 1, 0, 0, 0, 0],
        [1, 0, 0, 1, 1, 0, 0, 1],
        [1, 0, 0, 1, 0, 0, 1, 0],
        [1, 0, 0, 0, 0, 0, 1, 0],
        [1, 1, 1, 1, 1, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 0],
        [1, 0, 0, 1, 0, 0, 0, 0]]

current = 0
count = 2

try:
    while True:
        if count == 0:
            current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
            show_num(current_leds, 1)
            current = (current+1)%len(nums)
        
        elif count == 1:
            current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
            current = (current-1)%len(nums)
            show_num(current_leds, 1)
            
        elif count == 2:
            current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
            current = random.randint(0, 9)
            show_num(current_leds, 1)
        
        elif count > 2:
            count = 0

except KeyboardInterrupt:
    print("Programm ended")


GPIO.cleanup(pins)



