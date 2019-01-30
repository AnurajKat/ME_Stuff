import socket
import sys
import os
import math


s=socket.socket()
host= socket.gethostname()
# port
port=12345
	
# bind port to the socket
s.bind((host,port))	
print("Socket Opened.")
s.listen(5)
while True:
    c,addr=s.accept()	# accept a connection when requested.
    print("Connection request received from ",addr)
    
    df = "~/anuraj/"	
    while True:
        recvFN = c.recv(1024).decode()	# receive requests
        print("request received")
        df=recvFN;
        if os.path.exists(df):	# check if file exists.
            with open(df, 'rb') as f:
                packet = f.read(1024)
                c.send(packet) # send contents of the file in chunks of 1024 bytes.
            print("file content sent")
        else :
            message="file not found."
            try:
                c.send(message.encode())
                print(message)
            except:
                print("Connection closed or dropped")
                break

s.close()
