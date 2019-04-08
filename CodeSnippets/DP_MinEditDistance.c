#include <iostream>
#include <vector>
using namespace std;

// As we trace back to zero in the memoization table, below are the conventions:
// - Move to the left: Add column character.
// - Move to the top: Delete the row character.
// - Move diagonally across, no change in value: No-op. Characters are the same.
// - Move diagonally across, value decrements: Substitute row with column character.
void Print(const vector<vector<int>>& tbl, const string& s1, const string& s2, int row, int col) {
  if (tbl[row][col]) {
    if (s1[row - 1] == s2[col - 1]) {
      Print(tbl, s1, s2, row - 1, col - 1);
    } else {
      int min = tbl[row][col - 1] < tbl[row - 1][col] ?
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

int MinEdit (const string& s1, const string& s2) {
  // abc -> akcd. abc will figure vertically in rows and akcd horizontally in columns.
  // So you'll have 4 rows and 5 columns, one extra entry for NULL.

  // Check for edge cases. If one of the strings is NULL, the
  // minimum edit distance is the length of the other string.
  if (s1.empty() || s2.empty()) {
    return s1.length() > 0 ? s1.length() : s2.length();
  }

  vector<vector<int>> arr (s1.length() + 1, vector<int> (s2.length() + 1, 0));

  for (unsigned i = 1; i <= s1.length(); i++) {
    arr[i][0] = i;
  }

  for (unsigned i = 1; i <= s2.length(); i++) {
    arr[0][i] = i;
  }

  for (unsigned i = 1; i <= s1.length(); i++) {
    for (unsigned j = 1; j <= s2.length(); j++) {
      arr[i][j] = arr[i - 1][j - 1];

      if (s1[i - 1] != s2[j - 1]) {
        if (arr[i][j - 1] < arr[i][j])
          arr[i][j] = arr[i][j - 1];

        if (arr[i - 1][j] < arr[i][j])
          arr[i][j] = arr[i - 1][j];

        arr[i][j]++;
      }
    }
  }

  Print(arr, s1, s2, s1.length(), s2.length());
  return arr[s1.length()][s2.length()];
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

bool OneEditApart (const string& s1, const string& s2) {
  if (s1 == s2)
    return false;

  if (abs(int(s1.length() - s2.length())) > 1)
    return false;

  // A boolean to track if we saw a difference.
  bool sawdiff = false;

  for (unsigned i = 0, j = 0; i < s1.length() && j < s2.length();) {
    if (s1[i] == s2[j]) {
      i++; j++;
    }

    else if (sawdiff == true)
        return false;

    else {
      // We've seen a difference before. If we see a difference
      // again, then the edit distance exceeds one. Return false.
      sawdiff = true;

      // Reason for the below selective increment:
      // Take for instance 'akc' and 'k'. You check 'a' and 'k'.
      // They're dissimilar. That is one new addition in the smaller
      // string. Now move to the next character in the longer string
      // but stay at the same character in the smaller string. So the
      // below increment in the bigger string.
      if (s1.length() > s2.length())
        i++;
      else
        j++;
    }
  }

  // Reason for boolean OR:
  // Take for instance 'kc' and 'k'. You'll exit the loop while
  // sawdiff is still false. This happens if the smaller string
  // is the leftmost substring of the bigger string, falling short
  // of only one character at the very last. "abcde" and "abcd" for example.
  return sawdiff || s1.length() != s2.length();
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