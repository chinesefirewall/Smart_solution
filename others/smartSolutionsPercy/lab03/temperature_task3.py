#!/usr/bin/python3

import serial
import time
import sys
import neopixel
import board


# Data for correction matrix
matrix = [
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255]


#led
led= neopixel.NeoPixel(board.D18,1)

# Fumction to map value from low to high or inverse
def maping_values(x,input_min,input_max,output_min,output_max):
    return (x-input_min)*(output_max-output_min)//(input_max-input_min)+output_min


if __name__ == '__main__':  
    try:
        #open port /dev/ttyUSB0 at 9600 bps
        ser=serial.Serial('/dev/serial0', 9600, timeout=1)
        ser.flush()
        
        #Let's print port name
        print(ser.name)
        
        number_of_temp = 0
        temperatures = []
        
        # Recording 20 measurements
        while number_of_temp < 50:
            print("sending: ", "begin")
            ser.write("begin\n".encode('ascii'))
            
            if ser.inWaiting() > 0:
                print("inwaiting mode")
                read_serial=ser.read(ser.inWaiting()).decode('ascii').rstrip()
                print("Message received: ", read_serial)
                temperatures.append(read_serial)
                
                #Displaying the led brightness
                if read_serial!= "-127":
                    intens = maping_values(int(read_serial),18,35,0,255)
                    # green red blue color
                    led[0] = (matrix[intens],0,matrix[255-intens])
            
                number_of_temp += 1
            
            time.sleep(1)
            
            # write temperatues to the file
            file = open("data.txt", "w+")
            for temp in temperatures:
                file.write("%s\n"%temp)
                
            file.close()

    except KeyboardInterrupt:
        ser.close()
        print("Existing program successfully...")
        sys.exit()

