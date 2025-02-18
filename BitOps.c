#include <stdio.h>

/*
 * Example: n = 10(11)01b ; m = 10b ; j = 3; i = 2.
 * Get left = 110000, right = 11. Or them to get 110011.
 * And with n to zero out the positions of interest.
 * So you end up with 100001. Now left shift m by i to
 * get 1000. Or with the above value to get the final answer.
 * 100001 | 1000 = 101001.
 */
unsigned Transform(unsigned n, unsigned m, unsigned i, unsigned j) {
  unsigned ones = ~0;
  unsigned left, right, mask;

  /* Zeroes upto the jth position. Ones after that. */
  left = ones - ((1 << (j + 1)) - 1);
  
  /* Ones upto ith position. */
  right = (1 << i) - 1;
  
  mask = left | right;
  
  return (n & mask) | (m << i);
}

int main() {
  unsigned n = 0x56C, m = 3; // n = 1010(1101)100; m = 0011; j = 6; i = 3; output = 1010(0011)100 = 51C
  unsigned i = 3, j = 6;

  printf("Transformed val: 0x%02X\n", Transform(n, m, i, j));

  return 0;
}