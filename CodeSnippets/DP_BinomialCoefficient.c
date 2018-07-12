#include <stdio.h>

unsigned long Triangulate(unsigned int n, unsigned int k) {
  unsigned long Pascal[n + 1][k + 1];
  unsigned int row, col;

  /* Initialize the row base case. */
  for (row = 0; row <= n; row++) {
    Pascal[row][0] = 1;
  }

  /* Initialize the column base case. */
  for (col = 0; col <= k; col++) {
    Pascal[col][col] = 1;
  }

  /* Compute the combination now. */
  for (row = 2; row <= n; row++) {
    for(col = 1; col < row; col++) {
      Pascal[row][col] = Pascal[row - 1][col - 1] + Pascal[row - 1][col];
    }
  }
  
  return Pascal[n][k];
}

int main() {
  unsigned int n = 5,k = 3;
  
  printf("%uC%u: %lu\n", n,k, Triangulate(n,k));
  return 0;
}