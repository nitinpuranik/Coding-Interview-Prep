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