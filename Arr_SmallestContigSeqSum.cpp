// Given a target sum (28 in our example), find the smallest sequence
// in the given array that sums up to 28. If not found, print so.

#include <iostream>
#include <vector>
using namespace std;

void SmallestContigSequenceSum (const vector<int>& arr, int target) {
  if (arr.empty())
    return;
  
  int startindex, endindex;
  int sum, minindex, minlen;
  
  sum = 0;
  startindex = endindex = 0;
  minlen = arr.size() + 1;
  
  while (endindex < (int) arr.size()) {
    sum += arr[endindex];
    
    while (sum > target) {
      sum -= arr[startindex++];
    }
    
    if (sum == target) {
      if (endindex - startindex + 1 < minlen) {
        minlen = endindex - startindex + 1;
        minindex = startindex;
      }
    }
    
    endindex++;
  }
  
  if (minlen <= (int) arr.size()) {
    for (int i = 0; i < minlen; i++)
      cout << arr[minindex++] << ' ';
  }
}

int main() {
  vector<int> arr {2, 3, 16, 6, 1, 12, 9/*, 27, 1*/ /* 28 */};
  //vector<int> arr {2, 3, 16, 6, 1, 12, 9, 27, 0, 1};

  SmallestContigSequenceSum (arr, 28);
  return 0;
}