import serial,time,sys

try:
    ser=serial.Serial('/dev/ttyUSB1', 115200)
    print(ser.name)

    while True:
        read_serial=ser.readline().decode('utf-8').rstrip()
        
        print(read_serial)

        time.sleep(1)
        
except KeyboardInterrupt:
    ser.close()
    print("Lopetan")
    sys.exit()
