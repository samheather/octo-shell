#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int globalMemorySize;
void* global;

struct node {
	struct node* left;
	struct node* right;
	int status; // 0 = empty, 1 = has children, 2 = node full
};

int findAvailable(int requestedSpace, struct node *memoryMapNode, void** returnedPointer, int calls) {
	int currentNodeSpace = globalMemorySize/pow(2,(calls-1));
	printf("Called with callid: %d, nodeStatus: %d, memoryRequested: %d, currentNodeSpace: %d  << WHY 40???? \n",
		calls, memoryMapNode->status, requestedSpace, currentNodeSpace);
	// If node full, or requested > node size, return error.
	if (memoryMapNode->status == 2 || requestedSpace > currentNodeSpace) {
		return 1;
	}
	// Else if node empty, and appropriate size, allocate memory.
	else if (memoryMapNode->status == 0) {
		if (requestedSpace > currentNodeSpace/2) {
			memoryMapNode->status = 2;
			return 0;
		}
		// else if node is too big, create left and right and then recurse on left.
		else {
			// create left and right nodes in tree
			struct node* newLeftNodePointer = malloc(sizeof(struct node));
			struct node* newRightNodePointer = malloc(sizeof(struct node));
			*newLeftNodePointer = (struct node){.left = 0, .right = 0, .status = 0};
			*newRightNodePointer = (struct node){.left = 0, .right = 0, .status = 0};
			memoryMapNode->left = newLeftNodePointer;
			memoryMapNode->right = newRightNodePointer;
			// Adjust memoryMapNode status
			memoryMapNode->status = 1;
			// Fill from left first.
			return findAvailable(requestedSpace, memoryMapNode->left, returnedPointer, calls+1);
		}
	}
	else if (memoryMapNode->status == 1) {
		if (findAvailable(requestedSpace, memoryMapNode->left, returnedPointer, calls+1) == 1) {
			if (findAvailable(requestedSpace, memoryMapNode->right, returnedPointer, calls+1) == 1) {
				printf("went right");
				return 1;
			}
			else {
				return 0; // this if block can be condensed heavily
			}
		}
		else {
			printf("went left");
			return 0;
		}
	}
	else {
		return 2; // Some unknown error occurred.
	}
}

int main() {
	// First allocate 1Mbyte
	globalMemorySize = 1048576;
	global = malloc(globalMemorySize); // 1024^2
	
	struct node memoryMap = {.left = 0, .right = 0, .status = 0};
//	printf(memoryMap.left);
	void* requestedSpace;
	void* requestedSpace2;
	findAvailable((1048576/4)-1, &memoryMap, &requestedSpace, 1);
	findAvailable((1048576/4)-1, &memoryMap, &requestedSpace2, 1);
//	printf(memoryMap.left);
	
	
// 	struct node globalMap = {}
// 	globalMap.value = globalMemorySize;
// 
// 	while(1) {.left - }
// 	return 1;
}
