import torch
import socket
import platform

ip_address = socket.gethostbyname(socket.gethostname())

if torch.cuda.is_available():
    print("cuda is available")
else:
    print("cuda is not available")

    print(ip_address)
    print(platform.uname(), "\n")