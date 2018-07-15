#include <iostream>
#include <vector>
using namespace std;

void LCS (const string& s1, const string& s2) {
  if (s1.empty() || s2.empty())
    return;

  vector<vector<int>> tbl;
  int maxl, maxindex; // Track s1 in maxindex;

  maxl = 0;

  for (unsigned i = 0; i <= s2.size(); i++)
    tbl.push_back({0});

  for (unsigned j = 1; j <= s1.size(); j++)
    tbl[0].push_back(0);

  for (unsigned i = 1; i <= s2.size(); i++) {

    for (unsigned j = 1; j <= s1.size(); j++) {

      int entry = 0;

      if (s2[i - 1] == s1[j - 1]) {
        entry = tbl[i - 1][j - 1] + 1;
      }

      tbl[i].push_back(entry);

      if (entry > maxl) {
        maxl = entry;
        maxindex = i - 1;
      }
    }
  }

  for (int i = maxindex - maxl + 1; i <= maxindex; i++)
    cout << s2[i];
}

int main() {
  string s1 = "abcdaf";
  string s2 = "zbcdf";

  LCS (s1, s2);

  return 0;
}