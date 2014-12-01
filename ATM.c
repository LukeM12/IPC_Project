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
	int messageQID;
	//struct msgbuf receiver;
	//Make an ftok
	//For the editor communication IPC 
	if ((user_key = ftok("DBserver.c", 'E')) == -1){
		perror("ftok");
		exit(1);
	}

	/* Get an instance of the ,message queue */
	if ((messageQID = msgget(editor_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	else {
		printf("The message Queue was created and the key was made \n");
	}
	int result;
	if ((msgctl(messageQID, IPC_RMID, NULL)) == -1)
	{
		perror("msgctl");
		exit(1);
	}
	// for(;;;){
	// 	//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
	// }
	printf("Message queue was destroyed");
	return 0;

}