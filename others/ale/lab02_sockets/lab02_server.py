#!/usr/bin/python
import socket
import sys
import argparse
from _thread import *



HOST = ''


# number of connections
numconn = 10
buffer_size = 4096


# Handling message from command line arguments
# with argparse lib
parser = argparse.ArgumentParser(description="Creating socket server with port")
parser.add_argument("-p", "--port", help="Port lol", type=int)
args = parser.parse_args()
PORT = args.port

# Creating socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
except socket.error as msg:
    print(f"[ERROR] Bind failed (error code): {msg.args[0]}, error message: {msg.args[1]}")
    sys.exit()

print("[SUCCESS] Socket created!")


# Binding socket to local host and port

try:
    s.bind((HOST, PORT))

except socket.error as msg:
    print(f"[ERROR] Bind failed! Error code: {msg.args[0]}, error message: {msg.args[1]}")
    

print("[SUCCESS] Socket bind complete!")


# make socket listen nincoming connectionjs
s.listen(numconn)
print("[INFO] Socket listening")



# Handling connections
# creating threads
welcome_msg = "\nWelcome to the server! Type smth and hit enter.\n"
def handle_connection(conn):
    conn.send(welcome_msg.encode())
    
    while True:
        try:
            # recieveing from client
            data = conn.recv(buffer_size)
            if not data:
                break
            
            reply = f"[SUCCESS] Message recieved! ({data.decode()})"
            conn.sendall(reply.encode())
            print(f"[INFO] Recieved: {data.decode()}")
            print(f"[INFO] Sent to client: {reply}")
            
            
            
        except socket.error as msg:
            print(f"[ERROR] {msg}")
            break
        
        
    conn.close()
    
    


# Talking with the client

while True:
    # waiting to accept connection
    conn, addr = s.accept()
    
    # Display client info
    print(f"[INFO] New connection with {addr[0]}:{addr[1]}")
    
    # Start new thread
    # 1 argument - function to run
    # 2 argument - tuple of arguments to this function
    start_new_thread(handle_connection, (conn,))
    
    
    
    
    
    






 