#include <iostream>
#include <vector>
using namespace std;

void PrintLPS (const string& str, const auto& tbl, int row, int col) {
  if (tbl[row][col] == 1) {
    cout << str[col];
  }

  else if (tbl[row][col] > 1) {
    if (str[row] == str[col]) {
      cout << str[col];

      PrintLPS (str, tbl, row + 1, col - 1);

      cout << str[col];
    } else if (tbl[row][col - 1] > tbl[row + 1][col]) {
      PrintLPS (str, tbl, row, col -1);
    } else {
      PrintLPS (str, tbl, row + 1, col);
    }
  }
}

void LPS (const string& str) {
  if (str.empty())
    return;

  vector<vector<int>> tbl;

  // Initialize the entire table although you'll only use the upper
  // triangular half of it because for strings like "abba", you might
  // end up using a garbage uninitialized value.
  for (unsigned i = 0; i < str.length(); i++) {
    tbl.push_back({0});

    for (unsigned j = 1; j < str.length(); j++)
      tbl[i].push_back(0);
  }

  for (unsigned i = 0; i < str.length(); i++)
    tbl[i][i] = 1;

  for (unsigned gap = 1; gap < str.length(); gap++) {
    for (unsigned i = 0; i < str.length() - gap; i++) {
      if (str[i] == str[i + gap]) {
        tbl[i][i + gap] = 2 + tbl[i + 1][i + gap - 1];
      } else {
        tbl[i][i + gap] = tbl[i][i + gap - 1] > tbl[i + 1][i + gap] ?
                            tbl[i][i + gap - 1] : tbl[i + 1][i + gap];
      }
    }
  }

  /* An easier, more intuitive way of implementing the above loop is like so. */
  for (unsigned k = 1; k < str.length(); k++) {
    for (unsigned row = 0, col = k; col < str.length(); row++, col++) {
      if (str[row] == str[col]) {
        tbl[row][col] = tbl[row + 1][col - 1] + 2;
      } else if (tbl[row][col - 1] > tbl[row + 1][col]) {
        tbl[row][col] = tbl[row][col - 1];
      } else {
        tbl[row][col] = tbl[row + 1][col];
      }
    }
  }

  PrintLPS (str, tbl, 0, str.length() - 1);
}

int main () {
  string str = "npuraitinik"; // Try agbdba and abba.

  LPS (str);

  return 0;
}