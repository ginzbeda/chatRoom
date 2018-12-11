from socket import *
SERVER_NAME = 'localhost'
SERVER_PORT = 9000
import sys

def connect():
	sock = socket(AF_INET, SOCK_STREAM)
	sock.connect((SERVER_NAME, SERVER_PORT))
	
	return sock

def send(sock, message):
	sock.send(bytearray(message, 'utf-8'))


def recv(sock):
		return sock.recv(1024).decode('utf-8')



def client():
	connection = connect()
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
				response = recv(connection)
				print(response.strip())
				count+=1

	else:
		# else take input
		message = input('What is your input?')
		while message != "/QUIT":
			send(connection, message)
			respose = recv(connection)
			print(response.strip())
			message = sockask(connection)


client()