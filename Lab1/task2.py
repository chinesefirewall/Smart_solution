import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

sec = 0.05

pin = [8,10,12,16,18,22,24,26,38,40]
reverse_pin = [40,38,26,24,22,18,16,12,10,8]

def pin_lighter(pin,pause):
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(pin,GPIO.LOW)

while True:
    for i in pin:
        pin_lighter(i,sec)
    for i in reverse_pin:
        pin_lighter(i,sec)
        
GPIO.cleanup()

#     
# GPIO.setup(pin, GPIO.OUT)


# while True:
#     for LED in pin:
#         GPIO.output(LED, GPIO.HIGH)
#         time.sleep(sec)
#         GPIO.output(LED, GPIO.LOW)
# 
# GPIO.cleanup()



