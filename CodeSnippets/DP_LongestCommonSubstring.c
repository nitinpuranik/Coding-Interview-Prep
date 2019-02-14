#include <iostream>
#include <vector>
using namespace std;

/*
 * Algorithm: LCS (s1[i], s2[j]) = 0 if s1[i] != s2[j].
 * LCS (s1[i], s2[j]) = LCS (s1[i - 1], s2[j - 1]) + 1 if s1[i] == s2[j].
 */
void LCS (const string& s1, const string& s2) {
  if (s1.empty() || s2.empty())
    return;

  int maxlen = 0;
  int maxindex;

  vector<vector<int>> tbl;

  for (unsigned row = 0; row <= s1.length(); row++)
    tbl.push_back({0});

  for (unsigned col = 1; col <= s2.length(); col++)
    tbl[0].push_back(0);

  for (unsigned row = 1; row <= s1.length(); row++) {
    for (unsigned col = 1; col <= s2.length(); col++) {

      int entry = 0;

      if (s1[row - 1] == s2[col - 1]) {
        entry = tbl[row - 1][col - 1] + 1;

        if (entry > maxlen) {
          maxlen = entry;
          maxindex = row - 1;
        }
      }

      tbl[row].push_back(entry);
    }
  }

  for (int index = maxindex - maxlen + 1; index <= maxindex; index++)
    cout << s1[index];
}

int main() {
  string s1 = "abcdaf";
  string s2 = "zbcdf";

  LCS (s1, s2);

  return 0;
}