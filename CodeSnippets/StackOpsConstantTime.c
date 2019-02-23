// Implement a stack that runs in O(1) time for the operations Push(),
// Pop() and FindMin(). You are allowed to use an additional stack as you
// see fit.

// Solution: Use the additional stack to store a chain of minimum items.
// Insert the first item as-is. Every time there's a new Push() operation,
// check if the new item to be inserted is less than the item on the aux stack.
// If yes, then insert. Similarly, if we're popping out the minimum item, then
// pop it out from the aux stack as well, so that aux stack now points to the next
// minimum item, thereby giving us the ability to look up the minimum item at any
// given point in constant time.

#include <iostream>
#include <vector>
using namespace std;

static vector<int> stack;
static vector<int> aux;

int FindMin () {
  if (aux.empty())
    return 0xdeadbeef;

  return aux.back();
}

int Pop() {
  if (stack.empty())
    return 0xdeadbeef;

  if (stack.back() == aux.back())
    aux.pop_back();

  int data = stack.back();
  stack.pop_back();

  return data;
}

void Push (int data) {
  stack.push_back(data);
  cout << "Pushed " << data << endl;

  if (aux.empty()) {
    aux.push_back(data);
    cout << "Also pushed " << data << " onto aux" << endl;
  } else if (data <= aux.back()) {
    aux.push_back(data);
    cout << "Also pushed " << data << " onto aux" << endl;
  }
}

int main () {
  Push (6);
  Push (15);
  Push (18);
  cout << "Minimum is " << FindMin() << endl; // 6
  Push (5);
  Push (7);
  cout << "Minimum is " << FindMin() << endl; // 5
  cout << "Popped " << Pop() << endl; // Popped 7. 6 - 15 - 18 - 5
  cout << "Popped " << Pop() << endl; // Popped 5. 6 - 15 - 18
  cout << "Minimum is " << FindMin() << endl; // 6
  Push (9);
  Push (4);
  Push (12); // 6 - 15 - 18 - 9 - 4 - 12
  cout << "Minimum is " << FindMin() << endl; // 4
  cout << "Popped " << Pop() << endl; // Popped 12. 6 - 15 - 18 - 9 - 4
  cout << "Minimum is " << FindMin() << endl; // 4.
  cout << "Popped " << Pop() << endl; // Popped 4. 6 - 15 - 18 - 9
  cout << "Minimum is " << FindMin() << endl; // 6

  return 0;
}