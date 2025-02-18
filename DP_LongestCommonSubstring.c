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

  vector<vector<int>> arr(s1.length(), vector<int>(s2.length(), 0));

  for (unsigned row = 0; row < s1.length(); row++) {
    for (unsigned col = 0; col < s2.length(); col++) {
      if (s1[row] == s2[col]) {
        if (row == 0 || col == 0)
          arr[row][col] = 1;
        else
          arr[row][col] = arr[row - 1][col - 1] + 1;
        
        if (arr[row][col] > maxlen) {
          maxlen = arr[row][col];
          maxindex = row;
        }
      }
    }
  }

  if (maxlen > 0)
    cout << s1.substr(maxindex - maxlen + 1, maxlen);
}

int main() {
  string s1 = "abcdaf";
  string s2 = "zbcdf";

  LCS (s1, s2);

  return 0;
}