import socket
import sys



ip=socket.gethostname()	# get ip address of the machine.
port=12345	# server port.
s=socket.socket()


try:
    s.connect((ip,port)) # connecting to the server.
    messages={}
    while True:
       filename = input("enter file name :")
       s.send(filename.encode()) # encodes string and sends message to the server.
       message_receive=s.recv(1024).decode() #receive reseponse of size 1024 bytes.
       tot_message=0
       if message_receive is not None:
          print(message_receive);
          option1= input("send again (Y/N) :")
       if option1 is 'n':
          break
                     
except:
    e = sys.exc_info()
    s.close()
    print(e)
s.close()
