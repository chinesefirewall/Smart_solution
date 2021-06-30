import socket
import sys

from _thread import *

HOST = ''
PORT = 8888
numconn = 10
buffer_size = 4096
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print("socket created")

try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print(f"Bind failed (error code): {msg.arg[0]}, error message: {msg.arg[1]}")
