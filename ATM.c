/**
 * Author Luke Morrison
 * email : lukemo132@gmail.com
 */

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
	key_t server_key;
	int server_ID;
	struct my_msgbuf serverBuffer;
	//struct msgbuf receiver;
	//Make an ftok
	//For the editor communication IPC 
	if ((server_key = ftok("ATM.c", 'Q')) == -1){
		perror("ftok");
		exit(1);
	}

	/* Get an instance of the ,message queue */
	if ((server_ID = msgget(server_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	printf("Welcome to the ATM. \nPlease Input Your Desired Operation\n==\n");
	serverBuffer.mtype = 1; /* we don't really care in this case */
	while(fgets(serverBuffer.messagetext, sizeof serverBuffer.messagetext , stdin) != NULL){
		int len = strlen(serverBuffer.messagetext);

		if (serverBuffer.messagetext[len-1] == '\n') serverBuffer.messagetext[len-1] = '\0';

		if (msgsnd(server_ID, &serverBuffer,len+1, 0) == -1){
			perror("msgsnd");
		}
	}

	if ((msgctl(server_ID, IPC_RMID, NULL)) == -1)
	{
		perror("msgctl");
		exit(1);
	}

	printf("Message queue was destroyed");
	return 0;

}
