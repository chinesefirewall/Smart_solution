#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py

import socket
import sys
from _thread import *  # low level threading library
import RPi.GPIO as GPIO
import random
import time

# initialization to get the arguments name, and the port,
input_arguments = sys.argv

HOST = ''  # symbolic name meaning all available interfaces 
PORT = int(input_arguments[1])  # arbitrary non-privileged port
numconn = 10  # number of simultaneous connections
buffer_size = 4096  # input buffer size
FREQUENCY = 4


isON = False
isDisplayed = False
display = ""
isBusy = False
isDisplayBusy = False

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


def light(num, pins):
    numbers = [[1,1,1,1,1,1,0],
           [0,1,1,0,0,0,0],
           [1,1,0,1,1,0,1],
           [1,1,1,1,0,0,1],
           [0,1,1,0,0,1,1],
           [1,0,1,1,0,1,1],
           [1,0,1,1,1,1,1],
           [1,1,1,0,0,0,0],
           [1,1,1,1,1,1,1],
           [1,1,1,1,0,1,1]]
    for i in range(len(pins)):
        GPIO.output(pins[i], 1 - numbers[num][i])


def display_controller():
    
    global isDisplayed, display
    # leds for seven segment
    all_leds = [29, 31, 33, 35, 37, 40, 38]

    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(all_leds, GPIO.OUT)
     
    counter_back = 9
    
    while True:
        if display == "0":
            for i in range(10):
                light(0, all_leds)
                time.sleep(0.5)
                
        elif display == "1":
            for i in range(10):
                light(i, all_leds)
                time.sleep(0.5)
            
            
        elif display == "2":
            for i in range(10):
                light(counter_back - i, all_leds)
                time.sleep(0.5)
                if counter_back == -1:
                    counter_back = 9
            
            
        elif display == "3":
            number = random.randrange(10)
            light(number, all_leds)
            time.sleep(2)
            
        
        else:
            pass
        
        
# Blink the led and Receiving button command and answer to the client
def led_controller():
    
    #Initialization of led pin
    DISPLAY_LED1 = 11
    DISPLAY_LED2 = 13
    
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(DISPLAY_LED1, GPIO.OUT)
    GPIO.setup(DISPLAY_LED2, GPIO.OUT)
    
    global LED_STATE, FREQUENCY, isON
    
    while True:
        if isON:
            GPIO.output(DISPLAY_LED1, GPIO.HIGH)
            GPIO.output(DISPLAY_LED2, GPIO.LOW)
            time.sleep(1 / (FREQUENCY/2))
            
            
            GPIO.output(DISPLAY_LED1, GPIO.LOW)
            GPIO.output(DISPLAY_LED2, GPIO.HIGH)
            
            time.sleep(1 / (FREQUENCY/2))
        
        if (isON == False):
            GPIO.output(DISPLAY_LED1, GPIO.LOW)
            GPIO.output(DISPLAY_LED2, GPIO.LOW)                


# function for handling connections...this will be used to create threads
def clientthread(conn):
    
    global isON, isDisplayed, display, isBusy, isDisplayBusy

    
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
            
        
            if received_message == "STARTLED":
                if isBusy:
                    reply = "The LED is busy"
                else:
                    reply = "LED is turned ON"
                    isON = True
                    isBusy = True
            elif received_message == "ENDLED":
                reply = "LED is turned OFF"
                isON = False
                isBusy = False
            elif "FREQUENCY" in received_message:
                message = split('=')
                FREQUENCY = message[1]
                
            elif received_message == "DISPLAY":
                if isDisplayBusy:
                    reply = "The Display is busy!!!"
                else:
                    reply = "Display activated!"
                    isDisplayBusy = True
                    
            elif received_message == "0" or received_message == "1" or received_message == "2" or received_message == "3":
                if isDisplayBusy:
                    display = received_message
                    reply = "Displaying....."
                else:
                    reply = "The Display is not initialize!!!"
                    
            elif received_message == "OFFDISPLAY":
                reply = "Turning off the display"
                isDisplayBusy = False

                   
            else:
                reply = "STARTLED/ENDLED to control the LED and (0-1-2-3) to control the display"
            
            
                
                
            print(reply)
            conn.sendall(reply.encode())
            
        except socket.error as message:  # error, for example if the connection is closed
            print(message)
            break
    # came out of loop
    conn.close()


start_new_thread(display_controller, ())
start_new_thread(led_controller, ())

# now keep talking with the client (infinite loop)
while True:
    # wait to accept a connection - blocking call
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    # start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function
    start_new_thread(clientthread, (conn,))

s.close()
GPIO.cleanup()
