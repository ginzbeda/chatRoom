#include "user.h"
#include <iostream>

vector<user> usrs;

void createUsr(char name[16], struct *sockAdr){
	user born;
	strncpy(born.nickname, name, sizeof(name));
	born.sockAdr = sockAdr;
}

int chattr(char name[16]){
	for(int i = 0; i < sizeof(usrs); i++){
		if(strcmp(usrs[i].nickname, name)==0){
			usrs[i].chatting = true;
			return 1;
		}
	}
	cout << "user does not exist" << endl;
	return -1;
}

