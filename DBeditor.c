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
void parseInputFile();
int test_user_Exists();
int main(int argc, const char *argv[]){
	key_t server_key;
	int server_ID;
	struct my_msgbuf receiver;
	//Make an ftok
	//For the editor communication IPC 
	if ((server_key = ftok("DBserver.c", 'E')) == -1){
		perror("ftok");
		exit(1);
	}
	//parseInputFile();
test_user_Exists();
	// /* Get an instance of the ,message queue */
	// if ((server_ID = msgget(server_key, 0644 | IPC_CREAT)) == -1){
	// 	perror("msgget");
	// 	exit(1);
	// }
	// printf("The Database Listener is awake and waiting for Database Input\n=====\n");
	// for(;;) { /* Spock never quits! */
	// 	if (msgrcv(server_ID, &receiver, sizeof(receiver.messagetext), 0, 0) == -1) {
	// 		perror("msgrcv");
	// 		exit(1);
	// 	}

	// 	printf("DBserver SAYS: \"%s\"\n", receiver.messagetext);
	// }
	// if ((msgctl(server_ID, IPC_RMID, NULL)) == -1){
	// 	perror("msgctl");
	// 	exit(1);
	// }

	// printf("Message queue was destroyed");
	// return 0;

}

void parseInputFile(){
    char *localString;
    size_t len = 0;
    int bytes_read;
    char *token2;
    const char s[2] = ",";
    FILE* inFile = fopen("database.txt","r");
    int one,two,three;
    int count_entries = 0;
    int count_fields = 0;
    while (bytes_read != -1) { 
        bytes_read = getline(&localString, &len, inFile);    
        char* token = strtok(localString, ",");
		while (token) {
		    printf("token: %s\n", token);
		    token = strtok(NULL, ",");
		    count_fields++;
		}
     }
}
/**
 * Description : This checks to see if the end user exists  
 * @param: the User Account Number
 * return: If the user exists in the database or not
 */
int user_Exists(int AccountNum){
    char *localString;
    size_t len = 0;
    int bytes_read;
    char *token2;
    const char s[2] = ",";
    FILE* inFile = fopen("database.txt","r");
    float one,two,three;
    float count_entries = 0;
    float count_fields = 0;
    while (bytes_read != -1) { 
        bytes_read = getline(&localString, &len, inFile);    
        char* token = strtok(localString, ",");
		while (token) {
		    printf("Value as token: %s\n", token);
		    printf("Value as int = %li\n",strtol(token, NULL, 10));
		    long int a = strtol(token, NULL, 10);
		    // printf("THIS IS A = %li AND THIS IS B = %i\n\n", a, AccountNum);

		    // if (a == AccountNum){
		    // 	printf("At leat this part works \n");

		    // }
		    if (count_fields==0 && a == AccountNum){
		    	printf("We found the value\n");
		    	return 1;
		    }
		    token = strtok(NULL, ",");
		    count_fields++;
		    // printf("1 + %i = %i", atoi (token), 1 + atoi (token)  );
		}
	count_fields = 0;
	count_entries++;
     }
     return 0;
}
/** accomponied by a test */
int test_user_Exists(){
	//user_Exists(000117
	//Very very strange case, I think it reads it as hex or something, because the input parameter ends up being 79 instead of 117 because of leading 0s
	if (user_Exists(11) == 1){
		printf("Test User Exists Passed!\n");
	}
	else{
		printf("Test User Exists Failed!\n");
	}
     return 0;
}
// FILE *readInputFile(char *fileString){
   
//     FILE *file = fopen(fileString, "r");
//     if (file == NULL){
//         error_flag[index]= ERROR_FILEIO;
//         index++;
//         printf("\n%s\n", ERROR_FILEREAD_out);
//         return ERROR_FILEREAD;
//     }
//     else return file;
// }
