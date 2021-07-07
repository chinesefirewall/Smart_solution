#https://projectiot123.com/2019/01/27/home-automation-using-raspberry-pi-via-bluetooth/

import serial
from RPLCD import i2c
import time
import bluetooth
import RPi.GPIO as GPIO   

server_socket=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
port = 1
server_socket.bind(("",port))
server_socket.listen(1)
client_socket,address = server_socket.accept()
print("Accepted connection from ",address)
while 1:
    data = client_socket.recv(1024)
    data = data.decode()
    print("Received: %s" % data)
    if (data == "q"):
        print ("Quit")
        break
        client_socket.close()
        server_socket.close()