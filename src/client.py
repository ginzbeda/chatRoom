from socket import *
SERVER_NAME = 'localhost'
SERVER_PORT = 9000
import sys
import threading

def connect():
	sock = socket(AF_INET, SOCK_STREAM)
	sock.connect((SERVER_NAME, SERVER_PORT))
	
	return sock

def send(sock, message):
	sock.send(bytearray(message, 'utf-8'))


def recv(sock):
		return sock.recv(1024).decode('utf-8')

def recvT(sock):
		while 1:
			print(recv(sock).strip())

def ask(prompt=':-p'):
    return input()

def client():
	connection = connect()
	t = threading.Thread(target = recvT, args=(connection, ))
	t.start()
	if len(sys.argv)>1:
		# if there is a file
		with open(sys.argv[1]) as f:
			content = f.readlines()
		content = [x.strip() for x in content] 
		size = len(content)
		count = 0
		print(content)
		while  count < size:
			send(connection, content[count])
			count+=1

	else:
		# else take input
		message = ask()
		while message != "/QUIT":
			send(connection, message)
			message = ask()


client()