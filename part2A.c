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
/* This is the main data stucture to pass off 
*/
typedef struct message
{
	long messageType;
	accEntry data;
} message;


int createMsgQ();
void atm();
void dbServer();
void dbEditor();



int main(int argc, char const *argv[])
{
		printf("Hello WOrld");limits
	return 0;
}

int createMsgQ(int key){
	int msgQid;
	key = ftok("/home/beej/somefile", 'b');
	msqid = msgget(key, 0666 | IPC_CREAT);
	// Let's leave the permissions open for now.
	//msgQid = msgget((key_t)1234, IPC_CREAT| 0600);
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
//sem referneces
//i sem nt semctl(int semid, int semnum, int cmd, ...);


       // int sem_wait(sem_t *sem);

       // int sem_trywait(sem_t *sem);

      // int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

       // int semget(key_t key, int nsems, int semflg);
// msgrcv(msqid, &pmb, sizeof(struct pirate_msgbuf) - sizeof(long), 2, 0);
//cmd which tells msgctl() how to behave
//Destructor
//msgctl(msqid, IPC_RMID, NULL);

void atm(int accNumber){

}

void dbServer(){

}

void dbEditor(){

}