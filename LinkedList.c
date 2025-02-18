#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
};

void Print (Node *node) {
  while (node) {
    cout << node->data << ' ';
    node = node->next;
  }

  cout << endl;
}

void Insert (Node **head, int data) {
  if (head) {
    Node *newnode = new (nothrow) Node {data, *head};

    if (newnode)
      *head = newnode;
  }
}

unsigned int Count (Node *list, int data) {
  unsigned count {0};

  while (list) {
    if (list->data == data)
      count++;

    list = list->next;
  }

  return count;
}

int GetNth (Node *node, int index) {
  while (node && index > 0) {
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

int Pop (Node **head) {
  if (head == nullptr || *head == nullptr)
    return 0xdeadbeef;

  int data = (*head)->data;
  Node *node = *head;

  *head = (*head)->next;
  delete node;

  return data;
}

void Insert (Node **head, int index, int data) {
  if (head == nullptr || index < 0)
    return;

  Node *curr = *head;
  Node *prev = nullptr;

  while (curr && index > 0) {
    prev = curr;
    curr = curr->next;
    index--;
  }

  if (index == 0) {
    Node *newnode = new Node {data, curr};

    if (prev) {
      prev->next = newnode;
    } else {
      *head = newnode;
    }
  }
}

void SortedInsert (Node **head, Node *newnode) {
  if (head == nullptr || newnode == nullptr) {
    return;
  }

  Node *prev = nullptr;
  Node *curr = *head;

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

  if (head == nullptr || *head == nullptr) {
    return;
  }

  curr = *head;
  *head = nullptr;

  while (curr) {
    newnode = curr;
    curr = curr->next;

    SortedInsert(head, newnode);
  }
}

void Append (Node **A, Node **B) {
  if (A == nullptr || B == nullptr || *B == nullptr) {
    return;
  }

  Node *curr = *A;

  while (curr && curr->next) {
    curr = curr->next;
  }

  if (curr) {
    curr->next = *B;
  } else {
    *A = *B;
  }

  *B = nullptr;
}

/* Have a one node jumping slow pointer and two node jumping fast pointer. */
void FrontBackSplit (Node *source, Node **frontRef, Node **backRef) {
  Node *fast, *slow;

  if (source == nullptr || frontRef == nullptr || backRef == nullptr) {
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
  slow->next = nullptr;
}

void RemoveDuplicates (Node *head) {
  while (head && head->next) {
    if (head->data == head->next->data) {
      Node *delnode = head->next;

      head->next = delnode->next;

      delete delnode;
    } else {
      head = head->next;
    }
  }
}

void MoveNode (Node **dest, Node **source) {
  Node *movenode;

  if (dest == nullptr || source == nullptr || *source == nullptr) {
    return;
  }

  movenode = *source;
  *source = movenode->next;

  movenode->next = *dest;
  *dest = movenode;
}

void AlternatingSplit (Node *source, Node **aRef, Node **bRef) {
  int count = 0;

  if (aRef == nullptr || bRef == nullptr) {
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

  // Alternate, advanced way of doing this:
  if (source == nullptr || aRef == nullptr || bRef == nullptr)
    return;

  while (source) {
    // This works because MoveNode takes care of moving your source pointer forward.
    MoveNode (aRef, &source);
    MoveNode (bRef, &source);
  }
}

Node* ShuffleMerge (Node *a, Node *b) {
	Node head {0xdead, nullptr};
	Node *tail (&head);

	while (a && b) {
		tail->next = a;
		tail = a;
		a = a->next;

		tail->next = b;
		tail = b;
		b = b->next;
	}

	tail->next = a ? a : b;
	return head.next;
}

// If using the above MoveNode, then your ShuffleMerge would look like this:
Node* ShuffleMerge (Node *a, Node *b) {
  Node *shuffle = nullptr;

  while (a && b) {
    MoveNode (&shuffle, &a);
    MoveNode (&shuffle, &b);
  }

  while (a)
    MoveNode (&shuffle, &a);

  while (b)
    MoveNode (&shuffle, &b);

  return shuffle;
}

// A real cool recursive way of ShuffleMerge is here:
Node *ShuffleMerge (Node *a, Node *b) {
  if (a == nullptr || b == nullptr)
    return a ? a : b;

  b->next = ShuffleMerge (a->next, b->next);
  a->next = b;

  return a;
}

Node* SortedMerge (Node* a, Node* b) {
    Node head {0xffff, nullptr};
    Node* tail {&head};

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    tail->next = a ? a : b;
    return head.next;
}

// Cool recursive SortedMerge
Node *SortedMerge (Node *a, Node *b) {
  if (a == nullptr || b == nullptr)
    return a ? a : b;

  if (a->data < b->data) {
    b->next = SortedMerge (a->next, b->next);
    a->next = b;
    return a;
  } else {
    a->next = SortedMerge (a->next, b->next);
    b->next = a;
    return b;
  }
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
  if (headRef == nullptr) {
    return;
  }

  Node* newnode = new Node {data, *headRef};
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
void Reverse (Node **headRef) {
    if (headRef == nullptr) {
        return;
    }

    Node* newlist {nullptr};

    while (*headRef) {
        Node* next = (*headRef)->next;
        (*headRef)->next = newlist;
        newlist = *headRef;
        *headRef = next;
    }

    *headRef = newlist;
}

void RecursiveReverseWorker (Node **headRef, Node *node) {
  if (node) {
    Node *nextnode = node->next;
    node->next = *headRef;
    *headRef = node;

    RecursiveReverseWorker (headRef, nextnode);
  }
}

void RecursiveReverse (Node **headRef) {
  if (headRef == nullptr)
    return;

  Node *node = *headRef;
  *headRef = nullptr;

  RecursiveReverseWorker (headRef, node);
}

// ===========================================================
// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

// k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

// Example:
// Given this linked list: 1->2->3->4->5

// For k = 2, you should return: 2->1->4->3->5
// For k = 3, you should return: 3->2->1->4->5

ListNode* reverseKGroup(ListNode* head, int k) {
	ListNode* curr {head};
    int count {k};

    while (curr && count) {
        curr = curr->next;
        count--;
    }

    if (count) {
        return head;
    }

    ListNode* newnext = reverseKGroup(curr, k);
    
    ListNode* newhead {nullptr};
    ListNode* oldhead {head};

    while (head != curr) {
        ListNode* next = head->next;
        head->next = newhead;
        newhead = head;
        head = next;
    }

    oldhead->next = newnext;

    return newhead;
}