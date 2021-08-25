# 
# import serial
# import time
# import RPi.GPIO as GPIO
# 
# #setup
# GPIO.setmode(GPIO.BOARD)
# GPIO.setwarnings(False)
# GPIO.setup(40, GPIO.OUT)
# 
# ser = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1)
# 
# # initial condition
# led = False
# 
# if ser.isOpen():
#     print("Serial open")
#     while True:
#         while ser.in_waiting():
#             if ser.in_waiting()>0:
#                 from_serial = ser.readline()
#                 from_serial = from_serial.decode().rstrip()
#                 if from_serial == "on":
#                     GPIO.output(40, GPIO.HIGH)
#                     print('LED on')
#                     led = True
#                 if from_serial == "off":
#                     GPIO.output(40, GPIO.LOW)
#                     print('LED off')
#                     led = False
#                 if from_serial == "info":
#                     print(led, "state")
#                     ser.write('state'.encode())
#             
#                 print(from_serial)
#                 time.sleep(0.2)
# else:
#     print("Serial is closed")



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
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1) 
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



    
    

