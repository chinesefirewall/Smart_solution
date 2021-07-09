#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full socket client example in python
# file: juhendid-sockets-nutipraks-2020-code-client-http.py
# adapted by: Jyri J6ul

import socket  # for sockets
import sys  # for exit

# initialise constants
remote_ip = input('ip address: ')
port = int(input('Port number: '))
buffer_size = 4096

try:
    # create an AF_INET, STREAM socket (TCP)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print('...failed to create socket...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket created...')

# connect to remote server
s.connect((remote_ip, port))
print('...socket connected to ' + str(port))
while True:
    try:

        mail = s.recv(buffer_size).decode()
        print(mail) 
        
        if mail == 'Flashing on/off: ':
        
            flashing = input(' ')    
            freq = input('Freq (Hz): ')
            
            lst_msg="Flashing "+flashing +" freq "+freq+ " Hz."
          
            s.sendall(lst_msg.encode())

            print('...message sent successfully...')
            reply = s.recv(buffer_size).decode()
            print(reply)   
        if mail == 'Enter command(start,reverse,random or restore): ':
        
            command = input(' ') 
            s.sendall(command.encode())
            # now receive data
            reply = s.recv(buffer_size).decode()
            print(reply)
    
    except KeyboardInterrupt:
        print('Exiting')
        sys.exit()


# close the socket
s.close()
