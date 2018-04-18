class Worker {
  public:
    Worker (function work_f);
    void Start (function Callback); // Starts work_f and once finished, calls Callback().
};

class MultiWorker {
  public:
    MultiWorker ();
    void AddWorker (function work_f);
    void Start (function Callback);
};

MultiWorker is called by multiple threads.
Applications call the MultiWorker AddWorker function every time they need to schedule some function to run in the background at some point in the future.
When its time to start running the scheduled functions, an application calls MultiWorker::Start. Start then has to start running all the scheduled functions. Once all the scheduled functions are done, we need to call the Callback function only once.
========================================
3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

int next (int n) {
  if (n % 2 == 0) {
    return n / 2;
  } else {
    return 3n + 1;
  }
}

void main (int n) {
  int count = 0;

  while (n > 1) {
    n = next(n);
    count++;
  }
  
  return count;
}
//========================================
// BuddyBitmap implementation - Google for the problem statement.
#include <stdio.h>

void setworker (int *arr, int index, int n) {
  int lchild, rchild;
  
  lchild = 2 * index + 1;
  rchild = 2 * index + 2;

  if (lchild < n && arr[lchild] == 0) {
    arr[lchild] = 1;
    setworker (arr, lchild, n);
  }
  
  if (rchild < n && arr[rchild] == 0) {
    arr[rchild] = 1;
    setworker (arr, rchild, n);
  }
}

void clearworker (int *arr, int index) {
  int parent;
  
  if (index >= 0) {
    if ((index & 1) == 1) {
      // Odd child is the left child.
      parent = (index - 1) / 2;
    } else {
      // Even child is the right child.
      parent = (index - 2) / 2;
    }
    
    if (arr[parent] == 1) {
      arr[parent] = 0;
      
      clearworker (arr, parent);
    }
  }
}

void clear (int *arr, int offset, int len, int n) {
  for (int index = offset; index < n && index < offset + len; index++) {
    if (arr[index] == 1) {
      arr[index] = 0;

      clearworker (arr, index);
    }
  }
}

void set (int *arr, int offset, int len, int n) {
  for (int index = offset; index < n && index < offset + len; index++) {
    if (arr[index] == 0) {
      arr[index] = 1;

      setworker (arr, index, n);
    }
  }
}

void Print (int *arr, int n) {
  printf("{%d", arr[0]);
  
  for (int index = 1; index < n; index++) {
    printf(", %d", arr[index]);
  }

  printf("}\n");
}

int main() {
  int orig[] = {0,0,1,1,0,1,1,1,1,1,0,1};
  int n = sizeof(orig)/sizeof(int);
  int arr[n];

  printf("Original: ");
  Print (orig, n);
  printf("\n");

  // Covers all possible test cases.
  for (int offset = 0; offset < n; offset++) {
    for (int len = 1; len <= n - offset; len++) {
      
      for (int index = 0; index < n; index++) {
        arr[index] = orig[index];
      }
      
      clear (arr, offset, len, n);
      
      printf("[off:%d, len:%d] ", offset, len);
      Print (arr, n);
      printf("\n");
    }
  }
  
  return 0;
}

//==========================================================================
// Register and Fire implementation with a rudimentary queue implementation.

typedef struct list_s {
  void* (*fn)(void*);
  struct list_s *next;
} list_t;

list_t *queue = NULL;
typedef void* (*fn)(void*) Callback;

void Enqueue (Callback cb) {
  list_t *newnode = malloc;
  newnode->fn = cb;
  newnode->next = queue;
  queue = newnode;
}

bool IsEmpty (list_t *queue) {
  return NULL == queue;
}

Callback Dequeue () {
  list_t *delnode;
  
  delnode = queue;
  Callback cb = queue->fn;
  queue = queue->next;
  
  free (delnode);
  
  return cb;
}

bool HasFired = false;
Queue<Callback> q = new queue<Callback>;
Mutex mutex;

void Register (Callback cb) {
  mutex.acquire();
  
  if (HasFired == false) {
    queue.enqueue (cb);
    mutex.release();
  } else {
    mutex.release();
    cb.invoke();
  }
}

void Fire () {
  mutex.acquire();
  while (queue.empty() == false) {
    Callback cb = queue.dequeue();
    mutex.release();
    cb.invoke();
    mutex.acquire();
  }
  
  HasFired = true;
  mutex.release();
}