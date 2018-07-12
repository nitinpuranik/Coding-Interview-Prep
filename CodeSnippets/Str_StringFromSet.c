#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool FooWorker (const vector<string>& arr, const string& target, unsigned index) {
  for (const string& str : arr) {

    if (target.size() - index >= str.size()) {

      if (target.find(str, index) == index) {

        if (target.size() - index == str.size())
          return true;

        if (true == FooWorker (arr, target, index + str.size()))
          return true;
      }
    }
  }

  return false;
}

bool Foo(const vector<string>& arr, const string& target) {
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