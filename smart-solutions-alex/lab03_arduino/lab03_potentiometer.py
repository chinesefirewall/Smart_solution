import time
import serial
import sys


# Other ports
# /dev/ttyUSB0
# /dev/ttyS0
# /dev/ttyAMA0 - classroom / home



try:
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1) 
    ser.flush()
    while True:        

        if ser.in_waiting > 0:
            reply = ser.readline().decode('utf-8').rstrip()
            print("Voltage: ", reply)


except KeyboardInterrupt:
    print("Programm stopped")
    ser.close()
    print("Serial closed")


except:
    print(f"[ERROR] {sys.exc_info()[0]}")
    raise
