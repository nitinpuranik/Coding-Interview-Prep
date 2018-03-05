// If all negatives, then pick the least negative number.

#include <stdio.h>

void PrintMax (int *arr, int index, int *pred) {
  if (pred[index] == -1) {
    printf("%d", arr[index]);
  } else {
    PrintMax (arr, pred[index], pred);
    printf(" + %d", arr[index]);
  }
}

void MaxSum (int *arr, int n) {
  int maxsum, maxindex;
  int pred[n], i;
  
  if (arr == NULL || n <= 0) {
    return;
  }
  
  for (i = 0; i < n; i++) {
    pred[i] = -1;
  }
  
  maxsum = arr[0];
  maxindex = 0;
  
  for (i = 1; i < n; i++) {
    if (arr[i] > 0) {
      if (maxsum > 0) { // If maxsum is positive, then adding arr[i] improves things.
        pred[i] = maxindex;
        maxsum += arr[i];
      } else { // If maxsum is negative, restart the sequence from this positive element.
        maxsum = arr[i];
      }
      
      maxindex = i;
      
    } else if (arr[i] > maxsum) { // If arr[i] is negative, then check if it is still greater than maxsum.
      maxsum = arr[i];
      maxindex = i;
    }
  }
  
  PrintMax (arr, maxindex, pred);
}

int main() {
  int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
  
  MaxSum(arr, sizeof(arr)/sizeof(int));
  
  return 0;
}