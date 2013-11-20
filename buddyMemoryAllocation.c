#include <stdlib.h>

int globalMemorySize;
void* global;

struct node {
	struct node left;
	struct node right;
	int value;
	bool inUse;
};

int main() {
	// First allocate 1Mbyte
	globalMemorySize = 1048576;
	global = malloc(globalMemorySize); // 1024^2
	
	struct node globalMap = {}
	globalMap.value = globalMemorySize;

	while(1) {.left - }
	return 1;
}

int findAvailable(int requiredSpace, struct node *buddyMapNode;) {
	if (globalMap.value >= requiredSpace) {
		int currentVal = buddyMapNode.value;
		*buddyMapNode.value = null;

}