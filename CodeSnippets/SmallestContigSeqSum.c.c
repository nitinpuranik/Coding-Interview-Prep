// Given a target sum (28 in our example), find the smallest sequence
// in the given array that sums up to 28. If not found, print so.

#include <stdio.h>

void SmallestContigSequenceSum (int *arr, int n, int target) {
  int minlen, minindex, startindex;
  int sum, index;
  
  minlen = n + 1;
  sum = 0;
  index = startindex = 0;
  
  while (index < n) {
    sum += arr[index];
        
    while (sum > target) {
      sum -= arr[startindex++];
    }
    
    if (sum == target) {
      if (index - startindex + 1 < minlen) {
        minlen = index - startindex + 1;
        minindex = startindex;
      }
    }
    
    index++;
  }
  
  if (minlen <= n) {
    for (index = minindex; index < minindex + minlen; index++) {
      printf("%d ", arr[index]);
    }
  } else {
    printf("Sum not found.\n");
  }
}

int main() {
  int arr[] = {2, 3, 16, 6, 1, 12, 9/*, 27, 1*/ /* 28 */};
    
  SmallestContigSequenceSum (arr, sizeof(arr)/sizeof(int), 28);
  return 0;
}