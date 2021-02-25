import RPi.GPIO as GPIO
import time

sec = 0.003
#leds = [29,31,33,35,37,40,38]
leds = [29,31,33,35,37,36,38,40]

num0 = [29,31,33,36,38,40],
num1 = [29,36]
num2 = [31,29,37,40,38]
num3 = [31,29,37,38,36]
num4 = [33,37,29,36]
num5= [31,33,37,36,38]
num6= [31,33,37,36,38,40]
num7= [31,29,36]
num8= [31,29,33,36,37,38,40]
num9= [29,31,33,37,36]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

def pin_lighter(pin,pause):
    #GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(pin,GPIO.LOW)
    

while True:
    for n in range(50):
        for i in num0:
            pin_lighter(i, sec)
            
     
    #time.sleep(0.5)

#     time.sleep(0.5)
    
    for n in range(50):
        for i in num2:
            pin_lighter(i, sec)
# #         
#     time.sleep(0.5)
    
    for n in range(50):
        for i in num3:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)

    for n in range(50):
        for i in num4:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)

    for n in range(50):
        for i in num5:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)
    
    for n in range(50):
        for i in num6:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)
    
    for n in range(50):
        for i in num7:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)
    
    for n in range(50):
        for i in num8:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)
    
    for n in range(50):
        for i in num9:
            pin_lighter(i, sec)
        
    #time.sleep(0.5)
GPIO.cleanup()    