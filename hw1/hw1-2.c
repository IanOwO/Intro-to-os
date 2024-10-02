#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int cont_working = 1;
	char* ptr;
	pid_t pid;

	while (cont_working) {
		char input[100];
		char instr[4];
		printf("osh> ");
		gets(input);
		pid = fork();
		for (int i = 0;i < 2;i++){
			instr[i] = input[i];
		}
		if (pid > 0) {
			wait(NULL);
		}
		else if (pid == 0){
			const char s[2] = " ";
			char *token;
			char *cmd1;
			char *cmd2;
			if(strcmp(instr,"ca") == 0){
				token = strtok(input,s);
				if (token != NULL) {
					cmd1 = strtok(NULL,s);
				}
				if (cmd1 != NULL) {
					execl("/bin/cat",instr,cmd1,NULL);
				}
				else {
					printf("error\n");
				}
			}
			else if(strcmp(instr,"ls") == 0){
				token = strtok(input,s);
				if (token != NULL) {
					cmd1 = strtok(NULL,s);
				}
				if (cmd1 != NULL) {
					cmd2 = strtok(NULL,s);
				}
				if (cmd2 != NULL){
					execl("/bin/ls",instr,cmd1,cmd2,NULL);
				}
				else if (cmd1 != NULL){
					execl("/bin/ls",instr,cmd1,NULL);
				}
				else {
					execl("/bin/ls",instr,NULL);
				}
			}
			else if(strcmp(instr,"da") == 0){
				ptr = input;
				execl("/bin/date",instr,NULL);
			}
			else if(strcmp(instr,"ps") == 0){
				token = strtok(input,s);
				if (token != NULL) {
					cmd1 = strtok(NULL,s);
				}
				if (cmd1 != NULL) {
					execl("/bin/ps",instr,cmd1,NULL);
				}
				else {
					printf("error\n");
				}
			}
			else if(strcmp(instr,"pw") == 0){
				ptr = input;
				execl("/bin/pwd",input,NULL);
			}
			else if(strcmp(instr,"ex") == 0){
				ptr = input;
			}
			else{
				printf("error in decoding\n");
			}
		}
		if (strcmp(instr,"ex") == 0) cont_working = 0; 
	}
	if(pid == 0) printf("Process end\n");
}
