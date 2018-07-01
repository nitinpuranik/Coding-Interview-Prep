#include <iostream>
#include <vector>
using namespace std;

void LongestConsecutiveIncreasingSeq (const vector<int>& arr) {
  unsigned currlen, maxlen;
  unsigned i, maxind;

  if (arr.empty()) {
    return;
  }

  currlen = 1;
  maxlen = 1;
  maxind = 0;

  for (i = 1; i < arr.size(); i++) {
    if (arr[i] > arr[i - 1]) {
      currlen++;
    } else {
      if (currlen > maxlen) {
        maxlen = currlen;
        maxind = i - 1;
        currlen = 1;
      }
    }
  }

  /*
   * If you skip this if-conditional, your code
   * will fail the input {2,4,3,5,7,6,9,10,12}
   */
  if (currlen > maxlen) {
    maxlen = currlen;
    maxind = i - 1;
  }

  i = maxind - maxlen + 1;
  cout << "{" << arr[i++];

  for (; i <= maxind; i++) {
    cout << ", " << arr[i];
  }

  cout << "}" << endl;
}

int main () {
  vector<int> arr {2,4,3,5,7,6,9,10,12,8};

  LongestConsecutiveIncreasingSeq(arr);

  return 0;
}