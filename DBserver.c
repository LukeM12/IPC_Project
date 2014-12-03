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
	struct my_msgbuf editorBuffer;
	/* Configure the MSGQueue for the ATM Machine */
//This is an outgoing message IPC
	if ((editor_key = ftok("DBserver.c", 'E')) == -1){
		perror("ftok");
		exit(1);
	}
		//For the editor communication IPC ' E' for EDITOR
	if ((EDITOR_ID = msgget(editor_key, 0644 | IPC_CREAT)) == -1){
		printf("Editor msgget\n");
		perror("msgget");
		exit(1);
	}
/* Configure the MSQueue for the Database Editor */
	if ((user_key = ftok("ATM.c", 'Q')) == -1){
		perror("ftok");
		exit(1);
	}

	// 	/* Get an instance of the user message queue */
	if ((ATM_ID = msgget(user_key, 0644 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}
	printf("Server is connected to Database and waiting for User Input\n==\n");
	editorBuffer.mtype = 1; /* we don't really care in this case */
	for(;;) { 
		if (msgrcv(ATM_ID, &userBuffer, sizeof(userBuffer.messagetext), 0, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}

		/**
		 * If the message was passed in, this is where the sanitation will go
		 * To Fulfill the functional requirements of the assignment
		 */
		else{
			//So it received a message. First get a copy of that.
			//strcpy(editorBuffer.messagetext, userBuffer.messagetext);
			int len = strlen(editorBuffer.messagetext);
		   sprintf
		    (editorBuffer.messagetext, userBuffer.messagetext);
   // sendMsg.type = CLIENT_MSG_TYPE;
   // sprintf
   //  (sendMsg.text, "From CLIENT: Are you there?");
   // msgFlags = 0;

   // if (msgsnd(msgQID, &sendMsg, 
   //   strlen(sendMsg.text)+1, msgFlags) < 0)
   // {
   // perror("CLIENT: msgsnd");
   // exit(EXIT_FAILURE);
   // }

			if (editorBuffer.messagetext[len-1] == '\n') editorBuffer.messagetext[len-1] = '\0';

			printf("Value Copied to Buffer Memory: %s\n",editorBuffer.messagetext);
			//try and send it
			if (msgsnd(EDITOR_ID, &editorBuffer,len+1, 0) == -1){
				printf("Message was not sent\n");
				perror("msgsnd");
			}
			else{
				printf("\n\nThe message was sent\n");
			}
		}
		//printf("ATM SAYS: \"%s\"\n", userBuffer.messagetext);
	}

	if ((msgctl(ATM_ID, IPC_RMID, NULL)) == -1)
	{
		perror("msgctl");
		exit(1);
	}

	if ((msgctl(EDITOR_ID, IPC_RMID, NULL)) == -1)
	{
		perror("msgctl");
		exit(1);
	}
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
