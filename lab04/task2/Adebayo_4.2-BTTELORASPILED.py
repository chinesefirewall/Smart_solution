import serial,time,sys
import RPi.GPIO as GPIO
comm = False
led_sw = False


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(40,GPIO.OUT)

try:
# open port /dev/ttyUSB0 at 9600 bps
    ser = serial.Serial("/dev/serial0", baudrate=9600, timeout=2)
##    ser=serial.Serial("/dev/serial0",9600)

    print(ser.name)
    while True:
        if comm == False:
            print('while loop check successful')
            fl = "Enter on/off\n  "
            
            ser.write(fl.encode("utf-8"))
            print('message sent successful')
           
            comm = True
            
        if ser.in_waiting > 0:
            print('serial waiting for comm')
            read_serial = ser.read(ser.in_waiting).decode().rstrip()
            time.sleep(0.1)
            if read_serial == "on":
                GPIO.output(40,GPIO.HIGH)
                led_sw = True
            if read_serial == "check":
                if led_sw == True:
                    ser.write("Ledon\n".encode())
                else:
                    ser.write("Ledoff\n".encode())
                
            
            if read_serial == "off":
                if led_sw == True:
                    GPIO.output(40,GPIO.LOW)
                    led_sw = False
                
                    
            print("Phone:",read_serial)
            comm = False
        time.sleep(0.1)
        

            
except KeyboardInterrupt:
    ser.close()
    print("exit command received...")
    sys.exit()
#Use sofware serial for digital communications
