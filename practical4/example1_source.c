#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
		         
 /* When a SIGUSR1 signal arrives, set this variable. */
volatile sig_atomic_t usr_interrupt = 0;

void synch_signal (int sig)
{
    usr_interrupt = 1;
}
     
/* The child process executes this function. */
void child_function (void)
{
   /* Perform initialization. */
    printf ("I'm here!!!  My pid is %d.\n", (int) getpid ());
   /* Let parent know you're done. */
    sleep(1);
    kill (getppid (), SIGUSR1);

   /* Continue with execution. */
    puts ("Bye, now....");
    exit(0);
}
																	         
int main (void)
{
      struct sigaction usr_action;// struct.  what happens with signal
      sigset_t block_mask;// sugset_t - struct used to represent set of signals.
      pid_t child_id;// stores a pid
						          
      /* Establish the signal handler. */
      sigfillset (&block_mask);// init block_bask to full, includes all signals
      usr_action.sa_handler = synch_signal;// handler - action to associate with signum.
      usr_action.sa_mask = block_mask;// mask - mask of signals to block.  Also, signal that
      								// triggers the handler with be blocked.
      usr_action.sa_flags = 0;// set of flags which modify behaviour of signal.  formed from bitwise
      						// or of >=0 of a list.

     /* Create the child process. */
      child_id = fork ();
      if (child_id == 0)
            child_function ();          /* Does not return. */
      /* Busy wait for the child to send a signal. */
      sigaction(SIGUSR1, &usr_action, NULL); // sigaction change the action taken by a process
      										// on receipt of a specific signal.
      										// Takes signal and user_action (and old)
      while (!usr_interrupt)
          ;
      /* Now continue execution. */
      puts ("That's all, folks!");
}
