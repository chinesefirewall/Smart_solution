try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("...error importing RPi.GPIO module")

import time


all_leds = [29, 31, 33, 35, 37, 40, 38, 36, 32, 22]
all_leds_flipped = [22, 32, 36, 38, 40, 37, 35, 33, 31, 29]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(all_leds, GPIO.OUT)

def light_all_pins(EACH_PIN, pause):
    GPIO.output(EACH_PIN, GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(EACH_PIN, GPIO.LOW)
    
try:
    while True:
        for led in all_leds:
            light_all_pins(led, 0.1)
        for led in all_leds_flipped:
            light_all_pins(led, 0.1)
        
except KeyboardInterrupt:
    GPIO.cleanup()

