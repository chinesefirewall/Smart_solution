import serial,time,sys


try:
# open port /dev/ttyUSB0 at 9600 bps
    ser=serial.Serial("/dev/ttyS0",9600)

    print(ser.name)
#     fl = input("Want to read Voltage: ")
    while True:
        
        if ser.in_waiting:
            time.sleep(0.1)
            read_serial = ser.read(ser.in_waiting)
#         
    
            print(read_serial.decode().rstrip('\n'))
        

            
except KeyboardInterrupt:
    ser.close()
    print("exit command received...")
    sys.exit()
#Use sofware serial for digital communications