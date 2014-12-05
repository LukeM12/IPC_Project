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
#include <time.h>

struct my_msgbuf {
	long mtype;
	char messagetext[200];
};

int LOGIN_COUNT = 0;
time_t rawtime;
struct tm * timeinfo;

int main(int argc, const char *argv[]){
	key_t server_key;
	int server_ID;
	struct my_msgbuf serverBuffer;

	/* Provide a key to use the ATM connected with Server */
	if ((server_key = ftok("ATM.c", 'Q')) == -1){
		perror("ftok");
		exit(1);
	}

	/* Get an instance of the message queue */
	if ((server_ID = msgget(server_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}

	printf("---==========================---\n    Welcome to the ATM Shell.\n---==========================---\nPlease Log in:\n\n");
	serverBuffer.mtype = 1;

	while(1){
		//Input Dummy Data Structure
		char input[200];
		int len = strlen(input);
		memset(serverBuffer.messagetext, '\0' ,sizeof(serverBuffer.messagetext));
		memset(input, '\0' ,sizeof(input));

		if (LOGIN_COUNT >= 3 ){
			printf("Your account was blocked at %s due to 3 Bad Login Attempts\n", asctime (timeinfo));
			printf("Please contact your local administrator to get access to your account\n");
		}
		else {
			printf("Input your 5 digit User Account Number\n");
			printf("(Invalid Login Attempts do not lower your Login Attempt tries)\n");
		}
		fgets(input, sizeof(input), stdin);
		if (LOGIN_COUNT >= 3){
			continue;
		}
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
		printf("You have %i Login Attempts left\n", 2-LOGIN_COUNT);
		printf("ATM sending = %s\n---Processing....---\n",serverBuffer.messagetext);

		if (msgsnd(server_ID, &serverBuffer,len+1, 0) == -1){
			perror("msgsnd");
		}		// if (serverBuffer.messagetext[len-1] == '\n') serverBuffer.messagetext[len-1] = '\0';
		else {
			if (msgrcv(server_ID, &serverBuffer, sizeof(serverBuffer.messagetext), 0, 0) == -1) {
				perror("msgrcv");
				exit(1);
			}
			{
				printf("ATM Result = %s ->", serverBuffer.messagetext);
				if (strcmp(serverBuffer.messagetext, "NOT OK") == 0){
					LOGIN_COUNT++;
					if (LOGIN_COUNT == 3){
						printf("INVALID ATTEMPT\n")
						//Grab the time for reference. Not necessary though
						time ( &rawtime );
						timeinfo = localtime ( &rawtime );
					}
				}

				else{
					//Enter the shell
				}
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
