// Given an array of integers, determine if the array has a clean
// partition such that the sums on both sides of the partition are equal.

// Solution: Start summing up from both ends until the indexes meet. At any
// given point, compare the left and right sums and pick the one with the lower
// sum to increment to the next item. Repeat until indexes meet.

#include <iostream>
#include <vector>
using namespace std;

bool Foo (vector<int>& arr) {
  if (arr.size() <= 1)
    return false;

  int lindex = 0;
  int rindex = arr.size() - 1;

  int lsum = arr[lindex];
  int rsum = arr[rindex];

  while (lindex < rindex) {
    if (lsum == rsum) {
      if (lindex == rindex - 1) {
        cout << "Part at " << lsum << endl;
        return true;
      }
    }

    if (lsum < rsum) {
      lsum += arr[++lindex];
    } else {
      rsum += arr[--rindex];
    }
  }

  return false;
}

int main() {
  vector<int> arr {3,4,2,1,2,3,-1};
  // Solution falls apart for {7,1,-2,10}.

  if (Foo(arr)) {
    cout << "Demarcation exists." << endl;
  } else {
    cout << "Demarcation doesn't exist." << endl;
  }

  return 0;
}