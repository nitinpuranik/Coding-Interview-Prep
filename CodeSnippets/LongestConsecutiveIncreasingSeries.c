#include <stdio.h>

void LongestIncreasingSeq (int *arr, int n) {
  int currlen, maxlen;
  int maxindex, i;

  if (arr == NULL || n <= 0) {
    return;
  }

  currlen = maxlen = 1;
  maxindex = 0;

  for (i = 1; i < n; i++) {
    if (arr[i] >= arr[i - 1]) {
      currlen++;
    } else {
      if (currlen > maxlen) {
        maxlen = currlen;
        maxindex = i - 1;
        currlen = 1;
      }
    }
  }

  i = maxindex - maxlen + 1;
  printf("{%u", arr[i++]);

  for (; i <= maxindex; i++) {
    printf(", %u", arr[i]);
  }

  printf("}\n");
}

int main () {
  int arr[] = {2,4,3,5,7,6,9,10,12,8};

  LongestIncreasingSeq(arr, sizeof(arr)/sizeof(int));

  return 0;
}