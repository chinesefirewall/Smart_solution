# from datetime import datetime

# now = datetime.now().time() # time object

# print("now =", now)
# print("type(now) =", type(now))	


import time
while True:

    t = time.localtime()
    current_time = time.strftime("%H:%M:%S", t)
    print(current_time)
    # print("type(current_time) =", type(current_time))
    hour = int(current_time[:2])
    minutes = int(current_time[3:5])
    seconds = int(current_time[6:])
    # print('time--> ', hour, ", ", minutes, " , ", seconds)
    print(type(minutes))

    if hour == 11 and minutes == 18 and seconds ==20:
        print('welcome to the time zone')
        break


