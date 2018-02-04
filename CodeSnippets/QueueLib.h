typedef struct node {
  int data;
  struct node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} queue_t;

void Enqueue(queue_t **q, int data) {
  Node *node;
  
  if (q == NULL) {
    printf("Invalid parameter!\n");
    return;
  }
  
  node = (Node*) malloc (sizeof(queue_t));
  node->data = data;
  node->next = NULL;
  
  if (*q == NULL) { /* Empty queue. */
    *q = (queue_t*) malloc (sizeof(queue_t));
    (*q)->head = (*q)->tail = node;
  } else {
    (*q)->tail->next = node;
    (*q)->tail = node;
  }
}

int Dequeue(queue_t **q) {
  Node *node;
  int data;
  
  if (q == NULL) {
    printf("Invalid parameter!\n");
    return 0xdeadbeef;
  } else if (*q == NULL) {
    return 0xdeadbeef;
  }
  
  node = (*q)->head;
  (*q)->head = (*q)->head->next;
  
  data = node->data;
  free(node);
  
  if ((*q)->head == NULL) { /* Now empty queue. */
    free(*q);
    *q = NULL;
  }
  
  return data;
}