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

def list(sock):
    send(sock, '-')
    result = recv(sock).rstrip()
    if result == '':
        return []
    else:
        return result.split(',')[0:-1]

def last_list(sock):
    xs = list(sock)
    if len(xs) == 0:
        return ''
    else:
        return xs[-1]

def prompt_on_last(sock):
    last = last_list(sock)
    if last == '':
        return ask()
    else:
        return ask(last)

def client():
	# socket = connect()
	if len(sys.argv)>1:
		# if there is a file
		with open(sys.argv[1]) as f:
			content = f.readlines()
			content = [x.strip() for x in content] 
			print(content)
	else:
		# else take input
		message = input('What is your input?')
		while message != "/QUIT":
			send(socket, message)
			respose = recv(socket)
			print(response.strip())
			message = prompt_on_last(socket)
	# print("This is the name of the script:" , sys.argv[0])
	# print("Number of arguments: ", len(sys.argv))
	# print("These are the arguments:", str(sys.argv))
	# message = input('What is your input?')
	# print('input: ' + message)

client()