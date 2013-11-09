#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;/* ID returned by pthread_create() */
	pthread_mutex_t passedCharMutex;
	pthread_cond_t readyToReadWriteSignal;
	int philosoperId;
	int* forks;
};

// in the shared struct, have an int to represent each philosopher
// and an array of forks, the same number as their are of philosophers.
// 

static void *philosopher(void *arg) {
	struct thread_info *myInfo = arg;
	printf("Started thread id: %d\n", (int)myInfo->thread_id);	
	while (1) {
		//printf("Child thread while ran");
		pthread_mutex_lock(&myInfo->passedCharMutex);
		while(myInfo->full) { pthread_cond_wait(&myInfo->readyToReadWriteSignal, 
												&myInfo->passedCharMutex); }
		int rid = read(0,myInfo->passedChar,2);
		myInfo->full = 1;
		pthread_mutex_unlock(&myInfo->passedCharMutex);
		pthread_cond_signal(&myInfo->readyToReadWriteSignal);
	}
	pthread_exit(0);
}

int main() {
	int forks[3] = {0,0,0};
	struct thread_info tinfo = {.passedCharMutex = PTHREAD_MUTEX_INITIALIZER,
								.readyToReadWriteSignal = PTHREAD_COND_INITIALIZER,
								.full = 0};
	printf("Main thread id: %d\n", (int)tinfo.thread_id);

	int s = pthread_create(&tinfo.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&philosopher,
		&tinfo);
	//pthread_join(tinfo.thread_id,NULL);

	while (1) {
		//printf("Main thread while ran");
		pthread_mutex_lock(&tinfo.passedCharMutex);
		while (tinfo.full == 0) { pthread_cond_wait(&tinfo.readyToReadWriteSignal,
													&tinfo.passedCharMutex); }
		write(1,tinfo.passedChar,2);
		tinfo.full = 0;
		pthread_mutex_unlock(&tinfo.passedCharMutex);
		pthread_cond_signal(&tinfo.readyToReadWriteSignal);
	}
}
