#include <stdio.h>
#include <string.h>

void StringPermutationWorker (const char *str, char *resultarray, int *count, int level) {
  int i;
  
  for (i = 0; i < 256; i++) {
    if (count[i]) {
      count[i]--;
      resultarray[level] = i;
      
      if (level == strlen(str) - 1) {
        printf("%s\n", resultarray);
      } else {
        StringPermutationWorker (str, resultarray, count, level + 1);
      }
      
      count[i]++;
    }
  }
}

void StringPermutation (const char *str, int n) {
  char resultarray[n + 1];
  int count[256];
  int i;
  
  for (i = 0; i < 256; i++) {
    count[i] = 0;
  }
  
  resultarray[n] = 0;
  
  for (i = 0; i < n; i++) {
    count[(unsigned char)str[i]]++;
  }
  
  StringPermutationWorker (str, resultarray, count, 0);
}

int main () {
  char *str = "aabc";

  StringPermutation (str, strlen(str));
  
  return 0;
}