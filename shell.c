#include <fcntl.h>
//#include <stdio.h>  // Hopefully do not need this again.
#include <string.h>
#include <stdlib.h>

// For threading
#include <unistd.h>
#include <sys/wait.h>

int main() {
	char shellLoaded[] = "\n--------------------\nShell Loaded Sucessfully: "
	"Octo-Shell V0.1\nCopyright (c) 2013 Sam Heather\nType \"help\""
	"for help.";
	write(1,shellLoaded,stringLength(shellLoaded));
	
	prompt();

	char shellExited[] = "\n--------------------\n\n\nShell exited\n";
	write(1,shellExited,stringLength(shellExited));
	return 0;
}

int prompt() {
	//write(1,string('a'),sizeof(string('a')));
	while (1 == 1) {
		char initialPrompt[] = "\nCommand: ";
		write(1,initialPrompt,sizeof(initialPrompt));

		// Get Input
		char inputData[256];
		int rid;
		rid = read(0,inputData,256);

		// Strip input
		char command[rid];
		int i;
		for (i = 0; i<=rid-2; i++) {
			command[i] = inputData[i];
		}
		command[rid-1] = '\0';

		// Debug
		//  printf("\n-%c-%i\n",command[10],(int)sizeof(command));
		//  write(1,command,sizeof(command));

		if (strcmp(command, "exit") == 0) {
			break;
		}

		char *instruction;
		char *parameter_1;
		char *parameter_2;
		instruction = strtok(command, " ");
		parameter_1 = strtok(NULL, " ");
		parameter_2 = strtok(NULL, " ");
		
		if (strcmp(instruction, "help") == 0) {
			char docs[] = "Instructions: \
			\n exit \
			\n rm <file>, \
			\n read <file>, \
			\n write <file, \"text\">, \
			\n ls <path>\t\t\t\t(No spaces in path), \
			\n e <other commands/parameters>\t\tRuns in new thread (ls only)";
			write(1,docs,stringLength(docs));
		}
		else if (strcmp(instruction, "rm") == 0) {
			deleteFile(parameter_1);
		}
		else if (strcmp(instruction, "read") == 0) {
			outputText(parameter_1);
		}
		else if (strcmp(instruction, "write") == 0) {
			writeToFile(parameter_1,parameter_2);
		}
		else if (strcmp(instruction, "ls") == 0) {
			callLs(parameter_1);
		}
		else if (strcmp(instruction, "e") == 0) {
			callInNewThread(instruction, parameter_1);
		}
		else {
			write(1,"No such instruction",stringLength("No such instruction"));
		}
	}

	return 0;
}

int stringLength(char *inputString) {
	int count = 1;
	while (*(inputString+1) != '\0') {
		inputString = inputString + 1;
		count++;
	}
	return count;
}

int outputText(char file[]) {
	char chars[1];
	char seperator[] = "\n----------\n";
	int fid;
	fid = open(file, O_RDONLY);
	if (fid < 0) {perror("readFailed"); exit(1);}
	write(1,seperator,sizeof(seperator));
	while (read(fid, chars, 1) == 1) write(1, chars, 1);
	write(1,seperator,sizeof(seperator));
	close(fid);
}

int deleteFile(char file[]) {
	if (remove(file) < 0) {perror("delete failed"); exit(1);}
}

int writeToFile(char file[], char inputText[]) {
	char *withoutQuotes;
	withoutQuotes = strtok(inputText, "\"");
	int fid, writtenBytes;
	fid = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	writtenBytes = write(fid, withoutQuotes, stringLength(withoutQuotes));
	close(fid);
	return 0;
}

int callLs(char path[]) {
	int pid, stat_loc;
	pid = fork();
	if (pid == 0) { execl("/bin/ls\0", path, NULL); }
	else {
		wait(&stat_loc);
	}
}
