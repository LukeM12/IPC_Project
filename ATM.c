#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf {
	long mtype;
	char messagetext[20];
};

int main(int argc, const char *argv[]){
	key_t server_key;
	int SERVER_ID;
	struct my_msgbuf serverBuffer;
	//struct msgbuf receiver;
	//Make an ftok
	//For the editor communication IPC 
	if ((server_key = ftok("DBserver.c", 'A')) == -1){
		perror("ftok");
		exit(1);
	}

	/* Get an instance of the ,message queue */
	if ((SERVER_ID = msgget(server_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	int result;
	if ((msgctl(SERVER_ID, IPC_RMID, NULL)) == -1)
	{
		perror("msgctl");
		exit(1);
	}

	serverBuffer.mtype = 1; /* we don't really care in this case */
	while(fgets(serverBuffer.messagetext, sizeof serverBuffer.messagetext , stdin) != NULL){
						int len = strlen(serverBuffer.messagetext);
				//now we wnat to get the message
		if (msgsnd(SERVER_ID, &serverBuffer,len+1, 0) == -1){
			perror("msgsnd");
			exit(1);
		}
	}
	printf("Message queue was destroyed");
	return 0;

}