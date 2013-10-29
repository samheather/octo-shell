#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;/* ID returned by pthread_create() */
//	int thread_num;     /* Application-defined thread # */
//	char *argv_string;  /* From command-line argument */
};

static void *thread_1_start(void *arg) {
	struct thread_info *myInfo = arg;
	printf("Thread id: %d\n", myInfo->thread_id);
	pthread_exit(0);
}

int main() {
	pthread_attr_t attr;
	struct thread_info tinfo;

	int s;
	s = pthread_create(&tinfo.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&thread_1_start,
		&tinfo);
	pthread_join(tinfo.thread_id,NULL);
}