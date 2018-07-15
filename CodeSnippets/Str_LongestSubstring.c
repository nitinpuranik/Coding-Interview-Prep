#include <stdio.h>
#include <string.h>

// aacdbbeb, k = 2. Output = aacdbbe
// alblabljln, k = 1. Output = ablj
// alblabljln, k = 2. Output = alblab.  <-- This is the most twisted example.

int LongestSubstringWorker (const char *str, int currindex, int k, int *maxindex) {
  int i, j, len = 0;
  int count[26];
  int newlength;
  
  for (i = 0; i < 26; i++) {
    count[i] = 0;
  }
  
  for (i = currindex; i < strlen(str); i++) {
    
    if (++count[str[i] - 'a'] > k) {
      
      for (j = currindex; j < i; j++) {
        
        if (str[j] == str[i]) {
         
          newlength = LongestSubstringWorker (str, j + 1, k, maxindex);
          
          if (newlength > len) {
            return newlength;
          } else {
            *maxindex = currindex;
            return len;
          }
        }
      }
    }
    
    len++;
  }
  
  *maxindex = currindex;
  return len;
}

void LongestSubstring (const char *str, int k) {
  int maxlen, maxindex;
  int i;
  
  if (str == NULL || k <= 0) {
    return;
  }
  
  maxlen = LongestSubstringWorker (str, 0, k, &maxindex);
  
  printf("Maxlen = %d\n", maxlen);
  
  for (i = maxindex; i < maxindex + maxlen; i++) {
    printf("%c", str[i]);
  }
  
  printf("\n");
}

int main () {
  LongestSubstring("alblabljln", 2);
  return 0;
}