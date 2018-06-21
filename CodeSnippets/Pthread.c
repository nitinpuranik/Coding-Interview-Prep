// https://computing.llnl.gov/tutorials/pthreads/#ConditionVariables

#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

#define MAX_THREADS 5

void* PrintHello (void *t) {
  unsigned tid = *(unsigned*) t;
  cout << "Hello, World! Thread: " << tid << endl;

  pthread_exit(NULL);
}

int main () {
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  unsigned tid[MAX_THREADS];
  void *status;

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  for (unsigned i = 0; i < MAX_THREADS; i++) {
    cout << "In main(): Creating thread " << i << endl;

    // Note that if you pass &i instead of i, you are passing the
    // address of a location that is changing in main(). So, 'i' may be
    // 4 when you pass &i to the thread and may be something else when
    // it is actually printed in the PrintHello. Not thread-safe.

    // To make it thread-safe, have a dedicated data structure for
    // each of the items. The tid array is created for that sake.

    tid[i] = i;
    int rc = pthread_create(&threads[i], &attr, PrintHello, (void*) &tid[i]);

    if (rc) {
      cout << "pthread_create() failed for thread " << i << ": " << rc << endl;
      exit(EXIT_FAILURE);
    }
  }

  pthread_attr_destroy (&attr);
  for (unsigned i = 0; i < MAX_THREADS; i++) {
    int rc = pthread_join (threads[i], &status);

    if (rc) {
      cout << "ERROR: Return from pthread_join: " << rc << endl;
      exit(EXIT_FAILURE);
    }

    cout << "Main: Joined with thread: " << i << endl;
  }

  // Last thing main() does before exiting.
  pthread_exit(NULL);

  return 0;
}

//===============================================================================================
#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

#define MAX_THREADS 3
#define COUNT_LIMIT 12

unsigned count;
pthread_mutex_t count_mutex;
pthread_cond_t count_thresh_cv;

void* watch_count (void *t) {
  unsigned tid = *(unsigned*) t;

  cout << "Waiting in thread " << tid << " for condition." << "\n";

  pthread_mutex_lock (&count_mutex);

  // Start waiting on the CV while simultaneously releasing mutex.
  pthread_cond_wait (&count_thresh_cv, &count_mutex);

  // Once you return from pthread_cond_wait, you automatically reacquire mutex.
  cout << "Count = " << count << "\n";

  cout << "Wait complete on condition: Thread " << tid << "\n";
  pthread_mutex_unlock (&count_mutex);

  pthread_exit (NULL);
}

void* inc_count (void *t) {
  unsigned tid = *(unsigned*) t;

  for (unsigned i = 0; i < 10; i++) {
    pthread_mutex_lock (&count_mutex);
    count++;
    cout << "Thread " << tid << " grabbed mutex. Count = " << count << "\n";

    if (count == COUNT_LIMIT) {
      pthread_cond_signal (&count_thresh_cv);
      cout << "Signaled condition: Thread " << tid << "\n";
    }

    // Don't forget to unlock mutex once you signal! Else the waiting threads never run.
    pthread_mutex_unlock (&count_mutex);
  }

  pthread_exit (NULL);
}

int main () {
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  unsigned tid[MAX_THREADS] {0,1,2};

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init (&count_mutex, NULL);
  pthread_cond_init (&count_thresh_cv, NULL);

  pthread_create (&threads[0], &attr, watch_count, (void*) &tid[0]);
  pthread_create (&threads[1], &attr, inc_count, (void*) &tid[1]);
  pthread_create (&threads[2], &attr, inc_count, (void*) &tid[2]);

  for (unsigned i = 0; i < MAX_THREADS; i++) {
    pthread_join (threads[i], NULL);
  }

  pthread_attr_destroy (&attr);
  pthread_mutex_destroy (&count_mutex);
  pthread_cond_destroy (&count_thresh_cv);
  pthread_exit(NULL);

  return 0;
}