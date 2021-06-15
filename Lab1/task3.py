import RPi.GPIO as GPIO
import time

sec = 0.003
#leds = [29,31,33,35,37,40,38]
#leds = [29,31,33,35,37,36,38]

leds = [16,18,22,11,13,15,37]
    #GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)

# num0 = [29,31,33,37,38,36],
# num1 = [29,37]
# num2 = [31,29,35,38,36]
# num3 = [31,29,37,35,36]
# num4 = [33,37,29,35]
# num5 = [31,33,35,37,36]
# num6 = [31,33,37,36,38,35]
# num7 = [31,29,37]
# num8 = [31,29,33,36,37,38,35]
# num9 = [29,31,33,35,36,37]
#dot  [40]

num0 = [16,18,22,11,13,15,37]
num1 = [16,13]
num2 = [18,16,11,37,15]
num3 = [18,16,11,13,15]
num4 = [22,11,16,13]
num5 = [18,22,11,13,15]
# num6 = [31,33,37,36,38,35]
# num7 = [31,29,37]
# num8 = [31,29,33,36,37,38,35]
# num9 = [29,31,33,35,36,37]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

def pin_lighter(pin,pause):
    #GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(pin,GPIO.LOW)
    

while True:
    time.sleep(sec)
    for n in range(50):
        for i in num0:
            pin_lighter(i, sec)
   
    for n in range(50):
        for i in num1:
            pin_lighter(i, sec)
    
    for n in range(50):
        for i in num2:
            pin_lighter(i, sec)
    
    for n in range(50):
        for i in num3:
            pin_lighter(i, sec)

    for n in range(50):
        for i in num4:
            pin_lighter(i, sec)

    for n in range(50):
        for i in num5:
            pin_lighter(i, sec)
        
#     for n in range(50):
#         for i in num6:
#             pin_lighter(i, sec)
#         
#     for n in range(50):
#         for i in num7:
#             pin_lighter(i, sec)
#     
#     for n in range(50):
#         for i in num8:
#             pin_lighter(i, sec)
#     
#     for n in range(50):
#         for i in num9:
#             pin_lighter(i, sec)
GPIO.cleanup()    