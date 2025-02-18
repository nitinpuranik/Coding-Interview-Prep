// Find the first character that is alphabetically less than its predecessor.
// Should be case-insensitive. Should only deal with alphabets.

#include <iostream>
using namespace std;

char ToUpper (char ch) {
  if (ch >= 'a' && ch <= 'z')
    ch = ch - 'a' + 'A';

  return ch;
}

void FindChar (const string& str) {
  if (str.length() <= 1) {
    cout << "Characters are in order." << endl;
    return;
  }

  unsigned curr, next;

  for (curr = 0; curr < str.length(); curr++) {
    if ((str[curr] >= 'a' && str[curr] <= 'z') ||
        (str[curr] >= 'A' && str[curr] <= 'Z')) {
      break;
    }
  }

  if (curr == str.length()) {
    cout << "No alphabetic characters." << endl;
    return;
  }

  for (next = curr + 1; next < str.length(); next++) {
    if ( !(str[next] >= 'a' && str[next] <= 'z') &&
         !(str[next] >= 'A' && str[next] <= 'Z') ) {
      continue;
    }

    char currchar = ToUpper(str[curr]);
    char nextchar = ToUpper(str[next]);

    if (nextchar <= currchar) {
      cout << str[next] << " is the first non increasing character." << endl;
      return;
    }

    curr = next;
  }

  cout << "Characters are in order." << endl;
}

int main() {
  string str = "ab.C#D..f..E";
  //string str = ".......";

  FindChar(str);

  return 0;
}