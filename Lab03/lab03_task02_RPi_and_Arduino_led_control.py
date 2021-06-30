import time
import serial


# Other ports
# /dev/ttyUSB0
# /dev/ttyS0
# /dev/ttyAMA0

led_command = ("ON", "OFF")

try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1) 
    ser.flush()
    print('Serial connection successful')
    while True:        
        
        message = input(" please enter ON or OFF>> ")
        if message.upper() not in led_command:
            continue
        
        ser.write(message.encode("utf-8"))
        
        if ser.in_waiting > 0:
            reply = ser.readline().decode('utf-8').rstrip()
            print("REPLY: ", reply)


except KeyboardInterrupt:
    print('Keyboard Interruption')
    ser.close()
    print("done")
    





