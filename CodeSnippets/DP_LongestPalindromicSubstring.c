// Find the longest palindromic substring in the given string.
// Build out the table's upper triangle starting with 1's across the
// diagonal. Then build out the next line of diagonal for two adjacent
// characters that are the same (insert 2). Then use the below recurrence relation:
// t[i][j] = 0 if s[i] != s[j]. t[i][j] = t[i + 1][j - 1] if s[i] == s[j] && t[i + 1][j - 1] != 0.
// Maintain a tracker for maxlength and the corresponding index.

#include <iostream>
using namespace std;

void LPS (const string& str) {
  if (str.empty())
    return;

  int length = 1;
  unsigned idx = 0;

  int tbl[str.length()][str.length()];

	// First diagonal.
  for (unsigned i = 0; i < str.length(); i++)
    tbl[i][i] = 1;

	// Second diagonal to the right of the first.
  for (unsigned i = 1; i < str.length(); i++) {
    if (str[i - 1] == str[i]) {
      tbl[i - 1][i] = 2;

      length = 2;
      idx = i - 1;
    }
    else {
      tbl[i - 1][i] = 0;
    }
  }

  for (unsigned k = 2; k < str.length(); k++) {
    for (unsigned i = 0, j = k; j < str.length(); i++, j++) {
      tbl[i][j] = 0;

      if (str[i] == str[j] && tbl[i + 1][j - 1]) {
        tbl[i][j] = tbl[i + 1][j - 1] + 2;

        if (tbl[i][j] > length) {
          length = tbl[i][j];
          idx = i;
        }
      }
    }
  }

  cout << str.substr(idx, length);
}

int main() {
  LPS ("forgeeksskeegfor" /* LPS(banana) = anana */);
  return 0;
}