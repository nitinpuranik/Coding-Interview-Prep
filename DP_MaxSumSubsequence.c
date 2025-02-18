#include <iostream>
#include <vector>
using namespace std;

// Inferior solution: This is O(n^2) in time complexity.
void MaxContiguousSubsequence_Slow (const vector<int>& arr) {
  if (arr.empty())
    return;

  int maxsum, maxindex;

  maxsum = arr[0];
  maxindex = 0;

  for (unsigned i = 0; i < arr.size(); i++) {
    int currsum = 0;

    for (unsigned j = i; j < arr.size(); j++) {
      currsum += arr[j];

      if (currsum > maxsum) {
        maxsum = currsum;
        maxindex = i;
      }
    }
  }

  cout << maxsum << ": ";
  while (maxsum != 0) {
    cout << arr[maxindex] << ' ';

    maxsum -= arr[maxindex++];
  }

  cout << endl;
}

void PrintSequence (const vector<int>& arr, int sum, int index) {
  if (sum) {
    PrintSequence (arr, sum - arr[index], index - 1);
    cout << arr[index] << ' ';
  }
}

// This is faster and is O(n) in time complexity.
void MaxContiguousSubsequence_Fast (const vector<int>& arr) {
  if (arr.empty())
    return;

  int maxsum, maxindex;
  int currsum;

  maxsum = currsum = arr[0];
  maxindex = 0;

  for (unsigned i = 1; i < arr.size(); i++) {
    currsum += arr[i];

    if (currsum < arr[i]) {
      currsum = arr[i];
    }

    if (maxsum < currsum) {
      maxsum = currsum;
      maxindex = i;
    }
  }

  cout << maxsum << ": ";

  PrintSequence (arr, maxsum, maxindex);

  cout << endl;
}

int main() {
  vector<int> arr {-2, -3, 4, -1, -2, 1, 5, -3};

  MaxContiguousSubsequence_Slow(arr);
  MaxContiguousSubsequence_Fast(arr);

  return 0;
}