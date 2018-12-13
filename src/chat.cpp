#include "chat.h"
#include "connection.h"


//must change user to chatting if return 1
user createUsr(char name[16],  sockaddr_in *server_addr, int connfd){
	user born;
	strncpy(born.nickname, name, strlen(name));
	born.server_addr = server_addr;
	born.chatting = false;
	return born;
}

int chattr(user *change, int connfd){
	change->chatting = true;
	return 1;
}

int join(char *name, char *room, int connfd){
	for(int i=0; i<Chat::chatrms.size(); i++){
		if(strncmp(chatrms[i].name,room, sizeof(chatrms[i].name)) == 0) // comparing char *
		{
			user nuser;
			nuser.nickname = name
			nuser.chatting = true;
			chatrms[i].usrs.push_back(nuser);
		}
	}
	return 1;
}
int rooms(int connfd){
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			send_message(connfd, Chat::chatrms[i]);
		}
		return 1;
	}
	return -1;
}
int leave(int connfd)
{

}
int who(int connfd);
int help(int connfd);
int mess(char name[25], char msg[MAXLINE], int connfd);