/*
 * Given a buffer with indices that are offsets from the current index,
 * determine whether hopping through the indices will take you through
 * the buffer full circle ending at index 0. For example, if arr[0] = 2,
 * it means you need to hop 2 indices further. If arr[2] = -1, then go
 * back one index. If arr[0] = -1, then wrap back and go to the last index.
 * So an array such as {2,2,-1} is a circular array while {2,1,-1} is not.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool IsCircular (const vector<int>& arr) {
  unordered_set<int> visited;

  int index = 0;

  visited.insert(0);

  while(true) {
    index += arr[index];

    if (index < 0) {
      index = (index * (-1)) % arr.size();
      index = arr.size() - index;
    }

    index %= arr.size();

    if (visited.find(index) != visited.end())
      return index == 0;

    visited.insert(index);
  }
}

int main() {
  vector<int> arr {2,-1,-1};
  //vector<int> arr {-7, -10, -1};

  if (IsCircular (arr))
    cout << "Circular buffer." << endl;
  else
    cout << "Not a circular buffer." << endl;

  return 0;
}