import socket
import sys
import time
from _thread import *  # low level threading library
import RPi.GPIO as GPIO

pin = [40, 38]  # int(input('Enter LED pin number: ')) # led pins #LED_pin=[40, 38]
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#setting pins
GPIO.setup(pin, GPIO.OUT)


host = '169.254.92.143' #'127.0.0.1' # 192.168.1.241 
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

#start_new_thread(led_program, ())
while True:
    # wait to accept a connection 
    conn, addr = s.accept()


    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))
    
    buffer_size = 4096
    # sending message to connected client
    conn.send('...welcome to Niyi control server...type something 1 for LED, after, on, stop, off: '.encode())  # send only takes bytes
    try:
        # receiving from client
        data = conn.recv(buffer_size)  # receives bytes
        data1 = data.decode()
        conn.send("led selected".encode())
        f = int(data_1)
        tf = float(1/(4*f))
        reply = "Frequency set to " + str(f) + " Hz"
        
    #                                                                   ####################################33
     
        GPIO.output(pin[0], GPIO.HIGH)
        time.sleep(tf)
        print('led sould be on')
        GPIO.output(pin[0], GPIO.LOW)
        time.sleep(tf)
        GPIO.output(pin[1], GPIO.HIGH)
        time.sleep(tf)
        GPIO.output(pin[1], GPIO.LOW)
    except:
        print('exception error')

    

  ##############################################                                ##################################  

    # start_new_thread(clientthread, (conn,)) # Starts new thread to handle all connections
    #start_new_thread(clientthread, (conn,))
s.close()

