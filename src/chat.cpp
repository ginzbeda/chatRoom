#include "chat.h"

//must change user to chatting if return 1
user createUsr(char name[16], 	struct sockaddr_in *server_addr;){
	user born;
	strncpy(born.nickname, name, sizeof(name));
	born.sockAdr = sockAdr;
	born.chatting = false;
	return born;
}

int chattr(user *change){
	change->chatting = true;
	return 1;
}

int join(char name[25], char room[25]){
	for(int i=0; i<sizeof(chatrms); i++){
		if(strcmp(chatrms[i].name, room)==0){
			
		}
	}
}
int rooms();
int leave();
int who();
int help();
int mess(char name[25], char msg[MAXLINE]);