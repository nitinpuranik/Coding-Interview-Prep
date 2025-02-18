// Find a divider in the array such that the left and right partitions
// have equal sums. Solution: You can start by initializing the left
// sum to arr[0] and right sum to arr[1..n-1]. Then go on placing the
// divider at indexes starting from 1 and proceed by adding elements
// to the left partition and dropping from the right partition.

#include <iostream>
#include <vector>
using namespace std;

int Partition (const vector<int>& arr) {
  if (arr.empty())
    return -1;

  int lsum = arr[0];
  int rsum = 0;

  for (int i = 1; i < (int) arr.size(); i++) {
    rsum += arr[i];
  }

  for (int i = 1; i < (int) arr.size() - 1; i++) {
    if (lsum == rsum) {
      cout << "Sum = " << lsum << endl;
      return i;
    }

    lsum += arr[i];
    rsum -= arr[i];
  }

  return -1;
}

int main() {
  vector<int> arr {2,7,-4,6,3,-8,-10,3,7,4};

  int idx = Partition (arr);
  if (idx != -1)
    cout << "Index = " << idx << endl;
  else
    cout << "No partition." << endl;

  return 0;
}