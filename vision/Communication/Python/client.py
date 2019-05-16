import socket
from time import sleep

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


while True:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 12345))
    x = 5
    y = 9
    d = 15 #데이터 넣기
    data_str = "{} {} {}".format(x, y, d)
    byte_data = str.encode(data_str)
    sock.send(byte_data)
    sleep(0.1)
