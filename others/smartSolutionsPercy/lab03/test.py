import time
import board
import busio
import adafruit_character_lcd.character_lcd_i2c as character_lcd

i2c = busio.I2C(board.SCL, board.SDA)
lcd = character_lcd.Character_LCD_I2C(i2c, 16, 2)

scroll_message = "hello"
lcd.message = scroll_message
time.sleep(2)
for i in range(len(scroll_message)):
    lcd.move_left()
    time.sleep(0.5)