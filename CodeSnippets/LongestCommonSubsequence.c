#include <iostream>
#include <vector>
using namespace std;

void PrintLCS (const string& s1, const string& s2, auto const& tbl, int row, int col) {
  if (tbl[row][col]) {
    if (s2[row - 1] == s1[col - 1]) {
      PrintLCS (s1, s2, tbl, row - 1, col - 1);
      cout << s2[row - 1];
    } else {
      if (tbl[row - 1][col] > tbl[row][col - 1])
        PrintLCS (s1, s2, tbl, row - 1, col);
      else
        PrintLCS (s1, s2, tbl, row, col - 1);
    }
  }
}

// s1 along cols, s2 along rows
void LCS (const string& s1, const string& s2) {
  if (s1.empty() || s2.empty()) {
    cout << "Empty string" << endl;
    return;
  }

  vector<vector<int>> tbl;

  for (unsigned i = 0; i <= s2.length(); i++)
    tbl.push_back({0});

  for (unsigned i = 1; i <= s1.length(); i++)
    tbl[0].push_back(0);

  for (unsigned i = 1; i <= s2.length(); i++) {
    for (unsigned j = 1; j <= s1.length(); j++) {
      if (s2[i - 1] == s1[j - 1]) {
        tbl[i].push_back(tbl[i - 1][j - 1] + 1);
      } else {
        int entry = tbl[i - 1][j] > tbl[i][j - 1] ? tbl[i - 1][j] : tbl[i][j - 1];
        tbl[i].push_back(entry);
      }
    }
  }

  if (tbl[s2.length()][s1.length()] == 0)
    cout << "No LCS" << endl;

  PrintLCS (s1, s2, tbl, tbl.size() - 1, tbl[0].size() - 1);
}

int main() {
  string s1 = "abcdafklg";
  string s2 = "acbcfmg";

  LCS (s1, s2);

  return 0;
}