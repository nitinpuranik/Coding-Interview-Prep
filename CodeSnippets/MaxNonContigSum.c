#include <stdio.h>

void PrintMax (int *arr, int index, int *parent) {
  if (parent[index] == -1) {
    printf("%d", arr[index]);
  } else {
    PrintMax (arr, parent[index], parent);
    printf(" + %d", arr[index]);
  }
}

void MaxSum (int *arr, int n) {
  int i;
  int maxsum, maxindex;
  int sum[n], parent[n];
  
  if (arr == NULL || n <= 0) {
    return;
  }
  
  for (i = 0; i < n; i++) {
    sum[i] = arr[i];
    parent[i] = -1;
  }
  
  maxsum = arr[0];
  maxindex = 0;
  
  for (i = 1; i < n; i++) {
    if (maxsum + arr[i] > arr[i]) {
      sum[i] = maxsum + arr[i];
      parent[i] = maxindex;
    }
    
    if (sum[i] > maxsum) {
      maxsum = sum[i];
      maxindex = i;
    }
  }
  
  PrintMax (arr, maxindex, parent);
}

int main() {
  int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
  
  MaxSum(arr, sizeof(arr)/sizeof(int));
  
  return 0;
}