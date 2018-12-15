#include "chat.h"
#include "connection.h"


vector<Chatroom *> Chat::chatrms;

//Join a room
/*
  @param {char*} name - nickname to join under
  @param {char*} room - room to join
  @param {User*} usr - takes in a pointer to User
*/
void join(char *name, char *room, User* nUser){
	char* buf;
	bool found = false;
	//checks for room and name
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
			if((strlen(Chat::chatrms[i]->getNm())== strlen(room)) && (strncmp(Chat::chatrms[i]->getNm(), room, strlen(Chat::chatrms[i]->getNm()))==0)){
				found = true;
				//Checks for ban
				if(Chat::chatrms[i]->getBan(nUser)){
					char* buf = (char*) "You are banned from: ";
					send_message(nUser->getCon(), buf);
					char* buf2 = (char*) room;
					send_message(nUser->getCon(), buf2);
					return;
				}
				//Adds user to room
				Chat::chatrms[i]->addUsr(nUser);
				//Assigns user to room
				nUser->setChatrm(Chat::chatrms[i]);
				buf = (char*) "User Joined Room";
				send_message(nUser->getCon(), buf);
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

		}
	
}
//Lists rooms
/*
  @param {User*} usr - takes in a pointer to User
*/
void rooms(User* usr){
	int connfd = usr->getCon();
	if(Chat::chatrms.size()>0){
		for(size_t i = 0; i<Chat::chatrms.size(); i++){
			char* buf = (char*) Chat::chatrms[i]->name;
			send_message(connfd, buf);
			char* buf2 = (char*)" ";
			send_message(connfd, buf2);
		}
	}
	else{
		char* buf = (char*) "No chat rooms";
		send_message(connfd, buf);
	}
	
}

//Leaves current chatroom
/*
  @param {User*} usr - takes in a pointer to User
*/
void leave(User* usr){
	bool present = false;
	int connfd = usr->getCon();
	Chatroom* rum =  usr->getChatrm();
	vector <User*> usrs = rum->getUsrLst();
	for(vector<User*>::iterator user = usrs.begin(); user != usrs.end(); user++){
		if(usr->getCon()==(*user)->getCon()){
			usr->getChatrm()->rmUsr(usr);
			char* bye = (char*) " GOODBYE";
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


//Lists Users in chatroom
/*
  @param {User*} usr - takes in a pointer to User
*/
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
			send_message(connfd, buf);
			char* buf2 =(char*) " ";
			send_message(connfd, buf2);
		}
	}

}


//Lists roocommands
/*
  @param {User*} usr - takes in a pointer to User
*/
void help(User* usr){
	int connfd = usr->getCon();
	char* buf = (char*) "\\JOIN nickname room (Join room)\n\\ROOMS (List rooms)\n\\LEAVE (Leave room)\n\\WHO (List users in room)\n\\HELP (List commands)\n\\BAN nickname room (Ban from room)\n\\UBAN room (Unban all from room)\\nickname message (Private message)\n'message' (Group Message)";
	send_message(connfd, buf);
}

//Sends private emssage
/*
  @param {char} *name - nickname for destination
  @param {char} *msgr -message to be sent
  @param {User*} usr - takes in a pointer to User
*/
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

//Messages whole chatroom
/*
  @param {char} message[MAXLINE] - message to be sent
  @param {User*} usr - takes in a pointer to User
*/
void message_everyone(char message[MAXLINE], User* usr)
{
	if(usr->getChatrm() != NULL){
		char messg[MAXLINE]; // stores the message to be sent to everyone in the room
		strcpy(messg,usr->getName());// message now has the nickname of the sender
		strcat(messg, ": "); //appends ':' to the message
		strcat(messg,message); // appends the actual message after "nickname: "
			for(size_t j=0; j<usr->getChatrm()->getUsrLst().size(); j++)
			{
				int fd = usr->getChatrm()->getUsrLst()[j]->getCon();//gets the file descriptor of every user in the chat room
				send_message(fd,messg);//sends all of them the message
			}
	}
	else{
		char* buf = (char*) "Not in Chatroom";
		send_message(usr->getCon(), buf);
	}
}
//Ban from chatroom
/*
  @param {char*} name -User to ban
  @param {char*} room - room to ban from
  @param {User*} clnt - user to respond to
*/
void ban(char* name, char* room, User* clnt){
	User* usr;
	Chatroom* rm;
	bool found = false;
	bool found2 = false;
	for(size_t i =0; i< Chat::chatrms.size(); i++){
		if(strlen(room) == strlen(Chat::chatrms[i]->getNm()) && strncmp(Chat::chatrms[i]->getNm(),room, strlen(room)) == 0){
			rm = Chat::chatrms[i];
			found2 = true;
		}
		for(size_t j = 0; j<Chat::chatrms[i]->getUsrLst().size(); j++){
			if(strlen(name) == strlen(Chat::chatrms[i]->getUsrLst()[j]->getName()) && strncmp(Chat::chatrms[i]->getUsrLst()[j]->getName(), name, strlen(name))==0){
				usr = Chat::chatrms[i]->getUsrLst()[j];
				found = true;
			}
		}
		if(found && found2) {
			break;
		}
	}
	if(found && found2){
		rm->banUsr(usr);
		char* buf = (char*) "You are banned from: ";
		send_message(usr->getCon(), buf);
		char* buf2 = (char*) room;
		send_message(usr->getCon(), buf2);
		leave(usr);
	}
	else if(!found){
		char* buf = (char*) "User does not exist";
		send_message(clnt->getCon(), buf);
	}
	else{
		char* buf = (char*) "Room does not exist";
		send_message(clnt->getCon(), buf);
	}

}
// Unban all from chatroom
/*
  @param {char*} room - room to unban from
  @param {User*} clnt - User to respond to
*/
void unBan(char* room, User* clnt){
	Chatroom* rm;
	for(size_t i =0; i< Chat::chatrms.size(); i++){

		if(strlen(room) == strlen(Chat::chatrms[i]->getNm()) && strncmp(Chat::chatrms[i]->getNm(),room, strlen(room)) == 0){
			rm = Chat::chatrms[i];
			if(rm->getBanLst().size()>0){
				rm->rmBan();
				char* buf = (char*) "Bans were removed";
				send_message(clnt->getCon(), buf);
				return;
			}
		
		}
	}

	char* buf = (char*) "Room does not exist";
	send_message(clnt->getCon(), buf);

}



