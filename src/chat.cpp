#include "chat.h"
#include "connection.h"

vector<Chatroom*> Chat::chatrms;


int join(char *name, char *room, User* nUser){
	//Creates new set name and room of user
	cout<<"1"<<endl;
	nUser->namer(name);
	//Searches for chatroom
		cout<<"2"<<endl;
	for(size_t i = 0; i< Chat::chatrms.size(); i++){
		//If found
			cout<<"3"<<endl;
		if(strncmp(Chat::chatrms[i]->name, room, sizeof(Chat::chatrms[i]->name))==0){
			//Adds user to room
				cout<<"4"<<endl;
			Chat::chatrms[i]->addUsr(nUser);
			//Assigns user to room
			nUser->setChatrm(Chat::chatrms[i]);
			char* buf = (char*) "User Joined Room";
			send_message(nUser->getCon(), buf);
			return 1;
		}
	}
	//Room not found create room
		cout<<"5"<<endl;
	Chatroom* rum = new Chatroom(room);
	//Add user to room list
		cout<<"6"<<endl;
	rum->addUsr(nUser);
	//Assign user to room
		cout<<"7"<<endl;
	nUser->setChatrm(rum);
	//Add room to rooms
		cout<<"8"<<endl;
	Chat::chatrms.push_back(rum);
	char* buf = (char*) "User Created & Joined Room";
	send_message(nUser->getCon(), buf);
	return 2;
}
int rooms(User* usr){
	int connfd = usr->getCon();
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			send_message(connfd, Chat::chatrms[i]->name);
		}
		return 1;
	}
	return -1;
}
int leave(User* usr){
	int connfd = usr->getCon();
	Chatroom* rum =  usr->getChatrm();
	vector <User*> usrs = rum->getUsrLst();
	for(vector<User*>::iterator user = usrs.begin(); user != usrs.end(); user++){
		if(usr->getCon()==(*user)->getCon()){
			rum = NULL;
			usrs.erase(user);
			char* bye = (char*) "GOODBYE";
			send_message(connfd, bye);
			return 1;
		}
	}
	return -1;
}



int who(User* usr){
	int connfd = usr->getCon();
	Chatroom* rum = usr->getChatrm();
	if(rum == NULL) return -1;
	vector<User*> usrs = rum->getUsrLst();
	for(size_t i=0; i<usrs.size(); i++){
		send_message(connfd, usrs[i]->getName());
	}
	return 1;
}


int help(User* usr){
	int connfd = usr->getCon();
	char* buf = (char*) "\\JOIN nickname room (Join room)\n\\ROOMS (List rooms)\n\\LEAVE (Leave room)\n\\WHO (List users in room)\n\\HELP (List commands)\n\\nickname message (Private message)\n'message' (Group Message)";
	send_message(connfd, buf);
	return 1;
}


int mess(char name[25], char msg[MAXLINE], User* usr)
{
// 	for(int i=0; i<Chat::chatrms.size(); i++)
// 	{
// 		for(int j=0; j<Chat::chatrms[i].usrs.size(); j++)
// 		{
// 			if(strncmp((char *)name,Chat::chatrms[i].usrs[j].nickname,16) == 0)
// 			{
// 				send_message(Chat::chatrms[i].usrs[j].connfd,(char *)msg);
// 				send_message(connfd,(char *)msg);
// 				return 1;
// 			}
// 		}
// 	}
	return -1;
}



