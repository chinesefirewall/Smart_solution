import RPi.GPIO as GPIO
import time


all_leds = [29, 31, 33, 35, 37, 40, 38]


try:
    def light(num, pins):
        numbers = [[1,1,1,1,1,1,0],
               [0,1,1,0,0,0,0],
               [1,1,0,1,1,0,1],
               [1,1,1,1,0,0,1],
               [0,1,1,0,0,1,1],
               [1,0,1,1,0,1,1],
               [1,0,1,1,1,1,1],
               [1,1,1,0,0,0,0],
               [1,1,1,1,1,1,1],
               [1,1,1,1,0,1,1]]
        for i in range(len(pins)):
            GPIO.output(pins[i], 1 - numbers[num][i])        


    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)

    GPIO.setup(all_leds, GPIO.OUT)
    
    while True:
        for i in range(10):
            light(i, all_leds)
            time.sleep(0.5)

except KeyboardInterrupt:
    GPIO.cleanup()
