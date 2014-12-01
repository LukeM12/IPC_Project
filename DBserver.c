/*
**DBserver is the broker between the editor raw data and the ATM Machine
# author : Luke Morrison
Contributor/Partner Abhinav Thukral

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
//ftok generates a solid key to generate a key_t type system V IPC kwy
// .suitable  for use with msgget(2),
//        semget(2), or shmget(2).
int main (void){
	key_t key;
	int messageQID;
	//struct msgbuf receiver;
	//Make an ftok
	if ((key = ftok("DBeditor.c", 23)) == -1){
		perror("ftok");
		exit(1);
	}
	/* Get an instance of the ,message queue */
	if ((messageQID = msgget(key, 0644 | IPC_CREAT)) == -1){
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
	for(;;;){
		msg
	}
	printf("Message queue was destroyed");
	return 0;
}

//sem referneces
//i sem nt semctl(int semid, int semnum, int cmd, ...);
// int msgget(key_t key, int msgflg);

       // int sem_wait(sem_t *sem);

       // int sem_trywait(sem_t *sem);

      // int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

       // int semget(key_t key, int nsems, int semflg);
// msgrcv(msqid, &pmb, sizeof(struct pirate_msgbuf) - sizeof(long), 2, 0);
//cmd which tells msgctl() how to behave
//Destructor
//msgctl(msqid, IPC_RMID, NULL);