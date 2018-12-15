using namespace std;

/*
	@param {int} connfd - the file descriptor from which we are reading
	@param {char *} message - stores what we read from the file descriptor connfd
*/
// A wrapper around recv to simplify calls.
int receive_message(int connfd, char *message);
/*
	@param {int} connfd - the file descriptor to which we are writing
	@param {char *} message - the message we are writing to the file descriptor connfd
*/
// A wrapper around send to simplify calls.
int send_message(int connfd, char *message);