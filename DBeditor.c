#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf {
	long mtype;
	char messagetext[200];
};

int main(int argc, const char *argv[]){
	key_t key;
	/* Make a key */
	if (key = ftok("DBeditor.c", 23) == -1)
	{
		printf("Ftok Failed, probably because no file named DBeditors does not exist ywet\n");
	}

	else {
		printf("Ftok Succeeded and the key was made \n");
	}
	if (msgget(key, 0644 | IPC_CREAT ) == -1) 
	{
		
	}
			//msgget(key_t key, int msgflg)
	/* Make a message queue */
	return 0;

}