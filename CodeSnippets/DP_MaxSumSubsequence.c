#include <iostream>
#include <vector>
using namespace std;

// MaxContiguousSubsequence() is a brute-force non-dynamic way of computing the maximum contiguous
// subsequence. This is O(n^2) in time complexity but doesn't need extra space.
void MaxContiguousSubsequence (const vector<int>& arr) {
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
  if (sum == 0)
    return;

  PrintSequence (arr, sum - arr[index], index - 1);
  cout << arr[index] << ' ';
}

// MaxContiguousSubsequenceDynamic() is a dynamic programming way of computing the maximum contiguous subsequence.
// This is faster and is O(n) in time complexity but it does need auxiliary storage on the order of O(n).
void MaxContiguousSubsequenceDynamic (const vector<int>& arr) {
  if (arr.empty())
    return;

  int maxsum, maxindex;
  int s[arr.size()];

  maxsum = s[0] = arr[0];
  maxindex = 0;

  for (unsigned i = 1; i < arr.size(); i++) {
    s[i] = arr[i];

    if (s[i - 1] + arr[i] > arr[i]) {
      s[i] = s[i - 1] + arr[i];
    }

    if (s[i] > maxsum) {
      maxsum = s[i];
      maxindex = i;
    }
  }

  cout << maxsum << ": ";

  PrintSequence (arr, maxsum, maxindex);

  cout << endl;
}

int main() {
  vector<int> arr {-2, -3, 4, -1, -2, 1, 5, -3};

  MaxContiguousSubsequence(arr);
  MaxContiguousSubsequenceDynamic(arr);

  return 0;
}