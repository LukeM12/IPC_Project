/**
 * Part2a simulates an ATM machine
 * @author: Abhinav Thukral
 * @date: 26 November 2014
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define TRUE 1
#define FALSE 0


typedef struct accEntry
{
	long accNumber;
	int pin;
	float funds;
}accEntry;

typedef struct message
{
	long messageType;
	accEntry data;
}message;


int createMsgQ();
void atm();
void dbServer();
void dbEditor();



int main(int argc, char const *argv[])
{
		
	return 0;
}

void createMsgQ(int key){
	int msgQid;
	msgQid = msgget((key_t)1234, IPC_CREAT| 0600);
	if (msgQid == -1)
	{
		perror("msget failed");
		exit(1);
	}
	else{
		return msgQid;
	}
}



int sendMsg(int msgQid, message msg){
	int status;
	status = msgsnd(msgQid, &msg, sizeof(accEntry),0);
	if (status == -1)
	{
		printf("Message Sending failed\n");
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int receiveMsg(int msgQid, message *msg, int messageType, int flag){
	int bytesRead;
	if (flag)
	{
		bytesRead = msgrcv(msgQid, msg, sizeof(accEntry), messageType, 0);
	}
	else{
		bytesRead = msgrcv(msgQid, msg, sizeof(accEntry), messageType, IPC_NOWAIT);
	}
	if (bytesRead == -1)
	{
		return FALSE;
	}
	else{
		return TRUE;
	}

}

void atm(int accNumber){

}

void dbServer(){

}

void dbEditor(){

}