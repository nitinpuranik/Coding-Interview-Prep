#include <iostream>
using namespace std;

typedef struct node {
  long data;
  struct node *next;
} Node;

void Print (Node *node) {
  while (node) {
    cout << node->data << ' ';
    node = node->next;
  }

	cout << endl;
}

void Insert (Node **head, long data) {
  if (head == nullptr)
    return;

  Node *newnode = new Node;
  newnode->data = data;
  newnode->next = *head;
  *head = newnode;
}

unsigned int Count (Node *list, long data) {
  unsigned int count = 0;

  while (list) {
    if (list->data == data)
      count++;

    list = list->next;
  }

  return count;
}

long GetNth (Node *node, int index) {
  while (node && index >= 0) {
    node = node->next;
    index--;
  }

  if (node && index == 0) {
    return node->data;
  }

  cout << "Out of bounds!" << endl;
  return 0xdeadbeef;
}

void DeleteList (Node **node) {
  if (node == nullptr)
    return;

  while (*node) {
    Node *delnode = *node;
    *node = (*node)->next;

    delete delnode;
  }
}

long Pop (Node **head) {
  if (head == nullptr || *head == nullptr)
    return 0xdeadbeef;

  long data = (*head)->data;
  Node *node = *head;

  *head = (*head)->next;
  delete node;

  return data;
}

void Insert (Node **head, long index, long data) {
  if (head == nullptr || index < 0)
    return;

  Node *curr, *prev;
  curr = *head;
  prev = nullptr;

  while (curr && index > 0) {
    prev = curr;
    curr = curr->next;
    index--;
  }

  if (index == 0) {
    Node *newnode = new Node;
    newnode->data = data;
    newnode->next = curr;

    if (prev) {
      prev->next = newnode;
    } else {
      *head = newnode;
    }
  }
}

void SortedInsert (Node **head, Node *newnode) {
  Node *curr, *prev;

  if (head == NULL || newnode == NULL) {
    return;
  }

  prev = NULL;
  curr = *head;

  while (curr && curr->data < newnode->data) {
    prev = curr;
    curr = curr->next;
  }

  if (prev) {
    prev->next = newnode;
  } else {
    *head = newnode;
  }

  newnode->next = curr;
}

void InsertSort(Node **head) {
  Node *curr, *newnode;

  if (head == NULL || *head == NULL) {
    return;
  }

  curr = *head;
  *head = NULL;

  while (curr) {
    newnode = curr;
    curr = curr->next;

    SortedInsert(head, newnode);
  }
}

void Append (Node **A, Node **B) {
  Node *curr;

  if (A == NULL || B == NULL || *B == NULL) {
    return;
  }

  curr = *A;

  while (curr && curr->next) {
    curr = curr->next;
  }

  if (curr) {
    curr->next = *B;
  } else {
    *A = *B;
  }

  *B = NULL;
}

/* Have a one node jumping slow pointer and two node jumping fast pointer. */
void FrontBackSplit (Node *source, Node **frontRef, Node **backRef) {
  Node *fast, *slow;

  if (source == NULL || frontRef == NULL || backRef == NULL) {
    return;
  }

  slow = source;
  fast = source->next;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  *frontRef = source;
  *backRef = slow->next;
  slow->next = NULL;
}

void RemoveDuplicates (Node *head) {
  while (head && head->next) {
    if (head->data == head->next->data) {
      Node *delnode = head->next;

      head->next = delnode->next;

      free(delnode);
    } else {
      head = head->next;
    }
  }
}

void MoveNode (Node **dest, Node **source) {
  Node *movenode;

  if (dest == NULL || source == NULL || *source == NULL) {
    return;
  }

  movenode = *source;
  *source = movenode->next;

  movenode->next = *dest;
  *dest = movenode;
}

void AlternatingSplit (Node *source, Node **aRef, Node **bRef) {
  int count = 0;

  if (aRef == NULL || bRef == NULL) {
    return;
  }

  while (source) {
    if (count == 0) {
      MoveNode(aRef, &source);
    } else {
      MoveNode(bRef, &source);
    }

    count ^= 1;
  }
}

Node* ShuffleMerge (Node *a, Node *b) {
  Node *temp, *aRef;

  if (a == NULL) {
    return b;
  } else if (b == NULL) {
    return a;
  }

  aRef = a;

  while (a && b) {
    temp = b;
    b = b->next;

    temp->next = a->next;
    a->next = temp;

    a = temp->next;
  }

  if (b) {
    temp->next = b;
  }

  return aRef;
}

Node* SortedMerge (Node *a, Node *b) {
  if (a == nullptr)
    return b;
  else if (b == nullptr)
    return a;

  Node *prev = nullptr;
  Node *curr = a->data < b->data ? a : b;
  Node *other = (curr == b) ? a : b;

  while (curr && other) {
    if (curr->data < other->data) {
      prev = curr;
      curr = curr->next;
    } else {
      Node *nextnode = other->next;

      other->next = curr;
      prev->next = other;

      curr = other;
      other = nextnode;
    }
  }

  if (other) {
    prev->next = other;
  }

  return a->data < b->data ? a : b;
}

void MergeSort(Node **headRef) {
  Node *left, *right;

  if (headRef && *headRef && (*headRef)->next) {
    FrontBackSplit(*headRef, &left, &right);
    MergeSort(&left);
    MergeSort(&right);

    *headRef = SortedMerge(left, right);
  }
}

void Push (Node **headRef, int data) {
  Node *newnode;

  if (headRef == NULL) {
    return;
  }

  newnode = (Node*) malloc (sizeof(Node));
  newnode->data = data;
  newnode->next = *headRef;
  *headRef = newnode;
}

Node* SortedIntersect (Node *A, Node *B) {
  Node *sortedlist = NULL;

  while (A && B) {
    if (A->data < B->data) {
      A = A->next;
    } else if (A->data > B->data) {
      B = B->next;
    } else {
      Push(&sortedlist, A->data);
      A = A->next;
      B = B->next;
    }
  }

  if (sortedlist) {
    MergeSort(&sortedlist);
  }

  return sortedlist;
}

void Reverse (Node **headRef) {
  Node *curr, *newhead;

  if (headRef == NULL || *headRef == NULL) {
    return;
  }

  curr = (*headRef)->next;
  (*headRef)->next = NULL;

  while (curr) {
    newhead = curr;
    curr = curr->next;

    newhead->next = *headRef;
    *headRef = newhead;
  }
}

void RecursiveReverseWorker(Node **headRef, Node *curr) {
  Node *next;

  if (curr) {
    next = curr->next;

    curr->next = *headRef;
    *headRef = curr;

    RecursiveReverseWorker(headRef, next);
  }
}

void RecursiveReverse (Node **headRef) {
  Node *curr;

  if (headRef == NULL || *headRef == NULL) {
    return;
  }

  curr = (*headRef)->next;
  (*headRef)->next = NULL; /* This is an important step! Linked List bites its own tail without this. */

  RecursiveReverseWorker(headRef, curr);
}

void DeleteUnsortedNodes(Node *node) {
  Node *curr, *prev;

  if (node == NULL || node->next == NULL) {
    return;
  }

  while (node && node->next) {
    prev = node;
    curr = node->next;

    while(curr) {
      if (node->data == curr->data) {
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
      } else {
        prev = curr;
        curr = curr->next;
      }
    }

    node = node->next;
  }
}

int NthToLast(Node *node, unsigned int ntolast) {
  unsigned int size, idx;
  Node *curr;

  if (node == NULL) {
    return -1;
  }

  /* Count the number of items. */
  for(curr = node, size = 0; curr; size++, curr = curr->next);
  if (ntolast > size) {
    return -1;
  }

  curr = node;
  for (idx = 0; idx < size - ntolast; idx++) {
    curr = curr->next;
  }

  return curr->data;
}

/*
1 - 2 - 3 - 4 - 5
2nd to last = 4 ; 3 times = 5 - 2
4th to last = 2 ; 1 time = 5 - 4
*/
unsigned int NthToLastRecursiveWorker(Node *node, unsigned int count, int *data) {
  unsigned int step;

  if (node == NULL) {
    return 1;
  }

  step = NthToLastRecursiveWorker(node->next, count, data);
  if (step == count) {
    *data = node->data;
  }

  return step + 1;
}

int NthToLastRecursive(Node *node, unsigned int count) {
  int data = -1;

  if (node == NULL) {
    return -1;
  }

  NthToLastRecursiveWorker(node, count, &data);
  return data;
}

void DeleteNode (Node **headRef, Node *node) {
  Node *prev, *curr;

  if (headRef == NULL || *headRef == NULL || node == NULL) {
    return;
  }

  prev = NULL;
  curr = *headRef;

  while (curr && curr != node) {
    prev = curr;
    curr = curr->next;
  }

  if (curr) {
    if (prev) {
      prev->next = curr->next;
    } else {
      *headRef = (*headRef)->next;
    }
  }

  /*
   * Penalize the careless programmer if he passes a pointer
   * to a node that doesn't even exist in this list by freeing
   * it mindlessly.
   */
  free(node);
}

// (3 -> 1 -> 5) + (5 -> 9 -> 2)
Node* CreateList(unsigned int sum) {
  Node *head, *newnode;

  if (sum < 10) {
    Node *newlist = (Node*) malloc (sizeof(Node));
    newlist->data = sum;
    newlist->next = NULL;
    return newlist;
  }

  head = CreateList(sum / 10);
  newnode = (Node*) malloc (sizeof(Node));
  newnode->data = sum % 10;
  newnode->next = head;
  return newnode;
}

int LoopNode(Node *node) {
  Node *slow, *fast;

  slow = node;
  fast = node;

  while (fast && fast->next) {
    if (slow == fast)
      break;
    slow = slow->next;
    fast = fast->next->next;
  }

  slow = node;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow->data;

  /* See cracking diagram on page 110. Lets say the loop starts at k steps from start. By the time the slow guy takes k steps to get to the start, the fast guy would have gotten 2k steps ahead. So now in the loop, the fast guy has k steps headstart. With that headstart in a loop of n steps, now they meet after n - k steps, or k steps away from the loop start. Now if you reset the slow guy back to the list head and then move the slow guy and fast guy in single lockstep mode, they meet at the start of the loop after k steps. */
}

Node* ProcessListSum (Node *a, Node *b) {
  unsigned int sum = 0;
  unsigned int degree = 1;

  while (a || b) {
    if (a) {
      sum = sum + a->data * degree;
      a = a->next;
    }
    if (b) {
      sum = sum + b->data * degree;
      b = b->next;
    }
    degree = degree * 10;
  }

  return CreateList(sum);
}

int main()
{
  Node *A = NULL;

  Insert(&A, 9);
  Insert(&A, 8);
  Insert(&A, 7);
  Insert(&A, 6);
  Insert(&A, 5);
  Insert(&A, 4);
  Insert(&A, 3);
  Insert(&A, 2);

  Print(A);
  RecursiveReverse(&A);
  Print(A);

  /*
  C = ProcessListSum(A, B);
  Print(C);
  DeleteNode(&A, A->next->next->next->next);
  DeleteUnsortedNodes(A);
  RecursiveReverse(&A);
  MergeSort(&A);
  FrontBackSplit(A, &B, &C);
  ShuffleMergeRec(A, B);
  AlternatingSplit(head, &A, &B);
  MoveNode(&A, &B);
  RemoveDuplicates(head);
  Append(&First, &Second);
  Print(First);
  printf("Popped item: %d\n", Pop(&head));
  InsertNth(&head, 9, 16);
  DeleteList(&head);
  printf("Item at index %d: %d\n", index, GetNth(head, index));
  printf("%d occurs %d times in this list.\n", searchval, Count(head, searchval));
  Print(head);
  */
  return 0;
}