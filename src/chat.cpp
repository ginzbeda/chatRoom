#include "chat.h"
#include "connection.h"

vector<Chatroom *> Chat::chatrms;

//must change user to chatting if return 1
// user createUsr(char name[16],  sockaddr_in *server_addr, int connfd){
// 	user born;
// 	strncpy(born.nickname, name, strlen(name));
// 	born.server_addr = server_addr;
// 	born.chatting = false;
// 	return born;
// }

int join(char *name, char *room, User* nUser){
	char* buf;
	cout<< "1" <<endl;
	//Creates new set name and room of user
	if(strncmp(nUser->getName(),"",16)==0){
		nUser->namer(name);
	}
		cout<< "name: "<<nUser->getName()<<endl;
		//THIS IS THE PART
		// cout << "rooms= "<< strcmp((nUser->getChatrm())->getNm(), room)<< endl;
		cout<< "name1: "<<(nUser->getChatrm())<<endl;
	// if(strncmp(nUser->getChatrm()->getNm(), room, )!=0){
		if(nUser->getChatrm()!=0){
			nUser->setChatrm(0);
			cout<< "name2: "<<(nUser->getChatrm())<<endl;
		}

		
		cout<< "2" <<endl;
		//Searches for chatroom
		for(size_t i = 0; i< Chat::chatrms.size(); i++){
			cout<< "3" <<endl;
			//If found
			if(strncmp(Chat::chatrms[i]->name, room, sizeof(Chat::chatrms[i]->name))==0){
				cout<< "4" <<endl;
				// cout<<"Room: " << (nUser->getChatrm()!=NULL)<< endl;
				//Adds user to room
				Chat::chatrms[i]->addUsr(nUser);
				cout<< "5" <<endl;
				//Assigns user to room
				nUser->setChatrm(Chat::chatrms[i]);
				cout<< "6" <<endl;
				buf = (char*) "User Joined Room";
				cout<< "7" <<endl;
				send_message(nUser->getCon(), buf);
				// strncpy(buf, "", strlen(buf));
				cout<< "9" <<endl;
				return 1;
			}
		}
		//Room not found create room
		Chatroom* rum = new Chatroom(room);
		cout<< "10" <<endl;
		//Add user to room list
		rum->addUsr(nUser);
		cout<< "11" <<endl;
		//Assign user to room
		nUser->setChatrm(rum);
		cout<< "12" <<endl;
		//Add room to rooms
		Chat::chatrms.push_back(rum);
		cout<< "13" <<endl;
		buf = (char*) "User Created & Joined Room";
		cout<< "14" <<endl;
		send_message(nUser->getCon(), buf);
		cout<< "15" <<endl;
		// strncpy(buf, "", strlen(buf));
		cout<< "16" <<endl;
		return 2;
	
// else{
// 		buf = (char*) "Already in Room";
// 		send_message(nUser->getCon(), buf);
// 		return -1;
// 	}
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
	for(int i=0; i<Chat::chatrms.size(); i++)
	{
		for(int j=0; j<Chat::chatrms[i]->getUsrLst().size(); j++)
		{
			if(strncmp((char *)name,Chat::chatrms[i]->getUsrLst()[j]->getName(),16) == 0)
			{
				send_message(Chat::chatrms[i]->getUsrLst()[j]->getCon(),(char *)msg);
				send_message(connfd,(char *)msg);
				return 1;
			}
		}
	}
	return -1;
}

int message_everyone(char message[MAXLINE], User* usr)
{
	//step 3 : send the message to everyone in the sender's room including the sender
			//step 3a : we know the chatroom when we were finding the nickname
			//step 3b : loop through the user list in his chat room
			//step 3c : send_message() to every user in that list
	for(int i=0; i<Chat::chatrms.size(); i++)
	{
		for(int j=0; j<Chat::chatrms[i]->getUsrLst().size(); j++)
		{
			if(strncmp((char *)usr->getName(),Chat::chatrms[i]->getUsrLst()[j]->getName(),16) == 0)
			{
				char[MAXLINE+20] messg; // stores the message to be sent to everyone in the room
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
				return 1;
			}
		}
	}
	return -1;
}



