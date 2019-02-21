// Implement a function that outputs the Look and Say sequence:
// 1
// 11
// 21
// 1211
// 111221
// 312211
// 13112221
// 1113213211
// 31131211131221
// 13211311123113112211

#include <iostream>
#include <sstream>
using namespace std;

const string& ComputeLS (const string& seq) {
  // Note that you can return a reference only because str is static.
  static string str;
  stringstream os;

  int count = 1;
  char last = seq[0];

  // We go until i == seq.length() to account for the last character.
  // This is an important techique so that you don't have to repeat
  // what you did inside the loop again outside for the last character.
  for (unsigned i = 1; i <= seq.length(); i++) {
    if (i == seq.length() || last != seq[i]) {
      os << count << last;
      count = 1;
      last = seq[i];
    } else {
      count++;
    }
  }

  os >> str;
  return str;
}

void LookSay (int count) {
  // Initialize to a number.
  string seq {"5"};

  for (int i = 0; i < count; i++) {
    cout << seq << endl;

    seq = ComputeLS (seq);
  }
}

int main() {
  // Print upto 20 numbers in the sequence.
  LookSay (20);
  return 0;
}