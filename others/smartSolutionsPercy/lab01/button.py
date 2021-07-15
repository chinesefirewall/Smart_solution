import RPi.GPIO as GPIO

button_pin = 36

def button_callback(channel):
    print("Button was pressed")
    
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.add_event_detect(button_pin, GPIO.RISING, callback = button_callback, bouncetime=200)

message = input("Press enter to stop\n\n")

GPIO.cleanup()