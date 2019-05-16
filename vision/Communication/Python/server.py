import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(0)
while True:
    client_socket, addr = server_socket.accept()
    data = client_socket.recv(65535)
    received_string = data.decode("utf-8")
    ll = received_string.split()
    x = ll[0]
    y = ll[1]
    d = ll[2]
    print("x: {} y: {}, d:{}".format(x, y, d))

