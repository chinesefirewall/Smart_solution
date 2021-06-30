import RPi.GPIO as GPIO
import time
import random

BUTTON = 36

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

numbers = [num0,num1,num2,num3,num4,num5,num6,num7,num8,num9]

#setup pin modes

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

#button setup
GPIO.setup(BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def light_num(num):
    for n in range(70):
        for led in num:
            
            GPIO.output(led,GPIO.HIGH)
            time.sleep(0.003)
            GPIO.output(led,GPIO.LOW)
            

#define button callback and event

def button_func(smthing):
    global button_count
    print ("BUTTON PRESSED")
    
    button_count = button_count + 1
    if button_count == 3:
        button_count = 0

GPIO.add_event_detect(BUTTON, GPIO.RISING, callback = button_func, bouncetime=200)



button_count = 0
i = 0
while True:
    
    print("currently showing",i)
    light_num(numbers[i])
    
    if button_count == 0:
        i = i + 1
        
        if i == 10:
            i = 0
    
    if button_count == 1:
        i = i - 1
        
        if i == -1:
            i=9
            
    if button_count == 2:
        i = random.randrange(10)
        

    

