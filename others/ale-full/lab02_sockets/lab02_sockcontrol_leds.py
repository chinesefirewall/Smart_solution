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


# LED code
import RPi.GPIO as GPIO    
import time

# Default frequency for blinking (1Hz)
freq = 0.5
is_blinking = False


def subprogram_thread():
    global freq, is_blinking
    
    while True:
        try:
            GPIO.setmode(GPIO.BOARD)
            #mode = GPIO.getmode()
            pin_out1 = 38
            pin_out2 = 40
            GPIO.setwarnings(False)
            GPIO.setup(pin_out1, GPIO.OUT, initial=GPIO.HIGH)
            GPIO.setup(pin_out2, GPIO.OUT, initial=GPIO.LOW)
            while is_blinking:

                GPIO.output(pin_out1, GPIO.LOW)
                GPIO.output(pin_out2, GPIO.HIGH)
                time.sleep(freq)

                GPIO.output(pin_out1, GPIO.HIGH)
                GPIO.output(pin_out2, GPIO.LOW)
                time.sleep(freq)
                
            
            GPIO.cleanup((pin_out1, pin_out2))
                
        except socket.error as msg:
            print(f"[ERROR] {msg}")
            break





# Handling connections
# creating threads
welcome_msg = "[INFO] Welcome to the server! Type smth and hit enter.\n"
def handle_connection(conn):
    global is_blinking, freq
    
    conn.send(welcome_msg.encode())
    
    
    while True:
        try:
            print(f"[DEBUG] {is_blinking}")
            # recieveing from client
            data = conn.recv(buffer_size)
            if not data:
                break
            
            msg_recieved = data.decode()
            
            
            if msg_recieved.lower() == "start":
                if is_blinking == False:
            
                    is_blinking = True
                    reply = f"[SUCCESS] Blinking started.."
                
                else:
                    reply = f"[WARNING] Blinking already started"
                       
       
            
            elif msg_recieved.lower() == "stop":
                if is_blinking == True:
                    is_blinking = False
                    
                    # GPIO.setup([pin_out1, pin_out2],  GPIO.OUT, initial=GPIO.LOW)
                    reply = f"[SUCCESS] Blinking stoped"
            
                else:
                    reply = f"[WARNING] Blinking already stopped"
                    
            
            
            else:
                try:
                    freq = float(msg_recieved)
                except:
                    reply = f"[WARNING] Only 'start', 'stop' and ints for freq are allowed"
            

            #reply = f"OK Message recieved! ({msg_recieved})"
            conn.sendall(reply.encode())
            print(f"[INFO] Recieved: {msg_recieved}")
            print(f"[INFO] Sent to client: {reply}")
            
            
            
            
        except socket.error as msg:
            print(f"[ERROR] {msg}")
            break
        
        
    conn.close()
    
    


# Talking with the client

while True:
    # waiting to accept connection
    conn, addr = s.accept()
    
    
    # Creating thread for subprogram
    start_new_thread(subprogram_thread, ())
    
    
    # Display client info
    print(f"[INFO] New connection with {addr[0]}:{addr[1]}")
    
    
    
    # Start new thread
    # 1 argument - function to run
    # 2 argument - tuple of arguments to this function
    start_new_thread(handle_connection, (conn,))
    
    
    
    
    
    






 


