#include <fcntl.h>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

int main() {
	//char initialPrompt[] = "Command: ";
	//write(1, initialPrompt, sizeof(initialPrompt));

	//outputText("tesst.txt");
	//deleteFile("test.txt");
	//writeToFile("test.txt", "Hello World");
	
	prompt();

	write(1,"\nShell exited\n",sizeof("\nShell exited\n"));
	return 0;
}

int prompt() {
	char initialPrompt[] = "\nCommand: ";
	write(1,initialPrompt,sizeof(initialPrompt));
	char inputData[256];
	read(0,inputData,256);
	int returnIndex = 0;
	while (inputData[returnIndex] != "\n") {
		printf(inputData[returnIndex]);
		returnIndex++;
	}
	printf("returnIndex: %i", returnIndex);
	write(1,inputData,3);
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
