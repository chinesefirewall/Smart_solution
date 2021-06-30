import time
from rpi_ws281x import *

def colorWipe(strip, color, wait_ms=50):
    """Wipe color across display a pixel at a time."""
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()
        time.sleep(wait_ms/1000.0)


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

def map_to_range(x, range_from, range_to):
    in_low, in_max = range_from
    out_low, out_max = range_to
    return (x - in_low) * (out_max - out_low) / (in_max - in_low) + out_low

def led_color_on(strip, color, wait_ms=20, iterations=1):
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()
        time.sleep(wait_ms/1000.0)
        
        
def limit_to_range(x, range_to):
    low, high = min(range_to), max(range_to)
    if x > high:
        return high
    elif x < low:
        return low
    else:
        return x
        
red = 0
green = 0
blue = 0

temp_range = (20, 35)
color_range = (0, 255)

try:
    while True:
        
        tempc = limit_to_range(float(input(">> ")), temp_range)
        red = int(map_to_range(tempc, temp_range, color_range))
        blue = int(map_to_range(tempc, temp_range, color_range[::-1]))
        print(f"Temp: {tempc} | (r, g, b): ({red}, {green}, {blue})")
        led_color_on(strip, Color(red, green, blue))
        
        
        
        
        
        
        
        
        
        
        

except KeyboardInterrupt:
    pass

colorWipe(strip, Color(0,0,0), 10)

        
