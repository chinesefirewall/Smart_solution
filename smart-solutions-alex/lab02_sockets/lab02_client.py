#!/usr/bin/python
import socket
import sys
import argparse


# Server info
numconn = 10
buffer_size = 4096


# Handling message from command line arguments
# with argparse lib
parser = argparse.ArgumentParser(description="Sending message to random server")
parser.add_argument("-hst", "--host", help="Host to which to connect")
parser.add_argument("-p", "--port", help="Port lol", type=int)
#parser.add_argument("-m", "--msg", help="Message you want to send")

args = parser.parse_args()
HOST = args.host
PORT = args.port
#message = args.msg
# Not sure how to do it in more beautiful way
# This is annoying
#message += "\r\n\r\n"


 # Creating socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
except socket.error as msg:
    print(f"[ERROR] Bind failed (error code): {msg.args[0]}, error message: {msg.args[1]}")
    sys.exit()
    


print("[SUCCESS] Socket created!")


# Connecting to server
try:
    remote_ip = socket.gethostbyname(HOST)
    
except socket.gaierror:
    print("[ERROR] Can't resolve hostname")
    sys.exit()
    
    

s.connect((remote_ip, PORT))

print(f"[SUCCESS] Connected to {HOST} on IP: {remote_ip}")

while True:
    try:
        
        # Replies from server
        reply = s.recv(buffer_size).decode()
        print(f"[INFO] Server replied with: {reply}")
     

        
        # Sending message
        message = input("-->: ")
        try:
            s.sendall(message.encode())
        except socket.error:
            print("[ERROR] Sending failed")
        

        
        print(f"[SUCCESS] Send message: {message} ")
    

    #reply = s.recv(buffer_size).decode("utf-8")
    
    except KeyboardInterrupt:
        break
    
    
print("[INFO] Closing the socket")
s.close()


