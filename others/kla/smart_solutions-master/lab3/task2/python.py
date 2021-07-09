#!/usr/bin/python3
import serial,time,sys
try:
    # open port /dev/ttyUSB0 at 9600 bps
    ser=serial.Serial('/dev/ttyAMA0',baudrate = 9600, parity = serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, bytesize = serial.EIGHTBITS, timeout=1)
    ser.flush()
    # print port name
    print(ser.name)
    while True:
        cmd = input("write your command (ON/OFF): ")
        ser.write(cmd.encode())
        time.sleep(0.3)
        
        # read the buffer with newlines
        if ser.in_waiting > 0 :
            line = ser.readline().decode('acii').rstrip('\n')
            print(line)
            
except KeyboardInterrupt:
    ser.close()
    print("exit command received...")
    sys.exit()
