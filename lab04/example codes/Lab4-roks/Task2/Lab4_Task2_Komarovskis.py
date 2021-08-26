import serial


ser = serial.Serial("/dev/serial0", baudrate=9600, timeout=1)
while True:
    msg = ser.read(10).decode()
    if len(msg) != 0:
        
        if msg == "on":
            
                # Turn on LED
        #if msg == "off":
            
                # Turn off LED

    #else:
     #   print('else statment')
'''

import serial
uart_channel = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=2)
data1=""
data=""
while 1:
    data = uart_channel.read(1)
    data1 += str(data)jj
    print(data1)

    uart_channel.flush()
    data=""
    data1=""
'''