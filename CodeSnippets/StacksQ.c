#include <stdio.h>
#include <stdlib.h>

static int minimum = 

typedef struct node {
  int data;
  struct node *next;
  int nextmin;
}

void Push (Node **stacktop, int data) {
  Node *newnode;

  if (stacktop == NULL) {
    return;
  }
  
  newnode = (Node*) malloc (sizeof(Node));
  newnode->data = data;
  newnode->next = *stacktop;
  *stacktop = newnode;
}

int Pop (Node **stacktop) {
  Node *delnode;
  int data;
  
  if (stacktop == NULL || *stacktop == NULL) {
    return -1;
  }
  
  data = (*stacktop)->data;
  delnode = *stacktop;
  *stacktop = (*stacktop)->next;
  
  free(delnode);
  return data;
}

/*
 * Insert at tail, remove from head. Start the
 * Start the list at the head. Should be able to
 * move to the tail from the head. Else, when you
 * delete the head, you can't move back to the next
 * item unless it is a DLL.
 */
void Enqueue (Node **head, Node **tail, int data) {
  Node *newnode;
  
  if (head == NULL || tail == NULL) {
    return;
  }
  
  newnode = (Node*) malloc (sizeof(Node));  
  newnode->data = data;
  newnode->next = NULL;
  
  if (*tail == NULL) {
    *tail = newnode;
    *head = *tail;
  } else {
    (*tail)->next = newnode;
    *tail = newnode;
  }
}

int Dequeue (Node **head, Node **tail) {
  Node *delnode;
  int data;
  
  if (head == NULL || tail == NULL) {
    return -1;
  }
  
  if (*head == NULL || *tail == NULL) {
    return -1;
  }
  
  data = (*head)->data;
  delnode = *head;
  *head = (*head)->next;
  
  if (*head == NULL) {
    *tail = *head;
  }
  
  free(delnode);
  return data;
}

void PrintStack(Node *top) {
  if (top == NULL) {
    return;
  }

  while (top->next) {
    printf("%d <-- ", top->data);
    top = top->next;
  }
  
  printf("%d\n", top->data);
}

void PrintQueue(Node *head) {
  if (head == NULL) {
    return;
  }
  
  while (head->next) {
    printf("%d --> ", head->data);
    head = head->next;
  }
  
  printf("%d\n", head->data);
}

int main(int argc, char **argv) {
  //Node *top = NULL;
  Node *head = NULL, *tail = NULL;
  
  Enqueue(&head, &tail, 1);
  Enqueue(&head, &tail, 2);
  Enqueue(&head, &tail, 3);
  Enqueue(&head, &tail, 4);
  Enqueue(&head, &tail, 5);

  PrintQueue(head);
  Enqueue(&head, &tail, 6);
  PrintQueue(head);
  Dequeue(&head, &tail);
  PrintQueue(head);
  Enqueue(&head, &tail, 6);
  PrintQueue(head);
  Dequeue(&head, &tail);
  PrintQueue(head);
  return 0;
}