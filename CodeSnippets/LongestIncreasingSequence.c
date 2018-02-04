// Find the longest increasing sequence in the array. The sequence
// doesn't have to be consecutive. This is a dynamic programming problem
// since it has properties of optimal substructure, although they aren't overlapping.
// See Algorithm Design Manual by Steven Skiena for a treatment of this problem.

#include <stdio.h>

void PrintSeq(int *arr, int *pred, int index) {
  if (pred[index] != -1) {
  
    PrintSeq(arr, pred, pred[index]);
    
    printf(", %u", arr[index]);
  
  } else {
  
    printf("%u", arr[index]);
  }
}

void LongestSeq(int *arr, int n) {
  int l[n];    // Length of the longest sequence ending at each item in the array.
  int pred[n]; // Index of predecessor of each item in the array. Needed to print the sequence.
  int maxl;       // Length of the longest increasing sequence.
  int maxindex;   // Index of the last item in the longest sequence.
  int i, j;
  
  for (i = 0; i < n; i++) {
    l[i] = 1;
    pred[i] = -1;
  }
  
  maxl = 1;
  maxindex = 0;
  
  for (i = 1; i < n; i++) {
    if (arr[i] > arr[maxindex]) {
      l[i] = maxl + 1;
      maxl = l[i];
      pred[i] = maxindex;
      maxindex = i;
    } else {
      for (j = 0; j < i; j++) {
        if (arr[j] < arr[i]) { // A simple flip of the comparator and you have the longest decreasing subsequence!
          // Check if this item extends the longest sequence seen so far for items to its left which are less than this item.
          if (l[j] >= l[i]) { // Note the >=. If it is just >, then that's a bug. Run the program and see for yourself.
            l[i] = l[j] + 1;
            pred[i] = j;
          }
        }
        
        // Keep track of the longest sequence seen so far.
        if (l[i] > maxl) {
          maxl = l[i];
          maxindex = i;
        }
      }
    }
  }
  
  printf("Max Seq: {");
  PrintSeq(arr, pred, maxindex);
  printf("}\n");
}

int main() {
  int arr[] = {2,4,3,5,1,7,10,11,6,9,8};
  
  LongestSeq(arr, sizeof(arr)/sizeof(int));
  return 0;
}