/*
**DBserver is the broker between the editor raw data and the ATM Machine
Note : the editor will always take precedence in any operation
Because the user is disposable and the server always need to function independently 
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
	key_t user_key;
	key_t editor_key;
	int ATM_ID;
	int EDITOR_ID;
	struct my_msgbuf userBuffer;

	// if ((editor_key = ftok("DBeditor.c", 'E')) == -1){
	// 	perror("ftok");
	// 	exit(1);
	// }

		//For the user communication IPC  'A' for ATM
	if ((user_key = ftok("DBserver.c", 'Q')) == -1){
		perror("ftok");
		exit(1);
	}
		//For the editor communication IPC ' E' for EDITOR
	// if ((EDITOR_ID = msgget(editor_key, 0644)) == -1){
	// 	printf("Editor msgget\n");
	// 	perror("msgget");
	// 	exit(1);
	// }
	// 	/* Get an instance of the user message queue */
	if ((ATM_ID = msgget(user_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	for(;;) { /* Spock never quits! */
		if (msgrcv(ATM_ID, &userBuffer, sizeof(userBuffer.messagetext), 0, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}
		printf("ATM SAYS: \"%s\"\n", userBuffer.messagetext);
	}
	// while(fgets(userBuffer.messagetext, sizeof(userBuffer.messagetext), stdin) != NULL){
	// 	int len = strlen(userBuffer.messagetext);

	// 	//now we wnat to get the message
	// 	if (msgsnd(ATM_ID, &userBuffer, sizeof(userBuffer), 0) == -1){
	// 		perror("msgget");
	// 		exit(1);
	// 	}
	// }

	// int result;
	// if ((msgctl(ATM_ID, IPC_RMID, NULL)) == -1)
	// {
	// 	perror("msgctl");
	// 	exit(1);
	// }

	// if ((msgctl(EDITOR_ID, IPC_RMID, NULL)) == -1)
	// {
	// 	perror("msgctl");
	// 	exit(1);
	// }
	printf("Message queue was destroyed");
	
	return 0;
}

//sem referneces
//i sem nt semctl(int semid, int semnum, int cmd, ...);
// int msgget(key_t key, int msgflg);

       // int sem_wait(sem_t *sem);
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);


       // int sem_trywait(sem_t *sem);

      // int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

       // int semget(key_t key, int nsems, int semflg);
// msgrcv(msqid, &pmb, sizeof(struct pirate_msgbuf) - sizeof(long), 2, 0);
//cmd which tells msgctl() how to behave
//Destructor
//msgctl(msqid, IPC_RMID, NULL);
