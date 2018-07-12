// Given a target sum (28 in our example), find the smallest sequence
// in the given array that sums up to 28. If not found, print so.

#include <stdio.h>

void SmallestContigSequenceSum (int *arr, int n, int target) {
  int minlen, minindex, sum;
  int startindex, endindex;

  sum = 0;
  minlen = n + 1;
  startindex = endindex = 0;

  while (endindex < n) {
    sum += arr[endindex];

    while (sum > target) {
      sum -= arr[startindex++];
    }

    if (sum == target) {
      if (endindex - startindex + 1 < minlen) {
        minlen = endindex - startindex + 1;
        minindex = startindex;
      }
    }

    endindex++;
  }

  if (minlen <= n) {
    for (int i = 0; i < minlen; i++) {
      printf("%d ", arr[minindex++]);
    }
  } else {
    printf("Sum not found.\n");
  }
}

int main() {
  int arr[] = {2, 3, 16, 6, 1, 12, 9/*, 27, 1*/ /* 28 */};
  //int arr[] = {2, 3, 16, 6, 1, 12, 9, 27, 0, 1};

  SmallestContigSequenceSum (arr, sizeof(arr)/sizeof(int), 28);
  return 0;
}