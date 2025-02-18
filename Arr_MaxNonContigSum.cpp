// If all negatives, then pick the least negative number.

#include <iostream>
#include <vector>
using namespace std;

void PrintMax (const auto& arr, int index, const auto& pred) {
  if (pred[index] == -1) {
    cout << arr[index];
    return;
  }
  
  PrintMax (arr, pred[index], pred);
  cout << " + " << arr[index];
}

void MaxNonContigSum (const auto& arr) {
  if (arr.empty())
    return;
  
  int maxsum = arr[0];
  int maxindex = 0;
  
  vector<int> pred {-1};
  
  for (unsigned i = 1; i < arr.size(); i++) {
    
    pred.push_back(-1);

    if (arr[i] > 0) {
      
      if (maxsum > 0) { // If maxsum is positive, then adding arr[i] improves things.
        maxsum += arr[i];
        pred[i] = maxindex;
      } else { // If maxsum is negative, restart the sequence from this positive element.
        maxsum = arr[i];
      }
      
      maxindex = i;

    } else if (arr[i] > maxsum) { // If arr[i] is negative, then check if it is still greater than maxsum.
      maxsum = arr[i];
      maxindex = i;
    }
  }
  
  PrintMax(arr, maxindex, pred);
}

int main() {
  vector<int> arr {-2, -3, 4, -1, -2, 1, 5, -3};
  
  MaxNonContigSum(arr);
  
  return 0;
}