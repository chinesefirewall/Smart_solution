import RPi.GPIO as GPIO    
import time  

count = 0

def my_call(channel):
    global count
    if GPIO.input(channel) == GPIO.HIGH:
        count+=1
        print("Pressed!")
    else:
        print("Released")
    



try:
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    button = 11
    GPIO.setup(button, GPIO.IN)
    GPIO.add_event_detect(button, GPIO.BOTH, callback=my_call)

    
    message = input("Press any key to exit: ")

finally:
    GPIO.cleanup()
    

print(f"Pressed {count} times")