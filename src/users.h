using namespace std;

typedef struct user {
	char nickname[16];
	struct *sockAdr;
	bool chatting= false;
}user;

void createUsr(char name[16], struct *sockAdr);
int chattr(char name[16]);