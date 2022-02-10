import time
import serial
import sys
import RPi.GPIO as GPIO    


GPIO.setmode(GPIO.BOARD)

#mode = GPIO.getmode()

GPIO.setwarnings(False)
pin_out = 40
GPIO.setup(pin_out, GPIO.OUT, initial=GPIO.LOW)
led_statuses = {False: 'OFF', True:'ON'}

is_led_on = False
messages = ("on", "off")



# Other ports
# /dev/ttyUSB0
# /dev/ttyS0
# /dev/ttyAMA0 BT module (HC06)
# /dev/rfcomm0 built in BT

try:
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1) 
    ser.flush()
    while True:        

        if ser.in_waiting > 0:
            #ser.
            message = ser.readline().decode('ascii').rstrip()
            print(f"[DEBUG] {message}")
            
            if message.lower() not in messages:
                reply = f"command {message} was not recognized"
                print(f"[INFO] {reply}")
                continue
            
            if message == "on":
                if is_led_on:
                    reply = "LED is already on!"
                    #ser.write(reply.encode('ascii'))
                    #print(f"[INFO] {reply}")
                    
                else:
                    GPIO.output(pin_out, GPIO.HIGH)
                    reply = "LED is on!"
                    #ser.write(reply.encode('ascii'))
                    #print(f"[INFO] {reply}")
                    is_led_on = True
                    
            elif message == "off":
                if not is_led_on:
                    reply = "LED is already off!"
                    #ser.write(reply.encode('ascii'))
                    #print(f"[INFO] {reply}")
                    
                else:
                    GPIO.output(pin_out, GPIO.LOW)
                    reply = "LED is off!"
                    #print(f"[INFO] {reply}")
                    #ser.write(reply.encode('ascii'))
                    is_led_on = False
            
            
            
            print(f"[INFO] {reply}")
            
            
            
            


except KeyboardInterrupt:
    print("Programm stopped")
    # close serial
    ser.close()
    print("Serial closed")
   
    
    



except:
    print(f"[ERROR] {sys.exc_info()[0]}")
    raise



    
    
