#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py
# adapted by: Richard Erelt
import socket
import sys
from _thread import *  # low level threading library
import time
#for LED
try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("error in GPIO import")

GPIO.setmode(GPIO.BOARD)
mode = GPIO.getmode()
GPIO.setwarnings(False)
GPIO.setup(40, GPIO.OUT)


HOST = ''  # symbolic name meaning all available interfaces
PORT = 91 
numconn = 5  # number of simultaneous connections
buffer_size = 4096  # input buffer size

led_state = 0
freq = 1

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('...bind failed...error code: ' + str(msg.arg[0]) + ', error message: ' + msg.arg[1])
    sys.exit()

print('...socket bind complete...')
print(HOST)

# make socket to listen incoming connections
s.listen(numconn)
print('...socket now listening...')
def led_code():
    print('led')
    global led_state
    global freq
    if led_state == 1:
        GPIO.output(40, GPIO.HIGH)
        
    if led_state == 2: 
        GPIO.output(40, GPIO.LOW)
        time.sleep(freq)
    pass 

# function for handling connections...this will be used to create threads
def clientthread(conn):
    # sending message to connected client
    conn.send('...welcome to the server...type something and hit enter \n'.encode())  # send only takes bytes
    # infinite loop so that the function does not terminate and the thread does not end
    global led_state
    global freq
    while True:
        try:
            data = conn.recv(buffer_size)  # receives bytes
            if not data:
                break
            print(data.decode())    
            if (data.decode()) == "on":
                led_state = 1
                led_code()
                print('on')
                
            if (data.decode()) == "off":
                led_state = 2
                led_code()
                print('off')
          
            
            reply = '...OK...' + data.decode()  # decode bytes to string
            
            conn.sendall(reply.encode())
        except socket.error as message:  # error, for example if the connection is closed
            print(message)
            break
    # came out of loop
    


# now keep talking with the client (infinite loop)
while True:
    # wait to accept a connection - blocking call
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    # start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function
    start_new_thread(clientthread, (conn,))

s.close()
