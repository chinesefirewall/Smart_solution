import RPi.GPIO as GPIO
import time

sec = 0.01
#leds = [29,31,33,35,37,40,38]
leds = [8,10,12,16,18,22,24,26]

num0 = [8,10,12]
# num1 = [8,24]
# num2 = [10,12,26,38,40]

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(leds,GPIO.OUT)

def pin_lighter(pin,pause):
    #GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(pin,GPIO.LOW)
    

while True:
    #for n in range(50):
    for i in num0:
            pin_lighter(i, sec)
            
GPIO.cleanup()      
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num1:
#             light_pin(i,0.003)
# #         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num2:
#             light_pin(i,0.003)
# #         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num3:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
# 
#     for n in range(50):
#         for i in num4:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
# 
#     for n in range(50):
#         for i in num5:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num6:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num7:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num8:
#             light_pin(i,0.003)
#         
#     time.sleep(0.5)
#     
#     for n in range(50):
#         for i in num9:
#             light_pin(i,0.003)
        
#     time.sleep(0.5)
    
###################################
    
# num0= [29,31,33,37,40,38]
# num1= [29,38]
# num2= [31,29,35,37,40]
# num3= [31,29,35,38,40]
# num4= [33,29,35,38]
# num5= [31,33,35,38,40]
# num6= [31,33,35,38,40,37]
# num7= [31,29,38]
# num8= [31,29,33,35,37,38,40]
# num9= [31,33,35,29,38,40]