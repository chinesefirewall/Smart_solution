#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py

import socket
import sys
import time
import random

from _thread import *  # low level threading library

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
 = GPIO.getmode()
GPIO.setwarnings(False)
GPIO.setup(3, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(5, GPIO.OUT, initial=GPIO.LOW)


HOST = ''  # symbolic name meaning all available interfaces
PORT = int(input('Port number: '))  # arbitrary non-privileged port
numconn = 10  # number of simultaneous connections
buffer_size = 4096  # input buffer size



s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    #print('...bind failed...error code: ' + str(msg.arg[0]) + ', error message: ' + msg.arg[1])
    sys.exit()

print('...socket bind complete...')

# make socket to listen incoming connections
s.listen(numconn)
print('...socket now listening...')

flashing = 0
freq = 0
addresslist=[]
N = 0

# function for handling connections...this will be used to create threads
def clientthread(conn,addr):
    global flashing, freq, command, addresslist
    # sending message to connected client
    #conn.send('...welcome to the server...type something and hit enter \n'.encode())  # send only takes bytes
    # infinite loop so that the function does not terminate and the thread does not end
    while True:
        try:              
            if (addr not in addresslist and len(addresslist)== 0) or addresslist[0] == addr:
            
                
                conn.send('Flashing on/off: '.encode())
                data = conn.recv(buffer_size)
                decodedl = data.decode()    
                decodedl = decodedl.split(' ')
                flashing = decodedl[1]
                freq = decodedl[3]
                print('l',addresslist)
                
                if flashing == 'off':    
                    conn.send('LED is off \n'.encode()) 
                    
                elif flashing == 'on':    
                    conn.send('LED is on \n'.encode()) 
                    
                if addr not in addresslist:    
                    addresslist.append(addr)  
                
            elif (addr not in addresslist and len(addresslist)== 1) or addresslist[1] == addr:
              
                conn.send('Enter command(start,reverse,random or restore): '.encode())
                data = conn.recv(buffer_size)
                decodedl = data.decode() 
                conn.send('numbers on \n'.encode())
                command = decodedl
                
                if addr not in addresslist:    
                    addresslist.append(addr)  
                
                print('n',addresslist)    
        
            
            
        except socket.error as message:  # error, for example if the connection is closed
            print('Breaking')
            break
            
    # came out of loop
    conn.close()
    
def flashing_LED():
    while True:
        global flashing, freq
            
        #print(flashing)

        if flashing == 'on':
            GPIO.output(3, 1)
            time.sleep(1/(2*float(freq)))
            GPIO.output(3,0)

            GPIO.output(5,1) 
            time.sleep(1/(2*float(freq)))                    
            GPIO.output(5,0)
            
        elif flashing == 'off':
                GPIO.output(3,0)  
                GPIO.output(5,0)
                
def pin_lighter(pin,pause):
    #GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(pause)
    GPIO.output(pin,GPIO.LOW)
    
command = 0
def seven_seg():
    global command
    def number(n):
        t = 0.5
        sec = 0.5
        if n==0:        #0
            # 16,18,22,11,13,15,37
            GPIO.output(16, 0) 
            GPIO.output(18,0)
            GPIO.output(22,0)
            GPIO.output(13,0)
            GPIO.output(15,0)
            GPIO.output(37, 0)
            time.sleep(t)
            GPIO.output(22, 1)
            GPIO.output(18,1)
            GPIO.output(13,1)
            GPIO.output(15,1)
            GPIO.output(37,1)
            GPIO.output(16, 1)
            
            
        if n==1:    #1
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH) 
            time.sleep(t)
            GPIO.output(16,GPIO.LOW)
            GPIO.output(13,GPIO.LOW)

            
        if n==2:       #2
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(16, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            
            
        if n==3:        #3
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(16, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            
            
        if n==4:        #4
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(16,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            
            
        if n==5:        #5
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            
            
        if n==6:        #6
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            
            
        if n==7:        #7
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            time.sleep(t)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
          
            
        if n==8:        #8
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(16, GPIO.HIGH)
            time.sleep(t)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            GPIO.output(16, GPIO.LOW)
           
            
        if n==9:        #9
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(11, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(16, GPIO.HIGH)
            time.sleep(t)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(11, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(16, GPIO.LOW)
        
    
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(leds,GPIO.OUT)
        
        
#     GPIO.setmode(GPIO.BOARD)
#     mode = GPIO.getmode()
#     GPIO.setwarnings(False)
#     pinB = 16
#     pinA = 18
#     pinF = 22
#     pinG = 11
#     pinC = 13
#     pinD = 15
#     pinE = 37

    pins = [16,18,22,11,13,15,37]
    GPIO.setup(pins, GPIO.OUT)
#     GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)
    
    
    num0 = [16,18,22,11,13,15,37]
    num1 = [16,13]
    num2 = [18,16,11,37,15]
    num3 = [18,16,11,13,15]
    num4 = [22,11,16,13]
    num5 = [18,22,11,13,15]
     
    i = 0
    #time.sleep(t) 

    while True:
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
            print(i)
            number(i)
            
        if command == 'restore':
            number(i)
            i=i+1
            if i == 10:
                i = 0           
        

start_new_thread(flashing_LED,())
start_new_thread(seven_seg,())


# now keep talking with the client (infinite loop)
while True:
    # wait to accept a connection - blocking call
    
    conn, addr = s.accept()
    print(conn)
    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))


    # start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function
    start_new_thread(clientthread, (conn,addr))
  
s.close()