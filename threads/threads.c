#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;/* ID returned by pthread_create() */
	char passedChar[1];
	pthread_mutex_t passedCharMutex;
	pthread_cond_t conditionalSignal;
};

static void *thread_1_start(void *arg) {
	struct thread_info *myInfo = arg;
	printf("Started thread id: %d\n", myInfo->thread_id);
	while (1) {
		read(0,
	}
	pthread_exit(0);
}

int main() {
	struct thread_info tinfo;
	tinfo.thread_id=1234;

	int s;
	printf("Main thread id: %d\n", tinfo.thread_id);
	s = pthread_create(&tinfo.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&thread_1_start,
		&tinfo);
	pthread_join(tinfo.thread_id,NULL);
}