#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Find the minimum of [same row][prev col], [prev row][prev col] and
// [prev row][same col]. Your table value will be minimum + 1.
unsigned int FindMin(int i, int j, unsigned total, unsigned int tbl[][total]) {
  unsigned int min;

  min = tbl[i][j - 1];

  if (tbl[i - 1][j - 1] < min) {
    min = tbl[i - 1][j - 1];
  }

  if (tbl[i - 1][j] < min) {
    min = tbl[i - 1][j];
  }

  return min;
}

// As we trace back to zero in the memoization table, below are the conventions:
// - Move to the left: Delete the row character.
// - Move to the top: Add the column character.
// - Move diagonally across, no change in value: No-op. Characters are the same.
// - Move diagonally across, value decrements: Substitute row with column character.
void PrintOperations(int rowindex, int colindex, unsigned total, unsigned int tbl[][total],
                     const char *s1, const char *s2) {
  unsigned int min;

  if (rowindex >= 0 && colindex >= 0 && tbl[rowindex][colindex] > 0) {
    min = FindMin (rowindex, colindex, total, tbl);

    if (tbl[rowindex - 1][colindex - 1] == min) {

      PrintOperations(rowindex - 1, colindex - 1, total, tbl, s1, s2);

      // Substitution of s1 to s2.
      if (min == tbl[rowindex][colindex] - 1) {
        printf("Change '%c' in %s to '%c'.\n", s1[colindex - 1], s1, s2[rowindex - 1]);
      }

    } else if (tbl[rowindex][colindex - 1] == min) {

      // Deletion of s1.
      PrintOperations(rowindex, colindex - 1, total, tbl, s1, s2);
      printf("Delete %c from %s.\n", s1[colindex - 1], s1);

    } else if (tbl[rowindex - 1][colindex] == min) {

      // Addition of s2.
      PrintOperations(rowindex - 1, colindex, total, tbl, s1, s2);
      printf("Add '%c' to %s after '%c'.\n", s2[rowindex - 1], s1, s1[colindex - 1]);
    }
  }
}

unsigned int MinEdit (const char *s1, const char *s2, size_t len_s1, size_t len_s2) {
  // abc -> akcd. abc will figure horizontally and akcd vertically.
  // So you'll have 4 columns and 5 rows, one extra entry for NULL.
  unsigned int tbl[len_s2 + 1][len_s1 + 1];
  int i,j;
  unsigned int min;

  // Check for edge cases. If one of the strings is NULL, the
  // minimum edit distance is the length of the other string.
  if (s1 == NULL && s2 == NULL) {
    return 0;
  } else if (s1 == NULL) {
    return strlen(s2);
  } else if (s2 == NULL) {
    return strlen(s1);
  }

  // Initialize all elements to zero.
  for (i = 0; i <= len_s2; i++) {
    for (j = 0; j <= len_s1; j++) {
      tbl[i][j] = 0;
    }
  }

  // Initialize the first column equal to the length of the vertical substring.
  for (i = 1; i <= len_s2; i++) {
    tbl[i][0] = tbl[i - 1][0] + 1;
  }

  // Initialize the first row equal to the length of the horizontal substring.
  for (j = 1; j <= len_s1; j++) {
    tbl[0][j] = tbl[0][j - 1] + 1;
  }

  for (i = 1; i <= len_s2; i++) {
    for (j = 1; j <= len_s1; j++) {
      if (s2[i - 1] == s1[j - 1]) {
        // If the characters are the same, cell value is the value diagonally up.
        tbl[i][j] = tbl[i - 1][j - 1];
      } else {
        // If characters are different, find the minimum of previous cell values.
        tbl[i][j] = FindMin(i, j, len_s1 + 1, tbl) + 1;
      }
    }
  }

  min = tbl[len_s2][len_s1];

  // Print the needed operations going left to right.
  PrintOperations(len_s2, len_s1, len_s1 + 1, tbl, s1, s2);

  return min;
}

int main() {
  const char *s1 = "intentional";
  const char *s2 = "execution";
  
  printf("\nMinimum edit distance: %u\n", MinEdit(s1, s2, strlen(s1), strlen(s2)));
  return 0;
}