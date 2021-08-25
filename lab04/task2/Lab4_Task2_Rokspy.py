import serial


ser = serial.Serial("/dev/serial0", baudrate=9600, timeout=2)
while True:
    msg = ser.read(10).decode()
    if len(msg) != 0:
        
        if msg == "on":
            
                # Turn on LED
        elif msg == "off":
            
                # Turn off LED

