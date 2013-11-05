#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;/* ID returned by pthread_create() */
	char passedChar[2];
	int full;
	pthread_mutex_t passedCharMutex;
	pthread_cond_t readyToReadSignal;
	pthread_cond_t readyToWriteSignal;
};

static void *thread_1_start(void *arg) {
	struct thread_info *myInfo = arg;
	printf("Started thread id: %d\n", (int)myInfo->thread_id);	
	while (1) {
		printf("thread1 while ran");
		pthread_mutex_lock(&myInfo->passedCharMutex);
		while(myInfo->full) { pthread_cond_wait(&myInfo->readyToReadSignal, &myInfo->passedCharMutex); }
		int rid = read(0,myInfo->passedChar,2);
		myInfo->full = 1;
		pthread_mutex_unlock(&myInfo->passedCharMutex);
		pthread_cond_signal(&myInfo->readyToWriteSignal);
	}
	pthread_exit(0);
}

int main() {
	struct thread_info tinfo = {.passedCharMutex = PTHREAD_MUTEX_INITIALIZER,
								.readyToReadSignal = PTHREAD_COND_INITIALIZER,
								.readyToWriteSignal = PTHREAD_COND_INITIALIZER,
								.full = 0};
	printf("Main thread id: %d\n", (int)tinfo.thread_id);

	int s = pthread_create(&tinfo.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&thread_1_start,
		&tinfo);
	//pthread_join(tinfo.thread_id,NULL);

	while (1) {
		printf("thread2 while ran");
		pthread_mutex_lock(&tinfo.passedCharMutex);
		while (tinfo.full == 0) { pthread_cond_wait(&tinfo.readyToWriteSignal, &tinfo.passedCharMutex); }
		write(1,tinfo.passedChar,2);
		tinfo.full = 0;
		pthread_mutex_unlock(&tinfo.passedCharMutex);
		pthread_cond_signal(&tinfo.readyToReadSignal);
	}
}
