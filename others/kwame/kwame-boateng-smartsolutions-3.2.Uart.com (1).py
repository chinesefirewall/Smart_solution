import serial,time,sys
try:
# open port /dev/ttyUSB0 at 9600 bps
    ser=serial.Serial("/dev/ttyS0",9600)
# print port name
    print(ser.name)
    fl = input("What's up? ")
    while True:
        
        ser.write(fl.encode("utf-8"))
# read the buffer with newlines
        read_serial=ser.readline()
# cut the newline and display
    
        print(read_serial.decode().rstrip('\n'))
        
# a small break
        time.sleep(2)
except KeyboardInterrupt:
    ser.close()
    print("exit command received...")
    sys.exit()