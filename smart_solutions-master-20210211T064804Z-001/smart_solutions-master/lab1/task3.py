import RPi.GPIO as GPIO
import time


leds = [29,31,33,35,37,40,38]

num0= [29,31,33,37,40,38]
num1= [29,38]
num2= [31,29,35,37,40]
num3= [31,29,35,38,40]
num4= [33,29,35,38]
num5= [31,33,35,38,40]
num6= [31,33,35,38,40,37]
num7= [31,29,38]
num8= [31,29,33,35,37,38,40]
num9= [31,33,35,29,38,40]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

def light_pin(PIN,pause):
    
    GPIO.output(PIN,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(PIN,GPIO.LOW)
    

while True:
    for n in range(50):
        for i in num0:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num1:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num2:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num3:
            light_pin(i,0.003)
        
    time.sleep(0.5)

    for n in range(50):
        for i in num4:
            light_pin(i,0.003)
        
    time.sleep(0.5)

    for n in range(50):
        for i in num5:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num6:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num7:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num8:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    
    for n in range(50):
        for i in num9:
            light_pin(i,0.003)
        
    time.sleep(0.5)
    