#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	//char initialPrompt[] = "Command: ";
	//write(1, initialPrompt, sizeof(initialPrompt));

	//outputText("tesst.txt");
	//deleteFile("test.txt");
	//writeToFile("test.txt", "Hello World");
	
	prompt();

	char shellExited[] = "\n\n\n--------------------\nShell exited\n";
	write(1,shellExited,sizeof(shellExited));
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

		printf("\n-%c-%i\n",command[10],(int)sizeof(command));

		write(1,command,sizeof(command));

		// printf("\n\n%s\n%i\n", command, rid);
		// if (inputData[4] == 'e') {
		// 	write(1,"yay",3);
		// }

		// if (command[4] == 'e') {
		// 	write(1,"yay",3);
		// }

// 		switch (c) {
// case '\0':
//     printf("   \\0");
//     break;

		// write(1,command[3],sizeof(command[3]));
		if (command == "exit") {
			printf("EXIT EXIT EXIT");
			write(1,"exit",sizeof("exit"));
			break;
		}
		break;
	}

	return 0;
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
	int fid, writtenBytes;
	fid = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	writtenBytes = write(fid, inputText, sizeof(inputText));
	close(fid);
	return 0;
}
