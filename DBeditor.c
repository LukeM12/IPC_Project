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
	key_t user_key;
	key_t editor_key;
	int editor_ID;
	struct my_msgbuf receiver;
	//Make an ftok
	//For the editor communication IPC 
	if ((user_key = ftok("DBserver.c", 'E')) == -1){
		perror("ftok");
		exit(1);
	}

	/* Get an instance of the ,message queue */
	if ((editor_ID = msgget(editor_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	else {
		printf("The message Queue was created and the key was made \n");
	}
	for(;;) { /* Spock never quits! */
		if (msgrcv(editor_ID, &receiver, sizeof(receiver.messagetext), 0, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}

		printf("DBserver SAYS: \"%s\"\n", receiver.messagetext);
	}
	if ((msgctl(editor_ID, IPC_RMID, NULL)) == -1){
		perror("msgctl");
		exit(1);
	}

	printf("Message queue was destroyed");
	return 0;

}