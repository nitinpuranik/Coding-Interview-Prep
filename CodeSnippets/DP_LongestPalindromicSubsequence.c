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

  vector<vector<int>> tbl (str.length(), vector<int>(str.length(), 0));

  for (unsigned i = 0; i < str.length(); i++)
    tbl[i][i] = 1;

  /* Proceed diagonally until you fill the upper right triangle of the table. */
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

// Try agbdba and abba. Especially 'abba'. If you don't
// account for tbl[i][j] == 0, you'll overrun the tbl buffer.
int main () {
  string str = "npuraitinik";

  LPS (str);

  return 0;
}