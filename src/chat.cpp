#include "chat.h"
#include "connection.h"

vector<chatroom> Chat::chatrms;


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
	user nuser;
	strncpy(nuser.nickname,name,sizeof(nuser.nickname));
	nuser.connfd = connfd;
	nuser.chatting = true;
	for(int i=0; i<Chat::chatrms.size(); i++){
		if(strncmp(Chat::chatrms[i].name,room, sizeof(Chat::chatrms[i].name)) == 0) // comparing char *
		{
			Chat::chatrms[i].usrs.push_back(nuser);
		}
		return 1;
	}
	chatroom new_room;
	strncpy(new_room.name,room,sizeof(new_room.name));
	new_room.usrs.push_back(nuser);
	Chat::chatrms.push_back(new_room);
	return 1;
}
int rooms(int connfd){
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			send_message(connfd, Chat::chatrms[i].name);
		}
		return 1;
	}
	else{
		cout<< "it works" << endl;
	}
	return -1;
}
int leave(int connfd);

int who(int connfd){
 return 0;
}


int help(int connfd){
	char buff[] = "The following commands are available :-\n \\JOIN\n \\ROOMS\n \\WHO\n \\LEAVE\n \\nickname message\n";
	send_message(connfd,(char *)buff);
	return 1;
}


int mess(char name[25], char msg[MAXLINE], int connfd)
{
	for(int i=0; i<Chat::chatrms.size(); i++)
	{
		for(int j=0; j<Chat::chatrms[i].usrs.size(); j++)
		{
			if(strncmp((char *)name,Chat::chatrms[i].usrs[j].nickname,16) == 0)
			{
				send_message(Chat::chatrms[i].usrs[j].connfd,(char *)msg);
				send_message(connfd,(char *)msg);
				return 1;
			}
		}
	}
	return -1;
}



