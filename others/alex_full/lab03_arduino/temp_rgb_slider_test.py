import cv2
import numpy as np


# maps value from range to another range
# Function math stolen from arduino built-in map()
def map_to_range(x, in_low, in_max, out_low, out_max):
    return (x - in_low) * (out_max - out_low) / (in_max - in_low) + out_low




img = np.zeros((300, 512, 3), dtype=np.uint8)
windowName = 'RGB temp'
cv2.namedWindow(windowName)

# Trackbars
cv2.createTrackbar('temp', windowName, 1800, 3500, (lambda a: None))
#cv2.createTrackbar('R', windowName, 0, 255, (lambda a: None))
#cv2.createTrackbar('G', windowName, 0, 255, (lambda a: None))
#cv2.createTrackbar('B', windowName, 0, 255, (lambda a: None))
g = 0
b = 0

while True:
    #r = cv2.getTrackbarPos('R', windowName)
    #g = cv2.getTrackbarPos('G', windowName)
    #b = cv2.getTrackbarPos('B', windowName)
    temp = cv2.getTrackbarPos('temp', windowName)/100
    r = map_to_range(temp, 18, 35, 0, 255)
    b = map_to_range(temp, 18, 35, 255, 0)

    img[:] = [b, g, r] 

    cv2.imshow(windowName, img)
    print(f"RED: {round(r/255, 2)}, GREEN: {round(g/255, 2)}, BLUE: {round(b/255, 2)}")

    if cv2.waitKey(1) == 27:
        break


cv2.destroyAllWindows()