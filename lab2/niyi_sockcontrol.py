import socket
import sys
import time
from _thread import *  # low level threading library
import RPi.GPIO as GPIO

pin = int(input('Enter LED pin number: ')) # led pins
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#setting pins
GPIO.setup(pin, GPIO.OUT)


# Creates thread for per connection from clients
def clientthread(conn):
    global turn_led
    global lock_1
    global tf
    
    
    buffer_size = 4096
    # sending message to connected client
    conn.send('...welcome to the control server...type something and hit enter \n'.encode())  # send only takes bytes
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
                            break
                        elif data_1 == "off":
                            if turn_led == True:
                                reply = "LED OFF"
                                
                                turn_led = False
                            else:
                                reply = "LED is already OFF"

                        elif data_1 == 'frequency':
                            freq = True
                            reply = "Enter Frequency: "

                        elif freq:
                            f = int(data_1)
                            tf = float(1/(4*f))
                            reply = "Frequency set to " + str(f) + " Hz"
                            
                        else:
                            reply = "Enter on/off/frequency"

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
    pass


def led_program():
    global tf
    global turn_led
    while True:
        if turn_led: 
            GPIO.output(pin[0], GPIO.HIGH)
            time.sleep(tf)
            GPIO.output(pin[0], GPIO.LOW)
            time.sleep(tf)
            GPIO.output(pin[1], GPIO.HIGH)
            time.sleep(tf)
            GPIO.output(pin[1], GPIO.LOW)
            time.sleep(tf)

turn_led = False
turn_seg = False
freq = False
tf = 0.5
lock_1 = False


host = '127.0.0.1'  
port = int(input("Enter port No. : "))
numconn = 10    

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((host, port))
except socket.error as msg:
    print('...bind failed...error code: ' + str(msg.arg[0]) + ', error message: ' + msg.arg[1])
    sys.exit()

print('...socket bind complete...')

# listens to  incoming connections
s.listen(numconn)
print('...socket now listening...')

start_new_thread(led_program, ())
while True:
    # wait to accept a connection 
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    start_new_thread(clientthread, (conn,)) # Starts new thread to handle all connections
s.close()
