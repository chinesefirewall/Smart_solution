import time
import serial
import sys



from rpi_ws281x import *

# LED strip configuration:
LED_COUNT      = 1     # Number of LED pixels.
#LED_PIN        = 18      # GPIO pin connected to the pixels (18 uses PWM!).
LED_PIN        = 12      # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53


# Create NeoPixel object with appropriate configuration.
strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
# Intialize the library (must be called once before other functions).
strip.begin()



# Function lights a specific color: <Color(r, g, b)> passed to it 

def led_color_on(strip, color, wait_ms=20, iterations=1):
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()
        time.sleep(wait_ms/1000.0)


# maps value from range to another range
# Function math tactically stolen from arduino built-in map()
def map_to_range(x, range_from, range_to):
    in_low, in_max = range_from
    out_low, out_max = range_to
    return int((x - in_low) * (out_max - out_low) / (in_max - in_low) + out_low)


def limit_to_range(x, range_to):
    low, high = min(range_to), max(range_to)
    if x > high:
        return high
    elif x < low:
        return low
    else:
        return x




# File to store temps
filename = "temps.txt"


# to store temperatures
temps = list()

# Ranges
temp_range = (20, 35)
color_range = (0, 255)

red = 0
green = 0
blue = 0




# Other ports
# /dev/ttyUSB0
# /dev/ttyS0
# /dev/ttyAMA0


try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1) 
    ser.flush()
    while True:        

        if ser.in_waiting > 0:
            tempc = round(float(ser.readline().decode('utf-8').rstrip()), 2)
            tempc = limit_to_range(tempc, temp_range)
            print('temperature in celcius---->', tempc)
            
            temps.append(tempc)
            
            # Temps range here is 20..35 cause it vey hot in Delta (orig 18..35)
            red = map_to_range(tempc, temp_range, color_range)
            blue = map_to_range(tempc, temp_range, color_range[::-1])
            led_color_on(strip, Color(red, green, blue))
            print(f"Red: {red}, blue: {blue}, temp: {tempc}")
            
            


except KeyboardInterrupt:
    print("Programm stopped")
    # close serial
    ser.close()
    led_color_on(strip, Color(0,0,0), 10)
    
    
    print(f"Writing temps to file: {filename}")
    # Write temps to file
    with open(filename, 'w') as file:
        for t in temps:
            file.write('{}\n'.format(str(t)))    
    print("DONE")
    
    print("Plotting temperature graph...")
    import matplotlib.pyplot as plt
    plt.figure()
    plt.plot(temps)
    plt.show()
    
    



except:
    print(f"[ERROR] {sys.exc_info()[0]}")
    raise



    
    