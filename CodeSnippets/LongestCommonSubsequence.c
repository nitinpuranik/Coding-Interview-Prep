#include <stdio.h>
#include <string.h>

void PrintSeq (const char *s1, const char *s2, unsigned row, unsigned col, unsigned total, unsigned t[][total]) {
  if (t[row][col]) {
    if (s1[col - 1] == s2[row - 1]) {
      PrintSeq (s1, s2, row - 1, col - 1, total, t);
      printf("%c ", s1[col - 1]);
    } else {
      if (t[row][col] == t[row - 1][col]) {
        PrintSeq (s1, s2, row - 1, col, total, t);
      } else {
        PrintSeq (s1, s2, row, col - 1, total, t);
      }
    }
  }
}

// s1 along columns, s2 along rows.
void LongestCommonSubsequence (const char *s1, const char *s2, size_t len_s1, size_t len_s2) {
  unsigned t[len_s2 + 1][len_s1 + 1];
  unsigned i,j;

  // Init table.
  for (i = 0; i <= len_s1; i++) {
		t[0][i] = 0;
	}

	for (i = 0; i <= len_s2; i++) {
		t[i][0] = 0;
	}

  for (i = 1; i <= len_s2; i++) {
    for (j = 1; j <= len_s1; j++) {
      if (s2[i - 1] == s1[j - 1]) {
        t[i][j] = t[i - 1][j - 1] + 1;
      } else {
        t[i][j] = t[i - 1][j];

        if (t[i][j - 1] > t[i][j]) {
          t[i][j] = t[i][j - 1];
        }
      }
    }
  }

  PrintSeq (s1, s2, len_s2, len_s1, len_s1 + 1, t);
}

int main () {
  char *s1 = "abcdafklg";
  char *s2 = "acbcfmg";

  LongestCommonSubsequence (s1, s2, strlen(s1), strlen(s2));
  return 0;
}