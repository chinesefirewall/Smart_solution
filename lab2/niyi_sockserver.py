import socket
import sys
from _thread import *  # low level threading library


# Creates thread for per connection from clients
def clientthread(conn):
    buffer_size = 4096
    # sending message to connected client
    conn.send('...welcome to the server...type something fun and hit enter \n ----->'.encode())  # send only takes bytes
    while True:
        try:
            # receiving from client
            data = conn.recv(buffer_size)  # receives bytes
            if not data:
                break
            
            msg_client = data.decode()        
            print("received message: "+ data.decode())
                
            print(msg_client)
            reply = " Sending back " + msg_client
            conn.sendall(reply.encode())
            
        except socket.error as message:  
            print(message)
            break
    conn.close()



host = '127.0.0.8'  
port = int(input("Enter port: "))
numconn = 10  

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('...socket created...')

# bind socket to local host and port
try:
    s.bind((host, port))
except socket.error as msg:
    print('...bind failed...error code: ' + str(msg.arg[0]) + ', error message: ' + msg.arg[1])
    sys.exit()

print('...socket bind complete...')

# listens to  incoming connections
s.listen(numconn)
print('...socket now listening...')


while True:
    # wait to accept a connection 
    conn, addr = s.accept()

    # display client information
    print('...connected with ' + addr[0] + ':' + str(addr[1]))

    start_new_thread(clientthread, (conn,)) # Starts new thread to handle all connections
s.close()
