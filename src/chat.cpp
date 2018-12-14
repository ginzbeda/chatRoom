#include "chat.h"
#include "connection.h"


vector<Chatroom *> Chat::chatrms;

void join(char *name, char *room, User* nUser){
	char* buf;
	bool found = false;
	if(strlen(name)==0) {
		buf = (char*) "No nickname";
		send_message(nUser->getCon(), buf);
		return;
	}
	if(strlen(room)==0){
		buf = (char*) "No room";
		send_message(nUser->getCon(), buf);
		return;
	}
		nUser->namer(name);

		if(nUser->getChatrm()!=0){
			nUser->getChatrm()->rmUsr(nUser);
		}
		//Searches for chatroom
		for(size_t i = 0; i< Chat::chatrms.size(); i++){
			//If found
			if(strncmp(Chat::chatrms[i]->getNm(), room, strlen(room))==0){
				found = true;
				// cout<<"Room: " << (nUser->getChatrm()!=NULL)<< endl;
				//Adds user to room
				Chat::chatrms[i]->addUsr(nUser);
				//Assigns user to room
				nUser->setChatrm(Chat::chatrms[i]);
				buf = (char*) "User Joined Room";
				send_message(nUser->getCon(), buf);
				// strncpy(buf, "", strlen(buf));
				return;
			}
		}
		if(found ==false){
			//Room not found create room
			Chatroom* rum = new Chatroom(room);
			//Add user to room list
			rum->addUsr(nUser);
			//Assign user to room
			nUser->setChatrm(rum);
			//Add room to rooms
			Chat::chatrms.push_back(rum);
			buf = (char*) "User Created & Joined Room";
			send_message(nUser->getCon(), buf);
			// strncpy(buf, "", strlen(buf));
		}
	
}
void rooms(User* usr){
	char* buf;
	int connfd = usr->getCon();
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			buf = (char*) Chat::chatrms[i]->name;
			strcat(buf, " ");
			send_message(connfd, buf);
		}
	}
	else{
		char* buf = (char*) "No chat rooms";
		send_message(connfd, buf);
	}
	memset(buf, 0, MAXLINE);
}


void leave(User* usr){
	bool present = false;
	int connfd = usr->getCon();
	Chatroom* rum =  usr->getChatrm();
	vector <User*> usrs = rum->getUsrLst();
	for(vector<User*>::iterator user = usrs.begin(); user != usrs.end(); user++){
		if(usr->getCon()==(*user)->getCon()){
			usr->getChatrm()->rmUsr(usr);
			char* bye = (char*) "GOODBYE";
			send_message(connfd, bye);
			present = true;
			break;
		}
	}
	if(present == false){
		char* buf = (char*) "Not in a room";
		send_message(connfd, buf);
	}
}



void who(User* usr){
	int connfd = usr->getCon();
	char* buf;
	Chatroom* rum = usr->getChatrm();
	if(rum == NULL) {
		char* buf = (char*) "Not in a room";
		send_message(connfd, buf);
	}
	else{
		vector<User*> usrs = rum->getUsrLst();
		for(size_t i=0; i<usrs.size(); i++){
			buf = usrs[i]->getName();
			strcat(buf, " ");
			send_message(connfd, buf);
		}
	}
	memset(buf, 0, MAXLINE);
}



void help(User* usr){
	int connfd = usr->getCon();
	char* buf = (char*) "\\JOIN nickname room (Join room)\n\\ROOMS (List rooms)\n\\LEAVE (Leave room)\n\\WHO (List users in room)\n\\HELP (List commands)\n\\nickname message (Private message)\n'message' (Group Message)";
	send_message(connfd, buf);
}


void mess(char *name, char *msg, User* usr)
{
	bool found = false;
	for(size_t i=0; i<Chat::chatrms.size(); i++)
	{
		for(size_t j=0; j<Chat::chatrms[i]->getUsrLst().size(); j++)
		{
			if(strncmp((char *)name,Chat::chatrms[i]->getUsrLst()[j]->getName(),16) == 0)
			{
				send_message(Chat::chatrms[i]->getUsrLst()[j]->getCon(),(char *)msg);
				send_message(usr->getCon(),(char *)msg);
				found = true;
				break;
			}
		}
	}
	if(found == false){
		char* buf = (char*) "User does not exist";
		send_message(usr->getCon(), buf);
	}
}

void message_everyone(char message[MAXLINE], User* usr)
{
	//step 3 : send the message to everyone in the sender's room including the sender
			//step 3a : we know the chatroom when we were finding the nickname
			//step 3b : loop through the user list in his chat room
			//step 3c : send_message() to every user in that list
	if(usr->getChatrm() == NULL){
		for(size_t i=0; i<Chat::chatrms.size(); i++)
		{
			for(size_t j=0; j<Chat::chatrms[i]->getUsrLst().size(); j++)
			{
				if(strncmp((char *)usr->getName(),Chat::chatrms[i]->getUsrLst()[j]->getName(),16) == 0)
				{
					char messg[MAXLINE+20]; // stores the message to be sent to everyone in the room
					strcpy(messg,usr->getName());// message now has the nickname of the sender
					int len = strlen(messg);
					messg[len] = ':'; //appends ':' to the message
					messg[len + 1] = ' '; // appends ' ' to the message
					strcat(messg,message); // appends the actual message after "nickname: "
					for(int k=0; j<Chat::chatrms[i]->getUsrLst().size(); k++)
					{
						int fd = Chat::chatrms[i]->getUsrLst()[k]->getCon();//gets the file descriptor of every user in the chat room
						send_message(fd,messg);//sends all of them the message
						//this also includes the sender
					}
				}
			}
		}
	}
	else{
		char* buf = (char*) "Not in Chatroom";
		send_message(usr->getCon(), buf);
	}
}



