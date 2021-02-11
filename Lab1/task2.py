import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

sec = 0.2

pin = [16,18,22,36,37,35,38,40,3,5]
# LED2 = 18
# LED3 = 22
# LED4 = 36
# LED5 = 37
# LED6 = 35
# LED7 = 38
# LED8 =40
# LED9 = 
# LED10 =
    
GPIO.setup(pin, GPIO.OUT)
# GPIO.setup(LED2, GPIO.OUT)
# GPIO.setup(LED3, GPIO.OUT)
# GPIO.setup(LED4, GPIO.OUT)
# GPIO.setup(LED5, GPIO.OUT)
# GPIO.setup(LED6, GPIO.OUT)
# GPIO.setup(LED7, GPIO.OUT)
# GPIO.setup(LED8, GPIO.OUT)
# GPIO.setup(LED9, GPIO.OUT)
# GPIO.setup(LED10, GPIO.OUT)



while True:
    for LED in pin:
        GPIO.output(LED, GPIO.HIGH)
        time.sleep(sec)
        GPIO.output(LED, GPIO.LOW)
#     
#     GPIO.output(LED2, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED2, GPIO.LOW)
#     
#     
#     GPIO.output(LED3, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED3, GPIO.LOW)
#     
#     GPIO.output(LED4, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED4, GPIO.LOW)
#     
#     GPIO.output(LED5, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED5, GPIO.LOW)
#     
#     GPIO.output(LED6, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED6, GPIO.LOW)
#     
#     GPIO.output(LED7, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED7, GPIO.LOW)
#     
#     GPIO.output(LED6, GPIO.HIGH)
#     time.sleep(sec)
#     GPIO.output(LED6, GPIO.LOW)
    
    
GPIO.cleanup()

