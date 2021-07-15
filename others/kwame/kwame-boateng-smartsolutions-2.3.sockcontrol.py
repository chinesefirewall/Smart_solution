import socket
import sys
from _thread import *
import RPi.GPIO as GPIO
import time
import numpy as np

pin_leds =[12,16]
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin_leds,GPIO.OUT)

pin_sevenseg = [26,19,13,6,5,21,20]
GPIO.setup(pin_sevenseg, GPIO.OUT)  

# Initial conditions
turn_on = False
fr_on = False
seg_on = False
led_trig= False
seg_trig = False
t = 0.25
b_counter=0


HOST = "192.168.43.82"
PORT = int(input("Enter port number: "))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("...socket created...")
try:

    s.bind((HOST, PORT))
except socket.error as msg:
    print("...bind failed...error code: " + str(msg.arg[0]) + "error message: " +
          msg.arg[1])
    sys.exit()
print("...socket bind complete...")

# makes socket listen to connections
s.listen(5)
print("...socket now listening...")

def led_light():
    global pin_leds
    global turn_on
    global t
    
    while True:
        if turn_on == True:
            
            GPIO.output(pin_leds[0],GPIO.HIGH)
            GPIO.output(pin_leds[1],GPIO.LOW)
            time.sleep(t)
            GPIO.output(pin_leds[0],GPIO.LOW)
            GPIO.output(pin_leds[1],GPIO.HIGH)
            time.sleep(t)
        


def seven_seg():
    global b_counter
    global pin_sevenseg
    global seg_on
    
    def switch_led(number):
        for i in range(len(number)):
            GPIO.output(pin_sevenseg[i],number[i])

    def off_led():
        GPIO.output(pin_sevenseg, GPIO.LOW)
        
    # LED Number array 
    # num0=[0,0,0,0,0,0,1]
    # num1=[1,1,0,0,1,1,1]
    # num2=[0,0,1,0,0,1,0]
    # num3=[1,0,0,0,0,1,0]
    # num4=[1,1,0,0,1,0,0]
    # num5=[1,0,0,1,0,0,0]
    # num6=[0,0,0,1,0,0,0,]
    # num7=[1,1,0,0,0,1,1]
    # num8=[0,0,0,0,0,0,0]
    # num9=[1,0,0,0,0,0,0,]
    
    
    
    num0=[1,1,1,1,1,1,0]
    num1=[0,0,1,1,0,0,0]
    num2=[1,1,0,1,1,0,1]
    num3=[0,1,1,1,1,0,1]
    num4=[0,0,1,1,0,1,1]
    num5=[0,1,1,0,1,1,1]
    num6=[1,1,1,0,1,1,1,]
    num7=[0,0,1,1,1,0,0]
    num8=[1,1,1,1,1,1,1]
    num9=[0,1,1,1,1,1,1,]
    
    c = 0
    a = 1
    
    
    while True:
        if seg_on == True:
            if b_counter == 1: # reverse
                a = -1
                
            if b_counter == 2: # random
                ran = np.random.randint(10, size=1)
                c = ran[0]
                
            if b_counter == 3: # return
                a = 1
                
            if c == 0:
                switch_led(num0)
                time.sleep(1)
                off_led()
            if c == 1:
                switch_led(num1)
                time.sleep(1)
                off_led()
            if c == 2:    
                switch_led(num2)
                time.sleep(1)
                off_led()
            if c == 3:   
                switch_led(num3)
                time.sleep(1)
                off_led()
            if c == 4:   
                switch_led(num4)
                time.sleep(1)
                off_led()
            if c == 5:    
                switch_led(num5)
                time.sleep(1)
                off_led()
            if c == 6:   
                switch_led(num6)
                time.sleep(1)
                off_led()
            if c == 7:    
                switch_led(num7)
                time.sleep(1)
                off_led()
            if c == 8:    
                switch_led(num8)
                time.sleep(1)
                off_led()
            if c == 9:    
                switch_led(num9)
                time.sleep(1)
                off_led()
        
            c +=a
            if c>9:
                c = 0
            elif c< 0:
                c = 9
    
    
           
    

# function for handling connections... this will be use to create threads
def myclientthread(com):
    global turn_on
    global freq
    global t
    global fr_on
    global seg_on
    global b_counter
    global led_trig
    global seg_trig
    # send message to connected client
    com.send("...welcome to the server...enter a 1 for Led or 2 for Seven Seg".
             encode())  # send only takes bytes

    while True:
        try:
            # receiving data from client
            info = com.recv(4096)
            if not info:
                break
            
                
            if info.decode() == "1" and led_trig == False:
                com.send("LED program".encode())
                led_trig = True
                
                while True:
                    info = com.recv(4096)
                    if not info:
                         break
                            
                    if info.decode() == "start":
                        com.send("LED is now ON".encode())
                        turn_on = True
                        
                    if info.decode() == "stop":
                        com.send("LED is OFF".encode())
                        turn_on = False
                        led_trig = False
                        break
                    
                    if fr_on == True:
                        freq = float(info.decode())
                        t = float(1/(4*freq))
                        com.send(str(t).encode())
                        fr_on = False
                        
                    elif info.decode() == "frequency" :
                        com.send("what frequency: ".encode())
                        fr_on = True
                            
            elif info.decode() == "1" and led_trig == True:
                com.send("LED program is locked!".encode())
                
            if info.decode() == "2" and seg_trig == False:
                com.send("SEVEN SEG program".encode())
                seg_trig = True
                
                while True:
                    info = com.recv(4096)
                    if not info:
                         break
                
                    if info.decode() == "start":
                        com.send("Program started".encode())
                        seg_on = True
                        
                    if info.decode() == "stop":
                        com.send("Exiting".encode())
                        seg_on = False
                        seg_trig = False
                        break
                    
                    if info.decode() == "reverse":
                        com.send("Reversing order".encode())
                        b_counter = 1
                    if info.decode() == "random":
                        com.send("Randomising order".encode())
                        b_counter = 2
                    if info.decode() == "restore":
                        com.send("Going back to normal".encode())
                        b_counter = 3
                        
            elif info.decode() == "2" and seg_trig == True:
                com.send("SEVEN SEG is locked!".encode())
                
            
            respond = "...OK..." + info.decode()  # decodes bytes to string
            print("received")
            print(info.decode())
            print("sent")
            print(respond)
        except socket.error as message:  # error, for example if the connection is closed
            print(message)
            break
    com.close()

start_new_thread(led_light, ())
start_new_thread(seven_seg, ())
try:
    while True:
        com, addr = s.accept()
        # display client information
        print("...connected with", addr[0], ":", str(addr[1]))
    
        # start new thread takes 1st argument as function and name to be run, second is the tuple of the arguments to the function.
        start_new_thread(myclientthread, (com,))
except KeyboardInterrupt:
    GPIO.cleanup()    
s.close()
