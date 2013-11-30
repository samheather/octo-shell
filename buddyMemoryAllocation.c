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
	printf("Called with callid: %d, nodeStatus: %d, memoryRequested: %d, currentNodeSpace: %d\n",
		calls, memoryMapNode->status, requestedSpace, currentNodeSpace);
	// If node full, or requested > node size, return error.
	if (memoryMapNode->status == 2 || requestedSpace > currentNodeSpace) {
		return 1;
	}
	// Else if node empty, and appropriate size, allocate memory.
	else if (memoryMapNode->status == 0) {
		if (requestedSpace > currentNodeSpace/2) {
			memoryMapNode->status = 2;
			return 0;  // Use this node for data.
		}
		// else if node is too big, create left and right and then recurse on left.
		else {
			// create left and right nodes in tree
			// TODO(samheather) delete this memory at end, otherwise leaks.
			struct node* newLeftNodePointer = malloc(sizeof(struct node));
			struct node* newRightNodePointer = malloc(sizeof(struct node));
			*newLeftNodePointer = (struct node){.left = 0, .right = 0, .status = 0};
			*newRightNodePointer = (struct node){.left = 0, .right = 0, .status = 0};
			memoryMapNode->left = newLeftNodePointer;
			memoryMapNode->right = newRightNodePointer;
			// Adjust memoryMapNode status
			memoryMapNode->status = 1;
			// Fill from left first. Goes left down tree, so no need to change returnedPointer.
			return findAvailable(requestedSpace, memoryMapNode->left, returnedPointer, calls+1);
		}
	}
	else if (memoryMapNode->status == 1) {
		//Goes left down tree, so no need to change returnedPointer.
		if (findAvailable(requestedSpace, memoryMapNode->left, returnedPointer, calls+1) == 1) {
			// Now adjust returnedPointer, and un-adjust afterwards if 1 returned.
			*returnedPointer = *returnedPointer+currentNodeSpace/2;
			if (findAvailable(requestedSpace, memoryMapNode->right, returnedPointer, calls+1) == 1) {
				*returnedPointer = *returnedPointer-currentNodeSpace/2;
				printf("went RIGHT at status 1\n");
				return 1;
			}
			else {
				return 0; // this if block can be condensed significantly
			}
		}
		else {
			printf("went LEFT at status 1\n");
			return 0;
		}
	}
	else {
		return 2; // Some unknown error occurred.
	}
}

int freeSpace(void** memoryToFree, int size) {
	// TODO(samheather) find the node (a) that represents this pointer and set status to 0.
	// then set above pointer referred to by memoyrToFree to null.
	// Then run repairTree(struct node memoryMapNode) to repair nodes that point to (a).
}

int repairTree(struct node memoryMapNode) {
	// TODO(samheather) implement.
}

int main() {
	// First allocate 1Mbyte
	globalMemorySize = 1048576;
	global = malloc(globalMemorySize); // 1024^2
	
	struct node memoryMap = {.left = 0, .right = 0, .status = 0};
//	printf(memoryMap.left);
	void* requestedSpace0;
	void* requestedSpace1;
	void* requestedSpace2;
	void* requestedSpace3;
	void* requestedSpace4;
	if (findAvailable((1048576/4)-1, &memoryMap, &requestedSpace0, 1) != 0) { printf("Error\n"); }
	if (findAvailable((1048576/4)-1, &memoryMap, &requestedSpace1, 1) != 0) { printf("Error\n"); }
	if (findAvailable((1048576/4)-1, &memoryMap, &requestedSpace2, 1) != 0) { printf("Error\n"); }
	if (findAvailable((1048576/4)-1, &memoryMap, &requestedSpace3, 1) != 0) { printf("Error\n"); }
	if (findAvailable((1048576/4)-1, &memoryMap, &requestedSpace4, 1) != 0) { printf("Error\n"); }

	printf("Pointer address %p\n", requestedSpace0);
	printf("Pointer address %p\n", requestedSpace1);
	printf("Pointer address %p\n", requestedSpace2);
	printf("Pointer address %p\n", requestedSpace3);
	printf("Pointer address %p\n", requestedSpace4);
//	printf(memoryMap.left);
	
	
// 	struct node globalMap = {}
// 	globalMap.value = globalMemorySize;
// 
// 	while(1) {.left - }
// 	return 1;
}
