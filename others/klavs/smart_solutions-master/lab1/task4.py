import RPi.GPIO as GPIO
import time

butpin = 36

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

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)
GPIO.setup(butpin,GPIO.IN)

def light_num(num):
    for n in range(50):
        for led in num:
            
            GPIO.output(led,GPIO.HIGH)
            time.sleep(0.003)
            GPIO.output(led,GPIO.LOW)
            
            
while True:
    
    for num in numbers:
        light_num(num)

    
