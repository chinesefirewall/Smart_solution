import socket 
import sys 
import time


arguments = sys.argv

host = input("Enter IP: ") # e.g www.ut.ee
port = int(input("Enter port number: ")) #e.g 80

buffer_size = 4096

#creating the socket instance
try:
    # create an AF_INET, STREAM socket (TCP)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print('...failed to create socket...error code: ' + str(msg.args[0]) + ', error message: ' + msg.args[1])
    sys.exit()

print('...socket created...')
try:
    # connect to remote server
    s.connect((host, port))
    print('...socket connected to ' + host + ' on port ' + str(port))
except OSError:
    print("Socket could not connect to "+ host + ' on port  ' + str(port))
else:
    while True:
        # now receive data
        reply = s.recv(buffer_size).decode()

        print("Server message: " + reply)
        time.sleep(1)
        
        message = input("Client message: ")
        
        try:
            # send string encoded as bytes
            s.sendall(message.encode())
            print(message.encode())
        except socket.error:
            # send failed
            print('...send failed...')
            sys.exit()

        print('...message sent successfully...')
        
        
        


    # close the socket
    s.close()

