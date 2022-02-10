import time
import serial
import RPi.GPIO as GPIO    


try:
    ser = serial.Serial('COM4', 9600, timeout=1) # Establish the connection on a specific port
    ser.flush()
    while True:
        
        #message = input(">> ")

        
        #ser.write(message.encode())

        if ser.in_waiting > 0:
            reply = ser.readline().decode("utf-8").rstrip()
            print(reply)


except KeyboardInterrupt:
    ser.close()
    print("done")
    

