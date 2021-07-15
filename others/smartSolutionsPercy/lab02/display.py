import RPi.GPIO as GPIO
import time
import random


def display_controller(command):
    
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
     
        counter_back = 9
        
        while True:
            
            if command == "0":
                for i in range(10):
                    light(i, all_leds)
                    time.sleep(0.5)
            
            if command == "1":
                for i in range(10):
                    light(i, all_leds)
                    time.sleep(0.5)
                
            if command == "2":
                for i in range(10):
                    light(counter_back - i, all_leds)
                    time.sleep(0.5)
                    if counter_back == -1:
                        counter_back = 9
                        
            if command == "3":
                number = random.randrange(10)
                light(number, all_leds)
                time.sleep(2)
                
    except KeyboardInterrupt:
        GPIO.cleanup()
    



        


    



