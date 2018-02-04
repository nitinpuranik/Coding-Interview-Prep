#include <stdio.h>

// MaxContiguousSubsequence() is a brute-force non-dynamic way of computing the maximum contiguous
// subsequence. This is O(n^2) in time complexity but doesn't need extra space.
void MaxContiguousSubsequence(int *arr, size_t size) {
  unsigned int startindex, endindex;
  unsigned int i,j;
  int currsum, maxsum;
  
  if (arr == NULL) {
    return;
  }

  maxsum = arr[0];
  startindex = endindex = 0;
  
  // Compute the sum of each subarray starting from index zero. Inefficient as there is
  // a lot of repeat summation. However, if you can't afford sparing additional space,
  // go with this approach, trading off speed for space savings.
  for (i = 0; i < size; i++) {
    currsum = 0;

    for (j = i; j < size; j++) {
      currsum = currsum + arr[j];

      if (currsum > maxsum) {
        maxsum = currsum;
        startindex = i;
        endindex = j;
      }
    }
  }
  
  printf("Max consecutive sum = %d.\n", maxsum);
  printf("Occurs between indexes %u and %u.\n", startindex, endindex);
}

// MaxContiguousSubsequenceDynamic() is a dynamic programming way of computing the maximum contiguous subsequence.
// This is faster and is O(n) in time complexity but it does need auxiliary storage on the order of O(n).
void MaxContiguousSubsequenceDynamic (int *arr, size_t size) {
  int maxsum;
  int s[size];
  unsigned int i;
  unsigned int startindex, endindex;
  
  if (arr == NULL || size <= 0) {
    return;
  }

  s[0] = arr[0];
  maxsum = s[0];
  startindex = endindex = 0;
  
  for (i = 1; i < size; i++) {
    if (arr[i] > s[i - 1] + arr[i]) {
      s[i] = arr[i];
      
      if (s[i] > maxsum) {
        maxsum = s[i];
        startindex = endindex = i;
      }
    } else {
      s[i] = s[i - 1] + arr[i];
      
      if (s[i] > maxsum) {
        maxsum = s[i];
        endindex = i;
      }
    }
  }
  
  printf("Max consecutive sum = %d.\n", maxsum);
  printf("Occurs between indexes %u and %u.\n", startindex, endindex);
}

int main() {
  int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
  
  MaxContiguousSubsequence(arr, sizeof(arr)/sizeof(int));
	MaxContiguousSubsequenceDynamic(arr, sizeof(arr)/sizeof(int));
  
  return 0;
}