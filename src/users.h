using namespace std;

typedef struct user {
	char nickname[16];
	struct *sockAdr;
	bool chatting= false;
}user;
