#include "chat.h"
#include "connection.h"


vector<Chatroom *> Chat::chatrms;

/*
	@param {char *} name - nickname of the reciever
	@param {char *} room - room in which the reciever is
	@param {User *} nUser - User object for the reciever
*/

//joins the user with nickname 'name' to chatroom 'room'
//if 'room' does not exist one is created and 'nUser' is added to it
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
		for(size_t i = 0; i< Chat::chatrms.size(); i++){
			if((strlen(Chat::chatrms[i]->getNm())== strlen(room)) && (strncmp(Chat::chatrms[i]->getNm(), room, strlen(Chat::chatrms[i]->getNm()))==0)){
				found = true;
				Chat::chatrms[i]->addUsr(nUser);
				nUser->setChatrm(Chat::chatrms[i]);
				buf = (char*) "User Joined Room";
				send_message(nUser->getCon(), buf);
				return;
			}
		}
		if(found ==false){
			Chatroom* rum = new Chatroom(room);
			rum->addUsr(nUser);
			nUser->setChatrm(rum);
			Chat::chatrms.push_back(rum);
			buf = (char*) "User Created & Joined Room";
			send_message(nUser->getCon(), buf);
		}
	
}

/*
	@param {User *} usr - User object for the sender
*/

//displays the list of available rooms
void rooms(User* usr){
	
	int connfd = usr->getCon();
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			char* buf = (char*) Chat::chatrms[i]->name;
			strcat(buf, " ");
			send_message(connfd, buf);
		}
	}
	else{
		char* buf = (char*) "No chat rooms";
		send_message(connfd, buf);
	}
	
}

/*
	@param {User *} usr - User object for the sender
*/

//removes the user from the room it is in at the moment
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


/*
	@param {User *} usr - User object for the sender
*/

//displays the list of people in the user's current chatroom
void who(User* usr){
	int connfd = usr->getCon();
	
	Chatroom* rum = usr->getChatrm();
	if(rum == NULL) {
		char* buf = (char*) "Not in a room";
		send_message(connfd, buf);
	}
	else{
		char* buf;
		vector<User*> usrs = rum->getUsrLst();
		for(size_t i=0; i<usrs.size(); i++){
			buf = (char*) usrs[i]->getName();
			strcat(buf, " ");
			send_message(connfd, buf);
		}
		// memset(buf, 0, MAXLINE);
	}

}


/*
	@param {User *} usr - User object for the sender
*/

//dispalys the list of available commnands to the user
void help(User* usr){
	int connfd = usr->getCon();
	char* buf = (char*) "\\JOIN nickname room (Join room)\n\\ROOMS (List rooms)\n\\LEAVE (Leave room)\n\\WHO (List users in room)\n\\HELP (List commands)\n\\nickname message (Private message)\n'message' (Group Message)";
	send_message(connfd, buf);
}


/*
	@param {char *} name - nickname of the person the message is for, i.e, the reciever
	@param {char *} msg - the message the sender is sending to the reciever
	@param {User *} usr - User object for the sender
*/

//send a message 'msg' to the person with nickname 'name' in the chatroom
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


/*
	@param {char[]} message - the message the sender in sending to the group
	@param {User *} usr - User object for the sender
*/

//sends the message 'message' to everyone in the chatroom including the user itself
void message_everyone(char message[MAXLINE], User* usr)
{
	if(usr->getChatrm() != NULL){
		char messg[MAXLINE]; 
		strcpy(messg,usr->getName());
		strcat(messg, ": ");
		strcat(messg,message);
			for(size_t j=0; j<usr->getChatrm()->getUsrLst().size(); j++)
			{
				int fd = usr->getChatrm()->getUsrLst()[j]->getCon();
				send_message(fd,messg);
			}
	}
	else{
		char* buf = (char*) "Not in Chatroom";
		send_message(usr->getCon(), buf);
	}
}



