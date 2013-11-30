#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

typedef struct data
{
 char name[10];
  int age;
} data;

// I couldn't understand what was happening in terms of the handler funciton.
// or what line 52 would do.  Why woulnd't it be SIGURS1?


/* Shouldnt really use of printf/fprintf in the below because you're not
really meant to make system calls in a handler. In most cases such a 
call would block the process (probably forever). Here we get away with it
because we're not creating a race condition (as parent is sleeping) */

void sig_func(int sig)
{
  fprintf(stderr, "Caught signal 11\n", 17);
}

void func(data *p)
{
  struct sigaction usr_action;
    sigset_t block_mask;
    
    fprintf(stderr, "This is from thread function\n");
   strcpy(p->name, "Mr. Linux\0");
   p->age=30;

   /* Establish the signal handler. */
   sigfillset (&block_mask);
   usr_action.sa_handler = sig_func;  // Sets handler
   usr_action.sa_mask = block_mask;
   usr_action.sa_flags = 0;
   sigaction(SIGUSR1, &usr_action, NULL);

   sleep(3); // Sleep to catch the signal.
}

int main()
{
  pthread_t tid;
  pthread_attr_t attr;
  data d;
  data *ptr = &d;

  //signal(SIGSEGV,sig_func); // Register signal handler before going multithread
  							// change to SIGUSR1?

  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,(void*)func,ptr);
  sleep(1); // Leave time for initialisation

  pthread_kill(tid,SIGUSR1);

  pthread_join(tid,NULL);
  fprintf(stderr, "Name:%s\n",ptr->name);
  fprintf(stderr, "Age:%d\n",ptr->age);
}

