// Find the first character that is alphabetically less than its predecessor.
// Should be case-insensitive. Should only deal with alphabets.

#include <iostream>
using namespace std;

void FindChar (string& str) {
  unsigned i = 0;
  
  while (i < str.length()) {
    if ( (str[i] >= 'a' && str[i] <= 'z') ||
         (str[i] >= 'A' && str[i] <= 'Z') )
      break;
    
    i++;
  }
  
  if (i == str.length()) {
    cout << "Empty string or no alphabetic characters." << endl;
    return;
  }
  
  if (str[i] >= 'A' && str[i] <= 'Z')
    str[i] = str[i] - 'A' + 'a';

  unsigned j = i + 1;
  
  while (j < str.length()) {
    if ( (str[j] < 'a' || str[j] > 'z') &&
         (str[j] < 'A' || str[j] > 'Z') ) {
      j++;
      continue;
    }
    
    char temp = str[j];
    
    if (str[j] >= 'A' && str[j] <= 'Z') {
      str[j] = str[j] - 'A' + 'a';
    }
    
    if (str[j] < str[i]) {
      cout << temp << " is the first non-increasing character." << endl;
      return;
    }
    
    i = j++;
  }
  
  cout << "Characters are in order." << endl;
}

int main() {
  string str = "ab.C#D..f..E";
  //string str = ".......";
  
  FindChar(str);
  
  return 0;
}