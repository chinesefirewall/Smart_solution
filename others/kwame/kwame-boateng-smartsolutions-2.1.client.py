import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
HOST = input("Enter Host IP: ")
PORT = int(input("Enter port number: "))
s.connect((HOST, PORT))
while True:

    msg = s.recv(1024)
    print("Reply from server:", msg.decode('utf-8'))

    message = input("Enter your request: ")
    s.sendall(message.encode())
    print("sent:",message)
