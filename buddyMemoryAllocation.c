#include <stdlib.h>

int globalMemorySize;
void* global;

struct node {
	struct node* left;
	struct node* right;
//	int value;
	int status; // 0 = empty, 1 = has children, 2 = node full
};

int main() {
	// First allocate 1Mbyte
	globalMemorySize = 1048576;
	global = malloc(globalMemorySize); // 1024^2
	
	struct node memoryMap = {.left = nullptr, .right = nullptr, .status = 0};
	
// 	struct node globalMap = {}
// 	globalMap.value = globalMemorySize;
// 
// 	while(1) {.left - }
// 	return 1;
}

int findAvailable(int requestedSpace, struct node *memoryMapNode, void* returnedPointer, int calls) {
	int currentNodeSpace = globalMemorySize/(2**(calls-1));
	// If node full, or requested > node size, return error.
	if (*memoryMapNode.status == 2 | requestSpace > currentNodeSpace) {
		return 1;
	}
	// Else if node empty, and appropriate size, allocate memory.
	else if (*memoryMapNode.status == 0) {
		if (requestedSpace > currentNodeSpace/2) {
			*memoryMapNode.status = 2;
			return 0;
		}
		// else if node is too big, create left and right and then recurse on left.
		else {
			// create left and right nodes in tree
			struct node* newLeftNodePointer = {.left = nullptr, .right = nullptr, .status = 0};
			struct node* newRightNodePointer = {.left = nullptr, .right = nullptr, .status = 0};
			memoryMapNode->left = newLeftNodePointer;
			memoryMapNode->right = newRightNodePointer;
			// Adjust memoryMapNode status
			memoryMapNode->status = 1;
			// Fill from left first.
			return findAvailable(requestedSpace, memoryMapNode->left, returnedPointer, calls++);
	}
	else if (*memoryMapNode.status == 1) {
		if (findAvailable(requstedSpace, memoryMapNode->left, returnedPointer, calls++) == 1) {
			if (findAvailable(requstedSpace, memoryMapNode->right, returnedPointer, calls++) == 1) {
				return 1;
			}
		}
		else {
			return 0;
		}
	}
		
	
	// If request space > global memory size or node is full, return 1
	// else if requested space > currentNodeSpace / 2, allocate node
	// else traverse down tree and find node that will work.
	
	
// 	if (globalMap.value >= requestedSpace) {
// 		int currentVal = buddyMapNode.value;
// 		*buddyMapNode.value = null;

}