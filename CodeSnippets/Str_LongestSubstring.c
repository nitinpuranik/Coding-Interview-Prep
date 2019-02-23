// aacdbbeb, k = 2. Output = aacdbbe
// alblabljln, k = 1. Output = ablj
// alblabljln, k = 2. Output = alblab.  <-- This is the most twisted example.

#include <iostream>
#include <unordered_map>
using namespace std;

void LongestSubstringWorker (const string& str, int start, int *maxlen, int *maxindex, int k) {
  static int currlen = 0;
  static unordered_map<char, int> count;

  for (int i = start + currlen; i < (int) str.length(); i++) {
    count[str[i]]++;
    currlen++;

    if (count[str[i]] > k) {

      if (*maxlen < currlen - 1) {
        *maxlen = currlen - 1;
        *maxindex = start;
      }

      for (int j = start; j < i; j++) {
        count[str[j]]--;
        currlen--;

        if (str[j] == str[i]) {
          LongestSubstringWorker (str, j + 1, maxlen, maxindex, k);
          return;
        }
      }
    }
  }

  if (*maxlen < currlen) {
    *maxlen = currlen;
    *maxindex = start;
  }
}

void LongestSubstring (const string& str, int k) {
  if (str.empty() || k <= 0)
    return;

  int maxlen = 0;
  int maxindex = 0;

  LongestSubstringWorker (str, 0, &maxlen, &maxindex, k);

  for (int i = maxindex; i < maxindex + maxlen; i++) {
    cout << str[i];
  }
}

int main () {
  LongestSubstring("alblabljln", 2);
  return 0;
}
/*===============================================================
 * Here's an alternate cleaner non-recursive solution. Draws from
 * the optimal substructure approach used in Dynamic Programming.
 */

// aacdbbeb, k = 2. Output = aacdbbe
// alblabljln, k = 1. Output = ablj
// alblabljln, k = 2. Output = alblab.  <-- This is the most twisted example.

// a(1) l(2) b(3) l(4) a(5) b(6) l(5) j(6) l(5) n(6).

void LongestSubstring (const string& str, int k) {
  if (str.empty() || k < 1)
    return;

  int maxlen = 1;
  int maxindex = 0;
  int s[str.length()] {1};
  unordered_map<char, int> count {{str[0], 1}};

  for (unsigned i = 1; i < str.length(); i++) {
    s[i] = s[i - 1] + 1;
    count[str[i]]++;

    if (count[str[i]] > k) {
      for (unsigned j = i - s[i] + 1; j < i; j++) {
        s[i]--;
        count[str[j]]--;

        if (str[j] == str[i]) {
          break;
        }
      }
    }

    /* < gives the leftmost occurrence. <= gives the rightmost occurrence. */
    if (maxlen <= s[i]) {
      maxlen = s[i];
      maxindex = i;
    }
  }

  for (int i = maxindex - maxlen + 1; i <= maxindex; i++)
    cout << str[i];
}