#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;/* ID returned by pthread_create() */
	int *forks;
	pthread_mutex_t *forkMutexs;
	int philoId;
	//pthread_cond_t readyToReadWriteSignal; // not needed I think?
};
	
int forks[4] = {0,1,2,3};
pthread_mutex_t forkMutexs[4];

static void *philo(void *arg) {
	struct thread_info *myInfo = arg;
	int philoId = myInfo->philoId;	
	printf("Started thread id: %d, philoId: %d\n", (int)myInfo->thread_id, philoId);

	/*
	while (1) {
		//printf("Child thread while ran");
		pthread_mutex_lock(&myInfo->passedCharMutex);
		while(myInfo->full) { pthread_cond_wait(&myInfo->readyToReadWriteSignal, 
												&myInfo->passedCharMutex); }
		int rid = read(0,myInfo->passedChar,2);
		myInfo->full = 1;
		pthread_mutex_unlock(&myInfo->passedCharMutex);
		pthread_cond_signal(&myInfo->readyToReadWriteSignal);
	} */
	pthread_exit(0);
}

int main() {
	printf("Main thread id: %d\n", (int)pthread_self());

	struct thread_info thread_info_p0 = {.forks = forks,
								.forkMutexs = forkMutexs,
								.philoId = 0};
	struct thread_info thread_info_p1 = {.forks = forks,
								.forkMutexs = forkMutexs,
								.philoId = 1};
	struct thread_info thread_info_p2 = {.forks = forks,
								.forkMutexs = forkMutexs,
								.philoId = 2};
	struct thread_info thread_info_p3 = {.forks = forks,
								.forkMutexs = forkMutexs,
								.philoId = 3};

	int returnValP0 = pthread_create(&thread_info_p0.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&philo,
		&thread_info_p0);
	int returnValP = pthread_create(&thread_info_p1.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&philo,
		&thread_info_p1);
	int returnValP2 = pthread_create(&thread_info_p2.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&philo,
		&thread_info_p2);
	int returnValP3 = pthread_create(&thread_info_p3.thread_id,
		NULL, // was address of attr, error as this was not initialised.
		&philo,
		&thread_info_p3);
	//pthread_join(tinfo.thread_id,NULL);
	while(1) {}
/*
	while (1) {
		//printf("Main thread while ran");
		pthread_mutex_lock(&tinfo.passedCharMutex);
		while (tinfo.full == 0) { pthread_cond_wait(&tinfo.readyToReadWriteSignal,
													&tinfo.passedCharMutex); }
		write(1,tinfo.passedChar,2);
		tinfo.full = 0;
		pthread_mutex_unlock(&tinfo.passedCharMutex);
		pthread_cond_signal(&tinfo.readyToReadWriteSignal);
	}*/
}
