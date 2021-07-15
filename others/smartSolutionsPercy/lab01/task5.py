import RPi.GPIO as GPIO
import time
import random


all_leds = [29, 31, 33, 35, 37, 40, 38]
button_pin = 36

def button_callback(channel):
    global count_button
    
    count_button += 1
    if count_button == 3:
        count_button = 0
    
    print("Button was pressed")


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
    GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    
    
    GPIO.add_event_detect(button_pin, GPIO.RISING, callback = button_callback, bouncetime=200)
    
    count_button = 0
    counter_back = 9
    
    while True:
        print("Count number: ", count_button)
        
        if count_button == 0:
            for i in range(10):
                light(i, all_leds)
                time.sleep(0.5)
            
        if count_button == 1:
            for i in range(10):
                light(counter_back - i, all_leds)
                time.sleep(0.5)
                if counter_back == -1:
                    counter_back = 9
                    
        if count_button == 2:
            number = random.randrange(10)
            light(number, all_leds)
            time.sleep(2)
            
except KeyboardInterrupt:
    GPIO.cleanup()
    



        


    



