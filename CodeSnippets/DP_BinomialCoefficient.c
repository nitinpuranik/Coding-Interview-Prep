#include <iostream>
#include <array>
using namespace std;

/*
 * Find the combinatorial solution of nCk using
 * binomial method. This serves as a nice introduction
 * to the idea of dynamic programming.
 */

int Triangulate(int n, int k) {
  int arr[n + 1][k + 1];

  for (int row = 0; row <= n; row++)
    arr[row][0] = 1;

  for (int col = 1; col <= k; col++)
    arr[col][col] = 1;

  for (int row = 2; row <= n; row++) {
    for (int col = 1; col < row; col++) {
      arr[row][col] = arr[row - 1][col - 1] + arr[row - 1][col];
    }
  }

  return arr[n][k];
}

int main() {
  int n = 5, k = 3;

  cout << n << "C" << k << " = " << Triangulate(n,k) << endl;
  return 0;
}