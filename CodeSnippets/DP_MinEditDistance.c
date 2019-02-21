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

//=============================================================
// Here's a small variation of the above generic problem. You don't
// have to build an entire table. There are some tests you can run
// to determine if the edit distance is one.
#include <iostream>
#include <vector>
using namespace std;

bool OneEditApart(string& s1, string& s2) {
  string& bigger = s1;
  string& smaller = s2;

  // Determine the bigger and smaller string.
  // We're covered even if the strings are identical in length.
  if (s1.length() < s2.length()) {
    smaller = s1;
    bigger = s2;
  }

  if (bigger.length() - smaller.length() > 1)
    return false;

  // A boolean to track if we saw a difference.
  bool sawdiff = false;

  for (unsigned i = 0,j = 0; i < smaller.length(); i++, j++) {
    if (smaller[i] != bigger[j]) {

      // We've seen a difference before. If we see a difference
      // again, then the edit distance exceeds one. Return false.
      if (sawdiff == true) return false;

      sawdiff = true;

      // Reason for the below i-- decrement:
      // Take for instance 'akc' and 'k'. You check 'a' and 'k'.
      // They're dissimilar. That is one new addition in the smaller
      // string. Now move to the next character in the longer string
      // but stay at the same character in the smaller string. So the
      // below decrement.
      i--;
    }
  }

  // Reason for boolean OR:
  // Take for instance 'kc' and 'k'. You'll exit the loop while
  // sawdiff is still false. This happens if the smaller string
  // is the leftmost substring of the bigger string, falling short
  // of only one character at the very last. "abcde" and "abcd" for example.
  return sawdiff || bigger.length() == smaller.length() + 1;
}

int main() {
  string s1 {"kc" /*Also try ak, kc with k */};
  string s2 {"k" /*Also try ak, kc with k */};

  if (OneEditApart (s1, s2))
    cout << "One edit apart." << endl;
  else
    cout << "Not one edit apart." << endl;

  return 0;
}