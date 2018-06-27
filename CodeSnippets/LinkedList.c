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

      prev = other;
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

Node* SortedIntersect (Node *a, Node *b) {
  Node *slist = nullptr;

  while (a && b) {
    if (a->data < b->data) {
      a = a->next;
    }

    else if (b->data < a->data) {
      b = b->next;
    }

    else {
      Insert (&slist, a->data);
      a = a->next;
      b = b->next;
    }
  }

  return slist;
}

// Iterative solution.
void Reverse (Node **head) {
  if (head == nullptr || *head == nullptr)
    return;

  Node *curr = (*head)->next;
  (*head)->next = nullptr;

  while (curr) {
    Node *nextnode = curr->next;
    curr->next = *head;
    *head = curr;

    curr = nextnode;
  }
}

// Recursive helper function.
void __Reverse (Node **head, Node *curr) {
  if (curr) {
    Node *nextnode = curr->next;

    curr->next = *head;
    *head = curr;

    __Reverse (head, nextnode);
  }
}

// Recursive solution.
void Reverse (Node **head) {
  if (head == nullptr || *head == nullptr)
    return;

  Node *curr = (*head)->next;
  (*head)->next = nullptr;

  __Reverse (head, curr);
}