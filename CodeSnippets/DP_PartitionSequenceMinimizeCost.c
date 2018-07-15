#include <stdio.h>

// Given an array {300 100 200 400 700}, partition the array into three parts without
// shuffling around the array items such that the array is partitioned as evenly as possible.
// It means that you should aim at minimizing the maximum sum of partitions. In the given example,
// the three partitions would be: {300 100 200} | {400} | {700}. Here the maximum sum of partitions is for the
// third partition - 700. You cannot find a three-partition configuration with the maximum partition sum less than that.

// See "Algorithm Design Manual" by Steven Skiena. The chapter on Dynamic Programming discusses this problem in detail.

void PrintDividers (int *arr, unsigned int n, unsigned int k, unsigned int *positions) {
  unsigned int i, j, index;

  index = 0;
  j = 0;
  
  for (i = 0; i < k - 1; i++) {

    for (; j <= positions[i]; j++) {
      printf("%d  ", arr[index++]);
    }

    printf("|  ");
  }
  
  // Last divider printed. Print the rest of the array to the right of it.
  while (index < n) {
    printf("%d  ", arr[index++]);
  }
  
  printf("\n");
}

// Function parameters:
// arr - The array that we are partitioning.
// n   - The size of the array. Also, the number of columns in the below sample DP table.
// k   - The number of desired partitions. Also, the number of rows in the below sample DP table.

// Example: Given an array {300 100 200 400 700}, partition the array into three parts such that maximum sum of the partition is minimized.
// Solution: {300 100 200} | {400} | {700}. Here maximum sum of the partition is 700.
// Just as an illustration, {300 100} | {200} | {400 700} is not a solution because the maximum sum here is 400 + 700 = 1100 and we can do
// better than that.

// The recurrence relation to solve this DP problem looks like this:
                         
// Least Possible Maxsum =      Minimum      Max (Least possible maxsum to the left of divider at i, summation of items to the right of divider at i.)
//                          i = 0 to (n - 1)

// For the example array {300 100 200 400 700}, below is the dynamic programming (DP) table that is built by this recurrence relation.
// Rows are the number of partitions and columns are the items in the array.
//   | 300 | 100 | 200 | 400  | 700
// ---------------------------------
// 1 | 300 | 400 | 600 | 1000 | 1700
// ---------------------------------
// 2 | 300 | 300 | 300 | 600  | 1000
// ---------------------------------
// 3 | 300 | 300 | 300 | 400  | 700

void PartitionArray (int *arr, unsigned int n, unsigned int k) {
  int cost[k][n];
  int mincost, maxcost;
  int prefixsum[n];
  unsigned int positions[k - 1];
  unsigned int i, j, z;

  prefixsum[0] = arr[0];

  for (i = 1; i < n; i++) {
    prefixsum[i] = prefixsum[i - 1] + arr[i];
  }

  // prefixsum becomes the first row (i.e., one partition) of the DP table because that is one of the base cases.
  // If you are looking for only one partition, then the array sum upto the given array item is your maximum partition sum.
  for (i = 0; i < n; i++) {
    cost[0][i] = prefixsum[i];
  }

  // This is another base case. If you only have one element in your array, no matter how many partitions you need, you only
  // get one partition. The maxsum of this partition is nothing but the first item itself. This becomes the first column of the DP.
  for (i = 0; i < k; i++) {
    cost[i][0] = arr[0];
  }

  for (i = 1; i < k; i++) {

    for (j = 1; j < n; j++) {

      mincost = cost[i][0];

      for (z = 0; z < j; z++) {

        // The body of this loop is the meat of the recurrence relation. We evaluate the maxcost for each
        // of the 'z' possible placements of the 'i'th divider and pick the minimum of all possibilities.
        maxcost = cost[i - 1][z] > (p[j] - p[z]) ? cost[i - 1][z] : (p[j] - p[z]);

        if (maxcost < mincost) {
          mincost = maxcost;
          positions[i - 1] = z;
        }
      }
    }
  }

  PrintDividers (arr, n, k, positions);
}

int main() {
  int arr[] = {300, 100, 200, 400, 700};
  unsigned int k = 2;

  PartitionArray(arr, sizeof(arr)/sizeof(int), k);

  return 0;
}