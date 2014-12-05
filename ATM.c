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
#include <ctype.h>
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
	while(1){
		//int len = strlen(serverBuffer.messagetext);
		char input[200];
		char b[100];
		int len = strlen(input);
		//The the message Queue to start
		memset(serverBuffer.messagetext, '\0' ,sizeof(serverBuffer.messagetext));
		
		printf("Input your 5 digit User Account Number\n");
		fgets(input, sizeof(input), stdin);

		if (serverBuffer.messagetext[len-1] == '\n') serverBuffer.messagetext[len-1] = '\0';
		len = strlen(input) - 1; //for null terminating
		//get rid of newline
		if (len < 5 || len > 5){
			printf("Account Number Needs to be 5 (five) digits. Please try again :\n");
			continue;
		}
		if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';
		//Copy it to messagetext
		strcat(serverBuffer.messagetext, input);
		strcat(serverBuffer.messagetext, " ");

		//get the next value from the user & rid the messageText
		printf("Input your 3 digit PIN\n");
		fgets(input, sizeof(input), stdin);
		if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';

		//Append that to the end
		strcat(serverBuffer.messagetext, input);

		len = strlen(serverBuffer.messagetext);
		printf("ATM sending = %s\nLength= %i\n",serverBuffer.messagetext, len);

		if (msgsnd(server_ID, &serverBuffer,len+1, 0) == -1){
			perror("msgsnd");
		}		// if (serverBuffer.messagetext[len-1] == '\n') serverBuffer.messagetext[len-1] = '\0';
		else {
			if (msgrcv(server_ID, &serverBuffer, sizeof(serverBuffer.messagetext), 0, 0) == -1) {
				perror("msgrcv");
				exit(1);
			}
			{
				printf("ATM Result = %s\n", serverBuffer.messagetext);
			}
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
