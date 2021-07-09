#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py

import socket
import sys
from _thread import *  # low level threading library

#get arguments name, port,
arguments = sys.argv

HOST = '127.0.0.4'  
PORT = int(input("Enter port No. : "))

# HOST = ''  # symbolic name meaning all available interfaces
# PORT = int(arguments[1])  # arbitrary non-privileged port
numconn = 10  # number of simultaneous connections
buffer_size = 4096  # input buffer size

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('...bind failed...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket bind complete...')

# make socket to listen incoming connections
s.listen(numconn)
print('...socket now listening...')


# function for handling connections...this will be used to create threads
def clientthread(conn):
    import RPi.GPIO as GPIO
    #setup LED
    LED_PIN = input(int('Enter LED pin number: '))

    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(LED_PIN,GPIO.OUT)

    LED_STATUS = 0
    # sending message to connected client
    conn.send('...welcome to the server...type something and hit enter \n'.encode())  # send only takes bytes
    # infinite loop so that the function does not terminate and the thread does not end
    while True:
        try:
            # receiving from client
            data = conn.recv(buffer_size)  # receives bytes
            if not data:
                break
            
            received_msg = data.decode()        
            print("received message: "+ data.decode())
            
        
            
            #blink LED and answer apropriately
            if received_msg == "ON":
                if LED_STATUS == 0:
                    GPIO.output(LED_PIN,GPIO.HIGH)
                    reply = "Turned LED ON"
                    LED_STATUS = 1
                else:
                    reply = "LED is already ON"
            
            elif received_msg == "OFF":
                if LED_STATUS == 1:
                    GPIO.output(LED_PIN,GPIO.LOW)
                    reply = "Turned LED OFF"
                    
                    LED_STATUS = 0
                else:
                    reply = "LED is already OFF"
                    
            else:
                reply = "ON/OFF only accepted"
                
            print(reply)
            conn.sendall(reply.encode())
            
        except socket.error as message:  # error, for example if the connection is closed
            print(message)
            break
    # came out of loop
    conn.close()


# now keep talking with the client (infinite loop)
while True:
    # wait to accept a connection - blocking call
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    # start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function
    start_new_thread(clientthread, (conn,))

s.close()
