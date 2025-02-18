#include <iostream>
#include <vector>
using namespace std;

bool Foo (const vector<string>& arr, const string& target) {
  static unsigned index = 0;

  if (arr.empty() || target.empty())
    return false;

  if (index == target.length())
    return true;

  for (const string& str : arr) {

    if (str[0] == target[index]) {

      if (target.find (str, index) == index) {

        index += str.length();

        if (Foo (arr, target) == true)
          return true;

        index -= str.length();
      }
    }
  }

  return false;
}

int main () {
  vector<string> arr {"ono", "two", "four", "on", "one"};
  string target = "fouronone";

  if (true == Foo(arr, target)) {
    cout << target << " created from set." << endl;
  } else {
    cout << "Can't be created from set." << endl;
  }

  return 0;
}