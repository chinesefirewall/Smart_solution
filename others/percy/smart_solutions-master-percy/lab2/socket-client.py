#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full socket client example in python
# file: juhendid-sockets-nutipraks-2020-code-client-http.py
# adapted by: Jyri J6ul

import socket  # for sockets
import sys  # for exit
import time

#command line argument parsing
arguments = sys.argv

# initialise constants
host = 'www.ut.ee'
port = int(arguments[2])
#message = "GET / HTTP/1.0\r\n\r\n"
buffer_size = 4096

#creating socket  instance
try:
    # create an AF_INET, STREAM socket (TCP)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print('...failed to create socket...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket created...')


#ip obtaining using arguments
try:
    #remote_ip = socket.gethostbyname(host)
    remote_ip = arguments[1]
except socket.gaierror:
    # could not resolve
    print('...hostname could not be resolved...exiting...')
    sys.exit()

print('...IP address of ' + host + ' is ' + remote_ip)

# connect to remote server
s.connect((remote_ip, port))

print('...socket connected to ' + host + ' on IP ' + remote_ip)


while True:
    #wait for input from keyboard
    message = input("Enter a message to send: ")
    #annoying backlash
    #message = message + "\r\n\r\n"
    
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
    
    
    # now receive data
    reply = s.recv(buffer_size).decode()

    print(reply)
    time.sleep(1)


# close the socket
s.close()
