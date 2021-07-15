#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full socket client example in python
# file: juhendid-sockets-nutipraks-2020-code-client-http.py
# adapted by: Jyri J6ul

import socket  # for sockets
import sys  # for exit
import time

# initialization of command line argument parsing
input_arguments = sys.argv

# initialise constants
host = 'www.ut.ee'
port = int(input_arguments[2])
buffer_size = 4096

#creating socket  instance
try:
    # create an AF_INET, STREAM socket (TCP)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print('...failed to create socket...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket created...')


#Obtaining the ip address through arguments
try:
    remote_ip = input_arguments[1]
except socket.gaierror:
    # could not resolve
    print('...hostname could not be resolved...exiting...')
    sys.exit()

print('...IP address of ' + host + ' is ' + remote_ip)

# connect to remote server
s.connect((remote_ip, port))

print('...socket connected to ' + host + ' on IP ' + remote_ip)


while True:
    
    # now receive data
    reply = s.recv(buffer_size).decode()
    print(reply)
    
    #comming
    message = input("Please enter the message to be sent: ")
    
    # send some data to remote server
    try:
        # send string encoded as bytes
        s.sendall(message.encode())
        print(message.encode())
    except socket.error:
        # send failed
        print('...send failed...')
        sys.exit()

    print('...message sent successfully...')
    

    time.sleep(0.5)


# close the socket
s.close()
