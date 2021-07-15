import socket
import sys
from _thread import *

HOST = input("Enter the host address: ")
PORT = int(input("Enter port number: "))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("...socket created...")
try:

    s.bind((HOST, PORT))
except socket.error as msg:
    print("...bind failed...error code: " + str(msg.arg[0]) + "error message: " +
          msg.arg[1])
    sys.exit()
print("...socket bind complete...")

# makes socket listen to connections
s.listen(5)
print("...socket now listening...")


# function for handling connections... this will be use to create threads
def myclientthread(com):
    # send message to connected client
    com.send("...welcome to the server...enter a request and hit enter \n".
             encode())  # send only takes bytes

    while True:
        try:
            # receiving data from client
            info = com.recv(4096)
            if not info:
                break
            respond = "...OK..." + info.decode()  # decodes bytes to string
            com.sendall(respond.encode())
            print("received")
            print(info.decode())
            print("sent")
            print(respond)
        except socket.error as message:  # error, for example if the connection is closed
            print(message)
            break
    com.close()


while True:
    com, addr = s.accept()
    # display client information
    print("...connected with", addr[0], ":", str(addr[1]))

    # start new thread takes 1st argument as function and name to be run, second is the tuple of the arguments to the function.
    start_new_thread(myclientthread, (com,))
s.close()
