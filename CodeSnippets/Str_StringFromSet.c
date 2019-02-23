#include <iostream>
#include <vector>
using namespace std;

bool FooWorker (const auto& arr, const string& target, unsigned index) {
  for (const string& str : arr) {

    if (target[index] == str[0]) {

      if (target.find(str, index) == index) {

        if (index + str.length() == target.length())
          return true;

        if (true == FooWorker (arr, target, index + str.length())) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Foo (const auto& arr, const string& target) {
  return FooWorker (arr, target, 0);
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