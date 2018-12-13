#include "chat.h"
#include "connection.h"

vector<chatroom> Chat::chatrms;


//must change user to chatting if return 1
// user createUsr(char name[16],  sockaddr_in *server_addr, int connfd){
// 	user born;
// 	strncpy(born.nickname, name, strlen(name));
// 	born.server_addr = server_addr;
// 	born.chatting = false;
// 	return born;
// }


int join(char *name, char *room, int connfd){
	User nUser = new User(connfd, name);
	for(size_t i = 0; i< Chat::chatrms.length(), i++){
		if(strncmp(Chat::chatrms[i].name, room, sizeof(Chat::chatrms[i].name))==0){
			(User*) nUser
		}
	}

	user nuser;
	strncpy(nuser.nickname,name,sizeof(nuser.nickname));
	nuser.connfd = connfd;
	nuser.chatting = true;
	for(int i=0; i<Chat::chatrms.size(); i++){
		if(strncmp(Chat::chatrms[i].name,room, sizeof(Chat::chatrms[i].name)) == 0) // comparing char *
		{
			user nuser;
			nuser.nickname = name;
			nuser.chatting = true;
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
	return -1;
}
int leave(int connfd){
	for(size_t i=0; i<Chat::chatrms.size(); i++){
		for(size_t j =0; j<Chat::chatrms[i].usrs.size(); j++){
			if(Chat::chatrms[i].usrs[j].connfd == connfd){
				//MIGHT CAUSE PROBLEM
				memset(Chat::chatrms[i].usrs[j].room,NULL,sizeof(Chat::chatrms[i].usrs[j].room));
				Chat::chatrms[i].usrs[j].chatting = false;
				Chat::chatrms[i].usrs[j].erase();
				char* bye = "GOODBYE";
				send_message(connfd, bye);
				return 1;
			}
		}
	}
	return -1;
}


int who(int connfd){
	//list through chatrooms to check users
	for(size_t i=0; i<Chat::chatrms.size(); i++){
		for(size_t j =0; j<Chat::chatrms[i].usrs.size(); j++){
			//if connfd matches for user
			if(Chat::chatrms[i].usrs[j].connfd == connfd){
				for(size_t k = 0; k<Chat::chatrms[i].usrs.size(); k++){
					send_message(connfd, Chat::chatrms[i].usrs[k].nickname);
				}
				return 1;
			}
		}
	}
	return -1;
}


int help(int connfd){
	send_message(connfd, "\\JOIN nickname room (Join room)\n\\ROOMS (List rooms)\n\\LEAVE (Leave room)\n\\WHO (List users in room)\n\\HELP (List commands)\n\nickname message (Private message)\n'message' (Group Message)");
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



