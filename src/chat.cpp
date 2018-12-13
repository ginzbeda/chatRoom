#include "chat.h"



//must change user to chatting if return 1
user createUsr(char name[16],  sockaddr_in *server_addr){
	user born;
	strncpy(born.nickname, name, strlen(name));
	born.server_addr = server_addr;
	born.chatting = false;
	return born;
}

int chattr(user *change){
	change->chatting = true;
	return 1;
}

int join(char *name, char *room){
	for(int i=0; i<Chat::chatrms.size(); i++){
		if(chatrms[i].name == room) // comparing char *
		{
			user nuser;
			nuser.nickname = name
			nuser.chatting = true;
			chatrms[i].usrs.push_back(nuser);
		}
	}
	return 1;
}
int rooms();
int leave();
int who();
int help();
int mess(char name[25], char msg[MAXLINE]);