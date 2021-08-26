import socket
import sys
import time
import random
from _thread import *  # low level threading library
import RPi.GPIO as GPIO

pin = [40, 38]  # int(input('Enter LED pin number: ')) # led pins #LED_pin=[40, 38]
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

#setting pins
GPIO.setup(pin, GPIO.OUT)

# Creates thread for per connection from clients
def clientthread(conn):
    global turn_led
    global lock_1
    global lock_2
    global tf
    global freq
    global command
    
    buffer_size = 4096
    # sending message to connected client
    conn.send('...welcome to Niyi control server...type 1 = LED/ 2 = 7-segment LED: '.encode())  # send only takes bytes
    while True:
        try:
            # receiving from client
            data = conn.recv(buffer_size)  # receives bytes
            if not data:
                break

            if not lock_1:
                if data.decode()=="1":
                    conn.send("led selected".encode())
                    lock_1 = True

                    while True:
                        data_1 = conn.recv(buffer_size)
                        data_1= data_1.decode()

                        # Work on LED
                        if data_1 == "on":
                            if turn_led == False:
                                reply = "LED ON"
                                turn_led = True
                            else:
                                reply = "LED is already ON"
                                
                        elif data_1 == "stop":
                            reply = "Back to main program"
                            lock_1 = False
                            turn_led = False
                            conn.sendall(reply.encode())
                            break
                        
                        elif data_1 == "off":
                            if turn_led == True:
                                reply = "LED OFF"
                                
                                turn_led = False
                            else:
                                reply = "LED is already OFF"

                        elif data_1 == 'f':
                            freq = True
                            reply = "Enter Frequency: "

                        elif freq:
                            f = int(data_1)
                            tf = float(1/(4*f)) # Calculate the frequency wrt time
                            reply = "Frequency set to " + str(f) + " Hz"
                            freq = False
                            
                        elif data_1 != "off" or data_1 != "on" or data_1 != "f" or data_1 != "stop":
                            reply = "Enter on/off/f=frequency: "

                        conn.sendall(reply.encode())
                        
            # 7 segment program            
            if not lock_2:
                if data.decode()=="2":
                    conn.send("7 Segment LED selected".encode())
                    lock_2 = True

                    while True:
                        data_2 = conn.recv(buffer_size)
                        data_2= data_2.decode()

                        # Work on LED
                        if data_2 == "start":
                            #turn_led_2 = True
                            command = "start"
                            reply = "LED started"
                        elif data_2 == "stop":
                            reply = "Back to main program"
                            lock_2 = False
                            conn.sendall(reply.encode())
                            command = "stop"
                            break
                        elif data_2 == 'rev':
                            command = "reverse"
                            reply = "LED reversed"
                        elif data_2 == 'ran':
                            command = "random"
                            reply = "LED randomised"
                        elif data_2 == 'res':
                            command = "restore"
                            reply = "LED restored"
                        elif data_2 != "rev" or data_2 != "res" or data_2 != "ran" or data_2 != "start" or data_2 != "stop":
                            reply = "Enter start/rev/res/ran/stop"

                        conn.sendall(reply.encode())
            msg_client = data.decode()        
            print("received message: "+ data.decode())
                
            print(msg_client)
            reply = "Sending back:  " + msg_client
            conn.sendall(reply.encode())
        except socket.error as message:  
            print(message)
            break
    conn.close()


def seg_program():
    global command
       
    def number(n):
        t = 1
        if n==0:        #0
            # 16,18,22,36,13,15,37
            GPIO.output(16, GPIO.LOW)
            GPIO.output(18, GPIO.LOW)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15, GPIO.LOW)
            time.sleep(t)
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18, GPIO.HIGH)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15, GPIO.HIGH)
            
        if n==1:    #1
            GPIO.output(22, GPIO.LOW)
            GPIO.output(36,GPIO.LOW) 
            time.sleep(t)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(36,GPIO.HIGH)

        if n==2:       #2
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
                
        if n==3:        #3
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(36,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
             
        if n==4:        #4
            GPIO.output(15, GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            time.sleep(t)
            GPIO.output(15, GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            
        if n==5:        #5
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            
        if n==6:        #6
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(16,GPIO.HIGH)
            
        if n==7:        #7
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
          
        if n==8:        #8
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            GPIO.output(16, GPIO.LOW)
            time.sleep(t)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(16, GPIO.HIGH)
           
        if n==9:        #9
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            time.sleep(t)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)      

    pins = [16,18,22,36,13,15,37]
    GPIO.setup(pins, GPIO.OUT)
    GPIO.output(pins, GPIO.HIGH)
    
    i = 0
    time.sleep(1)
    
    while True:
        print(command)
        if command == 'stop':
            command = 'wait'
            
        if command == 'start':
            number(i)
            i=i+1
            if i == 10:
                i = 0
        if command == 'reverse':
            number(i)
            i=i-1
            if i<0:
                i = 9
        
        if command == 'random':
            i = random.randint(0,9)
            number(i)
            
        if command == 'restore':
            number(i)
            i=i+1
            if i == 10:
                i = 0

def led_program():
    global tf
    global turn_led
    while True:
        
        if turn_led == True: 
            GPIO.output(pin[0], GPIO.HIGH)
            time.sleep(tf)
            print('led should be on')
            GPIO.output(pin[0], GPIO.LOW)
            time.sleep(tf)
            GPIO.output(pin[1], GPIO.HIGH)
            time.sleep(tf)
            GPIO.output(pin[1], GPIO.LOW)
            time.sleep(tf)

turn_led = False
turn_seg = False
freq = False  # was comment out before
tf = 0.5
lock_1 = False
lock_2 = False
command = "wait"


host = '' #'169.254.92.143' #'127.0.0.1' # 192.168.1.241 
port = int(input("Enter port No. : "))
numconn = 10    

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((host, port))
except socket.error as msg:
    print('...bind failed...')
    sys.exit()

print('...socket bind complete...')

# listens to  incoming connections
s.listen(numconn)
print('...socket now listening...')

start_new_thread(seg_program, ())
start_new_thread(led_program, ())
while True:
    # wait to accept a connection 
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    # start_new_thread(clientthread, (conn,)) # Starts new thread to handle all connections
    start_new_thread(clientthread, (conn,))
s.close()
