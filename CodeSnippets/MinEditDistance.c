#include <iostream>
#include <vector>
using namespace std;

// As we trace back to zero in the memoization table, below are the conventions:
// - Move to the left: Add column character.
// - Move to the top: Delete the row character.
// - Move diagonally across, no change in value: No-op. Characters are the same.
// - Move diagonally across, value decrements: Substitute row with column character.
void Print(const auto& tbl, const string& s1, const string& s2, int row, int col) {
  if (tbl[row][col]) {
    if (s1[row - 1] == s2[col - 1]) {
      Print(tbl, s1, s2, row - 1, col - 1);
    } else {
      unsigned min = tbl[row][col - 1] < tbl[row - 1][col] ?
                tbl[row][col - 1] : tbl[row - 1][col];
      min = min < tbl[row - 1][col - 1] ? min : tbl[row - 1][col - 1];

      if (min == tbl[row][col - 1]) {
        Print(tbl, s1, s2, row, col - 1);
        cout << "Add " << s2[col - 1] << " to " << s1 << " after index " << row - 1 << endl;
      } else if (min == tbl[row - 1][col]) {
        Print(tbl, s1, s2, row - 1, col);
        cout << "Delete " << s1[row - 1] << endl;
      } else {
        Print(tbl, s1, s2, row - 1, col - 1);
        cout << "Change " << s1[row - 1] << " to " << s2[col - 1] << endl;
      }
    }
  }
}

unsigned int MinEdit (const string& s1, const string& s2) {
  // abc -> akcd. abc will figure vertically in rows and akcd horizontally in columns.
  // So you'll have 4 rows and 5 columns, one extra entry for NULL.

  // Check for edge cases. If one of the strings is NULL, the
  // minimum edit distance is the length of the other string.
  if (s1.empty() || s2.empty()) {
    return s1.empty() ? s2.size() : s1.size();
  }

  vector<vector<unsigned>> tbl;

  // Initialize the first column equal to the length of the vertical substring.
  for (unsigned row = 0; row <= s1.length(); row++) {
    tbl.push_back({row});
  }

  // Initialize the first row equal to the length of the horizontal substring.
  for (unsigned col = 1; col <= s2.length(); col++) {
    tbl[0].push_back(col);
  }

  // Initialize the first row equal to the length of the horizontal substring.
  for (unsigned j = 1; j <= s1.length(); j++) {
    tbl[0][j] = tbl[0][j - 1] + 1;
  }

  for (unsigned row = 1; row <= s1.length(); row++) {
    for (unsigned col = 1; col <= s2.length(); col++) {
      if (s1[row - 1] == s2[col - 1]) {
        tbl[row].push_back(tbl[row - 1][col - 1]);
      } else {
        unsigned min = tbl[row][col - 1] < tbl[row - 1][col] ?
                  tbl[row][col - 1] : tbl[row - 1][col];
        min = min < tbl[row - 1][col - 1] ? min : tbl[row - 1][col - 1];
        tbl[row].push_back(min + 1);
      }
    }
  }

  Print(tbl, s1, s2, s1.length(), s2.length());
  return tbl[s1.length()][s2.length()];
}

int main() {
  string s1 = "intentional";
  string s2 = "execution";

  cout << MinEdit(s1, s2) << endl;
  return 0;
}