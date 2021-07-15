#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py

import socket
import sys
from _thread import *  # low level threading library
import display as segment

# initialization to get the arguments name, and the port,
input_arguments = sys.argv

HOST = ''  # symbolic name meaning all available interfaces 
PORT = int(input_arguments[1])  # arbitrary non-privileged port
numconn = 10  # number of simultaneous connections
buffer_size = 4096  # input buffer size

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('...bind failed...error code: ' + str(msg.arg[0]) + ', error message: ' + msg.arg[1])
    sys.exit()

print('...socket bind complete...')

# make socket to listen incoming connections
s.listen(numconn)
print('...socket now listening...')


# function for handling connections...this will be used to create threads
def clientthread(conn):
    import RPi.GPIO as GPIO
    #Initialization of led pin
    DISPLAY_LED1 = 11
    DISPLAY_LED2 = 13

    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(DISPLAY_LED1, GPIO.OUT)
    GPIO.setup(DISPLAY_LED2, GPIO.OUT)

    LED_STATE = 0
    # sending message to connected client
    conn.send('...welcome to the server...type something and hit enter \n'.encode())  # send only takes bytes
    # infinite loop so that the function does not terminate and the thread does not end
    while True:
        try:
            # receiving from client
            data = conn.recv(buffer_size)  # receives bytes
            if not data:
                break
            
            received_message = data.decode()        
            print("received message: "+ data.decode())
            
        
            
            # Blink the led and Receiving button command and answer to the client
            if received_message == "ON":
                if LED_STATE == 0:
                    GPIO.output(DISPLAY_LED1, GPIO.HIGH)
                    GPIO.output(DISPLAY_LED2, GPIO.HIGH)
                    reply = "LED has been TURNED ON"
                    LED_STATE = 1
                else:
                    reply = "LED is already ON"
            
            elif received_message == "OFF":
                if LED_STATE == 1:
                    GPIO.output(DISPLAY_LED1, GPIO.LOW)
                    GPIO.output(DISPLAY_LED2, GPIO.LOW)
                    reply = "LED has been TURNED OFF"
                    
                    LED_STATE = 0
                else:
                    reply = "LED is already OFF"
            
            elif received_message == "1":
                reply = "Increament count"
                segment.display_controller(received_message)
                
                
            elif received_message == "2":
                reply = "Decreament count"
                segment.display_controller(received_message)
                
                
            elif received_message == "3":
                reply = "Displaying random number"
                segment.display_controller(received_message)
                
                
            else:
                reply = "ON/OFF to control the LED and (0-1-2-3) to control the display"
                
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
