// Find the longest increasing sequence in the array. The sequence
// doesn't have to be consecutive. This is a dynamic programming problem
// since it has properties of optimal substructure, although they aren't overlapping.
// See Algorithm Design Manual by Steven Skiena for a treatment of this problem.

#include <iostream>
#include <vector>
using namespace std;

void PrintSeq(const vector<int>& arr, const vector<int>& p, int index) {
  if (p[index] != -1) {
    PrintSeq(arr, p, p[index]);
  }

  cout << arr[index] << ' ';
}

void LongestSeq(const vector<int>& arr) {
  if (arr.empty())
    return;

  vector<int> s (arr.size(), 1);    // Length of the longest sequence ending at each item in the array.
  vector<int> p (arr.size(), -1); // Index of predecessor of each item in the array. Needed to print the sequence.
  int maxindex = 0;   // Index of the last item in the longest sequence.

  for (unsigned i = 1; i < arr.size(); i++) {
    /* This is an important optimization. */
    if (arr[i] > arr[maxindex]) { // A simple flip of the comparator and you have the longest decreasing subsequence!
      s[i] = s[maxindex] + 1;
      p[i] = maxindex;
      maxindex = i;
    } else {
      for (unsigned j = 0; j < i; j++) {
        // A simple flip of the comparator and you have the longest decreasing subsequence!
        // Note the <=. If it is just >, then that's a bug. Run the program and see for yourself.
        if (arr[i] > arr[j] && s[i] <= s[j]) {
          s[i] = s[j] + 1;
          p[i] = j;
        }
      }
    }

    // Keep track of the longest sequence seen so far.
    if (s[i] > s[maxindex]) {
      maxindex = i;
    }
  }

  PrintSeq(arr, p, maxindex);
}

int main() {
  vector<int> arr = {2,4,3,5,1,7,10,11,6,9,8};

  LongestSeq(arr);
  return 0;
}