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

class Stack {
  private:
    vector<int> stackv;
    vector<int> minv;

  public:
    void Push (int data);
    int Pop ();
    int FindMin ();
    bool Empty() { return stackv.empty(); }
};

void Stack::Push (int data) {
  stackv.push_back(data);

  if (minv.empty() || data <= minv.back())
    minv.push_back(data);
}

int Stack::Pop () {
  if (stackv.empty())
    throw "Stack empty.";

  int data = stackv.back();
  stackv.pop_back();

  if (data == minv.back())
    minv.pop_back();

  return data;
}

int Stack::FindMin () {
  if (stackv.empty())
    throw "Stack empty.";

  return minv.back();
}

int main () {
  Stack st;

  st.Push (6);
  st.Push (15);
  st.Push (18);
  cout << "Minimum is " << st.FindMin() << endl; // 6
  st.Push (5);
  st.Push (7);
  cout << "Minimum is " << st.FindMin() << endl; // 5
  cout << "Popped " << st.Pop() << endl; // Popped 7. 6 - 15 - 18 - 5
  cout << "Popped " << st.Pop() << endl; // Popped 5. 6 - 15 - 18
  cout << "Minimum is " << st.FindMin() << endl; // 6
  st.Push (9);
  st.Push (4);
  st.Push (12); // 6 - 15 - 18 - 9 - 4 - 12
  cout << "Minimum is " << st.FindMin() << endl; // 4
  cout << "Popped " << st.Pop() << endl; // Popped 12. 6 - 15 - 18 - 9 - 4
  cout << "Minimum is " << st.FindMin() << endl; // 4.
  cout << "Popped " << st.Pop() << endl; // Popped 4. 6 - 15 - 18 - 9
  cout << "Minimum is " << st.FindMin() << endl; // 6

  return 0;
}