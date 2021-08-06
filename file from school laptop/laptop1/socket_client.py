#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full socket client example in python
# file: juhendid-sockets-nutipraks-2020-code-client-http.py
# adapted by: Jyri J6ul
#umbes 95% koodist on sama mis lehel uleval oli EHK POLE MINU OMA, muutsin vaid moningaid ridu pls no plagiaadisuudistus -Uku

import socket  # for sockets
import sys  # for exit

host = sys.argv[1]
portnr = int(sys.argv[2])

# initialise constants
#host = 'www.ut.ee'
port = portnr
#message = "GET / HTTP/1.0\r\n\r\n"
buffer_size = 4096

try:
    # create an AF_INET, STREAM socket (TCP)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
except socket.error as msg:
    print('...failed to create socket...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket created...')

try:
    remote_ip = socket.gethostbyname(host)
except socket.gaierror:
    # could not resolve
    print('...hostname could not be resolved...exiting...')
    sys.exit()

print('...IP address of ' + host + ' is ' + remote_ip)

# connect to remote server
s.connect((remote_ip, port))

print('...socket connected to ' + host + ' on IP ' + remote_ip)

# send some data to remote server
for i in range(3):
	try:
		# send string encoded as bytes
		message = input('Watchu wanna send bro: ')
		s.sendall(message.encode())
    
	except socket.error:
		# send failed
		print('...send failed...')
		sys.exit()
	
	print('Message sent: '+ message)

	# now receive data
	reply = s.recv(buffer_size).decode()

	print('Reply recieved: '+reply)


# close the socket
s.close()

