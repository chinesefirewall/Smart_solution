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

# GPIO related imports
import RPi.GPIO as GPIO    
import time
import random


# LED opposite phase thread
#
# global variables for LED BLINKING
freq = 0.5
is_blinking_led = False
def subprogram_thread_leds():
    global freq, is_blinking_led
    
    while True:
        try:
            GPIO.setmode(GPIO.BOARD)
            #mode = GPIO.getmode()
            pin_out1 = 38
            pin_out2 = 40
            GPIO.setwarnings(False)
            GPIO.setup(pin_out1, GPIO.OUT, initial=GPIO.HIGH)
            GPIO.setup(pin_out2, GPIO.OUT, initial=GPIO.LOW)
            while is_blinking_led:

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





# global variables for 7seg display (numbers)
is_blinking_dis = False
current = 0
state = 0

def show_num(pins, delay):
    GPIO.output(pins, GPIO.LOW)
    time.sleep(delay)
    GPIO.output(pins, GPIO.HIGH)

# 7SEG display thread
# 7seg display done in a right way
# using true false matrix
def subprogram_thread_display():
    global is_blinking_dis, current, state
    
    while True:
        try:
            GPIO.setmode(GPIO.BOARD)
            GPIO.setwarnings(False)
            
            pins = [31, 16, 18, 36, 37, 33, 32, 22]
            nums = [[1, 1, 0, 0, 0, 0, 0, 0],
                    [1, 1, 1, 1, 1, 0, 0, 1],
                    [1, 0, 1, 0, 0, 1, 0, 0],
                    [1, 0, 1, 1, 0, 0, 0, 0],
                    [1, 0, 0, 1, 1, 0, 0, 1],
                    [1, 0, 0, 1, 0, 0, 1, 0],
                    [1, 0, 0, 0, 0, 0, 1, 0],
                    [1, 1, 1, 1, 1, 0, 0, 0],
                    [1, 0, 0, 0, 0, 0, 0, 0],
                    [1, 0, 0, 1, 0, 0, 0, 0]]
            
            GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)
            
            while is_blinking_dis:
                #print("[DEBUG] EBASHIM")
                if state == 0:
                    current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
                    show_num(current_leds, 1)
                    current = (current+1)%len(nums)
                
                elif state == 1:
                    current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
                    current = (current-1)%len(nums)
                    show_num(current_leds, 1)
                    
                    
                elif state == 2:
                    current_leds = [pins[i] for i in range(len(pins)) if nums[current][i] == 0]
                    current = random.randint(0, 9)
                    show_num(current_leds, 1)
                
                elif state > 2:
                    state = 0
              
                
        except socket.error as msg:
            print(f"[ERROR] {msg}")
            break





# Handling connections creating threads
# sorry
welcome_msg = "[INFO] Welcome to the server!\n LED commands:\n  start_led, stop_led, led <float>\n DISPLAY commands:\n  start_dis, stop_dis, dis <int>.\n"
def handle_connection(conn):
    global is_blinking_led, freq, state, is_blinking_dis
    
    conn.send(welcome_msg.encode())
    
    
    while True:
        try:
            #print(f"[DEBUG] {is_blinking}")
            # recieveing from client
            data = conn.recv(buffer_size)
            if not data:
                break
            
            msg_recieved = data.decode()
            
            
            if msg_recieved.lower() == "start_led":
                if is_blinking_led == False:
            
                    is_blinking_led = True
                    reply = f"[SUCCESS] LED Blinking started.."
                
                else:
                    reply = f"[WARNING] LED Blinking already started"
                       
       
            
            elif msg_recieved.lower() == "stop_led":
                if is_blinking_led == True:
                    is_blinking_led = False
                    
                    # GPIO.setup([pin_out1, pin_out2],  GPIO.OUT, initial=GPIO.LOW)
                    reply = f"[SUCCESS] LED Blinking stoped"
            
                else:
                    reply = f"[WARNING] LED Blinking already stopped"
                    
            
            elif msg_recieved.lower() == "start_dis":
                if is_blinking_dis == False:
            
                    is_blinking_dis = True
                    reply = f"[SUCCESS] DISPLAY numbers started.."
                
                else:
                    reply = f"[WARNING] DISPLAY numbers started already started"
                    
                    
            elif msg_recieved.lower() == "stop_dis":
                if is_blinking_dis == True:
                    is_blinking_dis = False
                    
                    # GPIO.setup([pin_out1, pin_out2],  GPIO.OUT, initial=GPIO.LOW)
                    reply = f"[SUCCESS] DISPLAY numbers stoped"
            
                else:
                    reply = f"[WARNING] DISPLAY numbers already stopped"  
            
            elif msg_recieved.lower().startswith("led"):
                try:
                    freq = float(msg_recieved.split()[1])
                except:
                    reply = f"[WARNING] {msg_recieved.split()[1]} must be float!"
                    
            elif msg_recieved.lower().startswith("dis"):
                try:
                    state = int(msg_recieved.split()[1])
                except:
                    reply = f"[WARNING] {msg_recieved.split()[1]} must be int!"
                    
            
            else:
                reply = f"[WARNING] Not allowed command"
            

            #reply = f"OK Message recieved! ({msg_recieved})"
            print(f"[DEBUG] {msg_recieved}")
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
    start_new_thread(subprogram_thread_leds, ())
    start_new_thread(subprogram_thread_display, ())
    
    
    # Display client info
    print(f"[INFO] New connection with {addr[0]}:{addr[1]}")
    
    
    
    # Start new thread
    # 1 argument - function to run
    # 2 argument - tuple of arguments to this function
    start_new_thread(handle_connection, (conn,))
    
    
    
    
    
    






 



