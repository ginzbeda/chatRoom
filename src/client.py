from socket import *
SERVER_NAME = 'localhost'
SERVER_PORT = 9000
import sys
import threading

def connect():
	sock = socket(AF_INET, SOCK_STREAM)
	sock.connect((SERVER_NAME, SERVER_PORT))
	
	return sock

# @param {*} sock - the socket on which the server and client are communicating
# @param {*} message - the message that is being communicated
def send(sock, message): #send message through the socket sock
	sock.send(bytearray(message, 'utf-8'))


# @param {*} sock - the socket on which the server and client are communicating
def recv(sock): #recieves messages on the socket sock
		return sock.recv(1024).decode('utf-8')


# @param {*} sock - the socket on which the server and client are communicating
def recvT(sock): #recieves a stripped message on the socket sock
		while 1:
			print(recv(sock).strip())


def ask(prompt=':-p'): #returns an input from stdin
    return input()


def client(): # connects to a server, sends and recieves messages from the server
	connection = connect()
	t = threading.Thread(target = recvT, args=(connection, ))
	t.start()
	if len(sys.argv)>1:
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
		message = ask()
		while message != "/QUIT":
			send(connection, message)
			message = ask()


client()