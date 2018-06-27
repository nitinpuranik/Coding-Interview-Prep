// C++ Implementations of problems in 'Cracking the Coding Interview'.

// Pending Problems: 1.6

/*********************************
* Chapter 1: Arrays and Strings. *
*********************************/
// 1.3 : Without using additional storage.
void RemoveUnique (char *str) {
  if (str == nullptr)
    return;

  if (strlen(str) < 2)
    return;

  unsigned tail = 1;

  for (unsigned i = 1; i < strlen(str); i++) {
    unsigned j;

    // Is str[i] a unique character? Can you replace tail with it?
    for (j = 0; j < tail; j++) {
      if (str[i] == str[j])
        break; // str[i] is not unique. It repeats somewhere in 0 <= j < tail.
    }

    // j == tail means you did not break from the above loop. So str[i] is unique.
    // Replace tail with it.
    if (j == tail) {
      str[tail] = str[i];
      tail++;
    }
  }

  str[tail] = 0;
}

// 1.3 : The above problem with additional storage.
void RemoveUnique (char *str) {
  bool table[256] {false};
  unsigned len;

  {
    char *temp = str;
    len = 0;

    while (*temp++) len++;
  }

  if (len < 2)
    return;

  unsigned tail = 1;
  unsigned char idx = str[0];
  table[idx] = true;

  for (unsigned i = 1; i < len; i++) {
    idx = str[i];

    if (table[idx] == false) {
      str[tail] = str[i];
      tail++;

      table[idx] = true;
    }
  }

  str[tail] = 0;
}

// 1.4
bool Anagram (string& str1, string& str2) {
  if (str1.length() != str2.length())
    return false;

  unsigned long hashtable[256] {0};

  for (unsigned i = 0; i < str1.length(); i++) {
    unsigned char idx = str1[i];
    hashtable[idx]++;

    idx = str2[i];
    hashtable[idx]--;
  }

  for (unsigned long item : hashtable) {
    if (item > 0) {
      return false;
    }
  }

  return true;
}

// 1.5
const char* ReplaceSpace (char *str) {
  unsigned strlen = 0;
  unsigned spaces = 0;

  {
    char *temp = str;

    while (*temp) {
      strlen++;

      if (*temp++ == ' ')
        spaces++;
    }
  }

  if (spaces == 0)
    return nullptr;

  char *newstr = new char[strlen + spaces * 2 + 1];
  char *temp = newstr;

  while (*str) {
    if (*str == ' ') {
      *temp++ = '%';
      *temp++ = '2';
      *temp++ = '0';
    } else {
      *temp++ = *str;
    }

    str++;
  }

  *temp = 0;

  return newstr;
}

// 1.7
void MakeZeroes (vector<vector<int>>& matrix) {
  unsigned rowlen = matrix.size();
  unsigned collen = matrix[0].size();

  bool rows[matrix.size()] {false};
  bool cols[matrix[0].size()] {false};

  for (unsigned i = 0; i < rowlen; i++) {
    for (unsigned j = 0; j < collen; j++) {
      if (matrix[i][j] == 0) {
        rows[i] = cols[j] = true;
      }
    }
  }

  for (unsigned i = 0; i < rowlen; i++) {
    for (unsigned j = 0; j < collen; j++) {
      if (rows[i] || cols[j])
        matrix[i][j] = 0;
    }
  }

  for (unsigned i = 0; i < rowlen; i++) {
    for (unsigned j = 0; j < collen; j++) {
      cout << matrix[i][j] << ' ';
    }
    cout << endl;
  }
}

void Foo (vector<vector<int>>& matrix) {
  cout << matrix.size() << endl;
  cout << matrix[0].size() << endl;
}

int main() {
  vector<vector<int>> matrix = {
                                {1,2,3,4,5},
                                {8,4,9,3,8},
                                {9,2,7,7,3},
                                {3,2,3,0,7},
                                {1,4,3,9,8},
                                {5,4,3,6,6}
                               };

  MakeZeroes (matrix);

  return 0;
}

/*********************************
* Chapter 2: Linked Lists.       *
*********************************/
// 2.1 : Using a hashset to check for duplicates.
void RemoveDuplicates (Node *node) {
  unordered_set<int> hashtable;
  Node *prev = nullptr;

  while (node) {
    if (hashtable.find(node->data) != hashtable.end()) {
      Node *delnode = node;

      prev->next = node->next;
      node = node->next;

      delete delnode;

    } else {
      hashtable.insert(node->data);
      prev = node;
      node = node->next;
    }
  }
}

// 2.1 : Without hashset.
void RemoveDuplicates (Node **head) {
  if (head == nullptr || *head == nullptr || (*head)->next == nullptr)
    return;

  Node *prev = *head;
  Node *curr = prev->next;

  while (curr) {
    Node *runner = *head;

    while (runner != curr) {
      if (runner->data == curr->data) {
        Node *delnode = curr;
        prev->next = curr->next;
        curr = curr->next;

        delete delnode;
        break;
      }

      runner = runner->next;
    }

    if (runner == curr) {
      prev = curr;
      curr = curr->next;
    }
  }
}

// 2.2 : Recursive solution.
int NthToLast (Node *node, int n) {
  if (node == nullptr) {
    cout << "Invalid parameter." << endl;
    return 0;
  }

  if (node->next == nullptr) {
    if (n == 1) {
      cout << n << "th to last element: " << node->data << endl;
      return 0;
    } else {
      return 2;
    }
  }

  int ret = NthToLast (node->next, n);


  if (ret == n) {
    cout << n << "th to last element: " << node->data << endl;
    ret = 0;
  } else if (ret > 0) {
    ret++;
  }

  return ret;
}

// 2.2 : Iterative solution.
Node* NthToLast (Node *node, int n) {
  if (node == nullptr || n <= 0)
    return nullptr;

  Node *p1 = node;
  Node *p2 = node;

  for (int i = n - 1; i > 0; i--) {
    if (p2->next)
      p2 = p2->next;
    else
      return nullptr;
  }

  while (p2->next) {
    p1 = p1->next;
    p2 = p2->next;
  }

  return p1;
}

int main () {
  Node *node = nullptr;

  Insert (&node, 4);
  Insert (&node, 1);
  Insert (&node, 9);
  Insert (&node, 2);
  Insert (&node, 3);
  Insert (&node, 9);
  Insert (&node, 1);
  Insert (&node, 7);
  Insert (&node, 2);
  Insert (&node, 3);
  Insert (&node, 1);

  Print (node);

  int n = 12;
  Node *nth;
  if ((nth = NthToLast(node, n)) != nullptr)
    cout << n << "th to last element: " << nth->data << endl;
  else
    cout << "Not found." << endl;

  return 0;
}

// 2.4
typedef struct node {
  long data;
  struct node *next;
} Node;

Node* InsertTail (Node **root, Node *tail, long data) {
  if (root == nullptr)
    return nullptr;

  Node *newnode = new Node;
  newnode->data = data;
  newnode->next = nullptr;

  if (*root == nullptr) {
    *root = newnode;
    tail = newnode;
  } else {
    tail->next = newnode;
    tail = newnode;
  }

  return tail;
}

void Insert (Node **node, long data) {
  if (node == nullptr)
    return;

  Node *newnode = new Node;
  newnode->data = data;
  newnode->next = *node;
  *node = newnode;
}

Node* AddLists (Node *a, Node *b) {
  Node *SumList = nullptr;
  long carry = 0;

  while (a && b) {
    long sum = a->data + b->data + carry;

    Insert (&SumList, sum % 10);
    carry = sum / 10;

    a = a->next;
    b = b->next;
  }

  while (a) {
    long sum = a->data + carry;
    Insert (&SumList, sum % 10);
    carry = sum / 10;
    a = a->next;
  }

  while (b) {
    long sum = b->data + carry;
    Insert (&SumList, sum % 10);
    carry = sum / 10;
    b = b->next;
  }

  if (carry > 0) {
    Insert (&SumList, carry);
  }

  return SumList;
}

int main() {
  Node *a = nullptr;
  Node *b = nullptr;
  Node *tail = nullptr;

  tail = InsertTail (&a, tail, 9);
  tail = InsertTail (&a, tail, 9);

  tail = InsertTail (&b, tail, 9);
  tail = InsertTail (&b, tail, 9);
  tail = InsertTail (&b, tail, 9);
  tail = InsertTail (&b, tail, 9);

  Node *SumList = AddLists (a, b);

  while (SumList) {
    cout << SumList->data << ' ';
    SumList = SumList->next;
  }

  return 0;
}

// 2.5
// See the diagram for problem 2.5. Lets say the loop starts at k steps from the first node. By the time the slow guy takes k steps to get to the start of the loop, the fast guy would have gotten 2k steps ahead. So now in the loop, the fast guy has k steps headstart. With that headstart in a loop of n steps, they meet after the slow guy takes n - k steps, or k steps away from the loop start. Now if you reset the slow guy back to the list head and then move the slow guy and fast guy in single lockstep mode, they meet at the start of the loop after k steps.
void DetectCycle (Node *node) {
  Node *slow = node;
  Node *fast = node;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
      break;
  }

  if (fast && fast->next) {
    slow = node;

    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }

    cout << "Cycle at " << slow->data;
  } else {
    cout << "No cycle";
  }
}

/*********************************
* Chapter 3: Stacks and Queues. *
*********************************/
// 3.2
class Stack {
  private:
    vector<long> stack;
    vector<long> trackstack;

  public:
    void Push (long data) {
      stack.push_back(data);

      if (trackstack.empty() || data <= trackstack.back()) {
        trackstack.push_back(data);
      }
    }

    long Top () {
      return stack.back();
    }

    void Pop () {
      if (stack.empty())
        return;

      if (stack.back() == trackstack.back()) {
        trackstack.pop_back();
      }

      stack.pop_back();
    }

    long Min () {
      return trackstack.back();
    }
};

int main() {
  Stack s;

  //s.Push(0);
  s.Push(4);
  s.Push(5);
  s.Push(7);
  s.Push(9);
  s.Push(2);
  s.Push(3);

  s.Pop();
  s.Pop();
  cout << s.Top() << endl;
  cout << s.Min();

  return 0;
}