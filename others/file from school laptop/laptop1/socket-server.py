#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/

# socket server example in python

import socket 
import sys, getopt, time
from _thread import *
from subprocess import call

HOST='' # symbolic name meaning all available interfaces
 # arbitrary non-privileged port

def usage():
	print("usage: ",sys.argv[0]," -p|--port PORT")
	return

def menu():
	try:
		opts,args = getopt.getopt(sys.argv[1:],"p:h",["port=","help"])
	except getopt.GetoptError:
		usage()
		sys.exit(2)

	if len(sys.argv)==1:
		usage()
		sys.exit(2)

	for opt,arg in opts:
		if opt in ("-h","--help"):
			usage()
			sys.exit()
		elif opt in ("-p","--port"):
			PORT=int(arg)

	return PORT

def create_socket(HOST,PORT):
	s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	print("socket created")

# bind socket to local host and port

	try:
		s.bind((HOST,PORT))
	except(socket.error, msg):
		print("...bind failed...error code: ",str(msg[0]),", error message: ",msg[1])
		sys.exit()

	print("...socket bind complete...")

	# start listening on socket

	s.listen(10)
	print("...socket now listening...")

	return s

# function for handling connections...this will be used to create threads
def clientthread(conn):
	# sending message to connected client
#	conn.send('...welcome to the server...type something and hit enter \n') # send only takes strings
	# infinite loop so that function do not terminate and thread do not end
	while True:
		# receiving from client
		data=conn.recv(1024)
		reply="...OK..." + bytes.decode(data)
		data1=bytes.decode(data)
		if not data:
			break
		print(time.asctime( time.localtime(time.time()) ),":",data1)

		conn.sendall(str.encode(reply))
		
		if data1.find('ledon')==0:
			print("turn led on")
			call(["ledonoff.py","-p 16","-s 1"])
		elif data1.find('ledoff')==0:
			print("turn led off")
			call(["ledonoff.py","-p 16","-s 0"])

	# came out of loop
	conn.close()
		
# now keep talking with the client

def main():

	PORT=menu()
	s=create_socket(HOST,PORT)

	while 1:
# wait to accept a connection - blocking call
		conn, addr = s.accept()

# display client information
		print("...connected with ",addr[0],":",str(addr[1]))

# start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function
		start_new_thread(clientthread,(conn,))

	s.close()
	
	return

if __name__=="__main__":
	main()
	

