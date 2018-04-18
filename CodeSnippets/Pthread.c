// https://computing.llnl.gov/tutorials/pthreads/#ConditionVariables

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 5

void *PrintHello (void *t) {
  unsigned tid = * (unsigned *) t;
  printf("Hello, World! Thread: %u\n", tid);

  pthread_exit(NULL);
}

int main (int argc, char **argv) {
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  unsigned tid[MAX_THREADS];
  unsigned i;
  int rc; void *status;

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (& attr, PTHREAD_CREATE_JOINABLE);

  for (i = 0; i < MAX_THREADS; i++) {
    printf("In main(): Creating thread %u.\n", i);

  /*
	 * Note that if you pass &i instead of i, you are passing the
   * address of a location that is changing in main(). So, 'i' may be
   * 4 when you pass &i to the thread and may be something else when
   * it is actually printed in the PrintHello. Not thread-safe.
   */

  /*
   * To make it thread-safe, have a dedicated data structure for
   * each of the items. The tid array is created for that sake.
   */
    tid[i] = i;
    rc = pthread_create(&threads[i], &attr, PrintHello, (void*) &tid[i]);

    if (rc) {
      printf("pthread_create() failed for thread %u: %d\n", i, rc);
      exit(EXIT_FAILURE);
    }
  }

  pthread_attr_destroy (&attr);
  for (i = 0; i < MAX_THREADS; i++) {
    rc = pthread_join (threads[i], &status);

    if (rc) {
      printf("ERROR: Return from pthread_join: %d\n", rc);
      exit(EXIT_FAILURE);
    }

    printf("Main: Joined with thread: %u\n", i);
  }

  /* Last thing main() does before exiting. */
  pthread_exit(NULL);

  return 0;
}

//===============================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 3
#define COUNT_LIMIT 12

unsigned count;
pthread_mutex_t count_mutex;
pthread_cond_t count_thresh_cv;

void *watch_count (void *t) {
  unsigned tid;

  tid = *(unsigned*) t;
  printf("Waiting in thread %u for condition\n", tid);

  pthread_mutex_lock (&count_mutex);

  pthread_cond_wait (&count_thresh_cv, &count_mutex);
  printf("Count = %u\n", count);

  printf("Wait complete on condition: Thread %u\n", tid);
  pthread_mutex_unlock (&count_mutex);

  pthread_exit (NULL);
}

void *inc_count (void *t) {
  unsigned tid;
  unsigned i;

  tid = *(unsigned*) t;

  for (i = 0; i < 10; i++) {
    pthread_mutex_lock (&count_mutex);
    count++;

    if (count == COUNT_LIMIT) {
      pthread_cond_signal (&count_thresh_cv);
      printf("Signaled condition: Thread %u\n", tid);
    }

    pthread_mutex_unlock (&count_mutex);
  }

  pthread_exit (NULL);
}

int main (int argc, char **argv) {
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr; unsigned i;
  unsigned tid[MAX_THREADS] = {0,1,2};

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init (&count_mutex, NULL);
  pthread_cond_init (&count_thresh_cv, NULL);

  pthread_create (&threads[0], &attr, watch_count, (void*) &tid[0]);
  pthread_create (&threads[1], &attr, inc_count, (void*) &tid[1]);
  pthread_create (&threads[2], &attr, inc_count, (void*) &tid[2]);

  for (i = 0; i < MAX_THREADS; i++) {
    pthread_join (threads[i], NULL);
  }

  pthread_attr_destroy (&attr);
  pthread_mutex_destroy (&count_mutex);
  pthread_cond_destroy (&count_thresh_cv);
  pthread_exit(NULL);
}