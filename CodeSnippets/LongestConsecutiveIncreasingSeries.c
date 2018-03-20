#include <stdio.h>

void LongestIncreasingSeq (int *arr, int n) {
  int currlen, maxlen;
  int maxind, i;

  if (arr == NULL || n <= 0) {
    return;
  }

  currlen = 1;
  maxlen = 1;
  maxind = 0;

  for (i = 1; i < n; i++) {
    if (arr[i] > arr[i - 1]) {
      currlen++;
    } else {
      if (currlen > maxlen) {
        maxlen = currlen;
        maxind = i - 1;
        currlen = 1;
      }
    }
  }

  /*
   * If you skip this if-conditional, your code
   * will fail the input {2,4,3,5,7,6,9,10,12}
   */
  if (currlen > maxlen) {
    maxlen = currlen;
    maxind = i - 1;
    currlen = 0;
  }

  i = maxind - maxlen + 1;
  printf("{%d", arr[i++]);
  for (; i <= maxind; i++) {
    printf(", %d", arr[i]);
  }

  printf("}\n");
}

int main () {
  int arr[] = {2,4,3,5,7,6,9,10,12,8};

  LongestIncreasingSeq(arr, sizeof(arr)/sizeof(int));

  return 0;
}