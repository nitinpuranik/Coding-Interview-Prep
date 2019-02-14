// Find the longest increasing sequence in the array. The sequence
// doesn't have to be consecutive. This is a dynamic programming problem
// since it has properties of optimal substructure, although they aren't overlapping.
// See Algorithm Design Manual by Steven Skiena for a treatment of this problem.

#include <iostream>
#include <vector>
using namespace std;

void PrintSeq(const vector<int>& arr, int *pred, int index) {
  if (pred[index] != -1) {

    PrintSeq(arr, pred, pred[index]);

    cout << ", " << arr[index];

  } else {

    cout << arr[index];
  }
}

void LongestSeq(const vector<int>& arr) {
  if (arr.empty())
    return;

  int l[arr.size()] {1};    // Length of the longest sequence ending at each item in the array.
  int pred[arr.size()] {-1}; // Index of predecessor of each item in the array. Needed to print the sequence.
  int maxl = 1;       // Length of the longest increasing sequence.
  int maxindex = 0;   // Index of the last item in the longest sequence.

  for (unsigned i = 1; i < arr.size(); i++) {
    /* This is an important optimization. */
    if (arr[i] > arr[maxindex]) { // A simple flip of the comparator and you have the longest decreasing subsequence!
      l[i] = maxl + 1;
      pred[i] = maxindex;
    } else {
      l[i] = 1;
      pred[i] = -1;

      for (unsigned j = 0; j < i; j++) {
        if (arr[i] > arr[j]) { // A simple flip of the comparator and you have the longest decreasing subsequence!
          // Check if this item extends the longest sequence seen so far for items to its left which are less than this item.
          if (l[j] >= l[i]) { // Note the >=. If it is just >, then that's a bug. Run the program and see for yourself.
            l[i] = l[j] + 1;
            pred[i] = j;
          }
        }
      }
    }

    // Keep track of the longest sequence seen so far.
    if (l[i] > maxl) {
      maxl = l[i];
      maxindex = i;
    }
  }

  cout << "Max Seq: {";
  PrintSeq(arr, pred, maxindex);
  cout << "}" << endl;
}

int main() {
  vector<int> arr = {2,4,3,5,1,7,10,11,6,9,8};

  LongestSeq(arr);
  return 0;
}