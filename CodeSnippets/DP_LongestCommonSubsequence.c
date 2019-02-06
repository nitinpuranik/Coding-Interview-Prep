#include <iostream>
#include <vector>
using namespace std;

/*
 * Algorithm: Take two strings - say abcm and acm. Check if the last two characters
 * are the same. If they are, then the length of the subsequence is the LCS of the two
 * strings without the last string, plus one. That is, LCS(abcm, acm) = LCS(abc, ac) + 1.
 * If the last two characters don't match, LCS(abck, acm) = max(LCS(abck, ac), LCS(abc, acm)).
 */

void PrintLCS (const string& s1, const string& s2, auto const& tbl, int row, int col) {
  if (tbl[row][col]) {
    if (s1[row - 1] == s2[col - 1]) {
      PrintLCS (s1, s2, tbl, row - 1, col - 1);
      cout << s1[row - 1];
    } else if (tbl[row - 1][col] > tbl[row][col - 1]) {
      PrintLCS (s1, s2, tbl, row - 1, col);
    } else {
      PrintLCS (s1, s2, tbl, row, col - 1);
    }
  }
}

// s1 along rows, s2 along rows
void LCS (const string& s1, const string& s2) {
  if (s1.empty() || s2.empty()) {
    cout << "Empty string" << endl;
    return;
  }

  vector<vector<int>> tbl;

  for (unsigned i = 0; i <= s1.length(); i++)
    tbl.push_back({0});

  for (unsigned i = 1; i <= s2.length(); i++)
    tbl[0].push_back(0);

  for (unsigned i = 1; i <= s1.length(); i++) {
    for (unsigned j = 1; j <= s2.length(); j++) {
      if (s1[i - 1] == s2[j - 1]) {
        tbl[i].push_back(tbl[i - 1][j - 1] + 1);
      } else {
        int entry = tbl[i - 1][j] > tbl[i][j - 1] ?
                    tbl[i - 1][j] : tbl[i][j - 1];
        tbl[i].push_back(entry);
      }
    }
  }

  if (tbl[s1.length()][s2.length()] == 0)
    cout << "No LCS" << endl;

  PrintLCS (s1, s2, tbl, s1.length(), s2.length());
  cout << endl;

  /*
   * If you'd like to implement your own stack, instead of the
   * runtime's recursion infrastructure, here is the code snippet.
   */
  vector<char> subseq;

  int row = s1.length();
  int col = s2.length();

  while (tbl[row][col]) {
    if (s1[row - 1] == s2[col - 1]) {
      subseq.push_back(s1[row - 1]);
      row--; col--;
    } else if (tbl[row][col - 1] > tbl[row - 1][col]) {
      col--;
    } else {
      row--;
    }
  }

  for (vector<char>::const_reverse_iterator it = subseq.rbegin(); it != subseq.rend(); it++)
    cout << *it;
}

int main() {
  string s1 = "abcdafklg";
  string s2 = "acbcfmg";

  LCS (s1, s2);

  return 0;
}