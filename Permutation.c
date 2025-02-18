#include <iostream>
#include <unordered_map>
using namespace std;

// Build a hashmap with the counts of characters. Define a
// static 'result' variable that will house the permutations.
// Iterate through the map and add the characters to the result.
// Decrement the count of the characters as they are added. Once your
// result array reaches the length of the original string, print it out.
// Increment back the character once you return from recursive calls.

void StringPermutationWorker (const string& str, unordered_map <char, int>& umap) {
  static string result;

  for (unordered_map <char, int>::iterator it = umap.begin();
       it != umap.end(); it++) {
    if (it->second > 0) {
      result += it->first;
      it->second--;

      if (result.length() == str.length())
        cout << result << endl;
      else
        StringPermutationWorker (str, umap);

      it->second++;
      result.pop_back();
    }
  }
}

void StringPermutation (const string& str) {
  if (str.empty())
    return;

  unordered_map <char, int> umap;

  for (unsigned i = 0; i < str.length(); i++) {
    umap[str[i]]++;
  }

  StringPermutationWorker (str, umap);
}

int main () {
  string str {"abc"};

  StringPermutation (str);

  return 0;
}