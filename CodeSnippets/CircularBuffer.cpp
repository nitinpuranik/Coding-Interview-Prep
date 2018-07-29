#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void IsCircular (const vector<int>& arr) {
  unordered_set<int> visited;
  int index = 0;
  
  while (true) {
    if (visited.find(index) == visited.end()) {
      visited.insert(index);
      
      index = index + arr[index];
      
      if (index >= (int) arr.size()) {
        index %= arr.size();
      } else if (index < 0) {
        index *= -1;
        index = arr.size() - (index % arr.size());
        
        index = index == (int) arr.size() ? 0 : index;
      }
    } else {
      if (index == 0 && visited.size() == arr.size()) {
        cout << "Circular buffer." << endl;
      } else {
        cout << "Not a circular buffer." << endl;
      }
      
      return;
    }
  }
}

int main() {
  vector<int> arr {-7, -10, -1};
  
  IsCircular (arr);
  
  return 0;
}