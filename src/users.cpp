#include "user.h"
#include <iostream>



user createUsr(char name[16], struct *sockAdr){
	user born;
	strncpy(born.nickname, name, sizeof(name));
	born.sockAdr = sockAdr;
	return born;
}

int chattr(user *change){
	change->chatting = true;
	return 1;
}

