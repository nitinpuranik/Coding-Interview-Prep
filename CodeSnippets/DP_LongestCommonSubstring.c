#include <stdio.h>
#include <string.h>

void LongestCommonSubstring(const char *s1, const char *s2, size_t len_s1, size_t len_s2) {
  unsigned int t[len_s2 + 1][len_s1 + 1];
  unsigned int i, j;
  unsigned int maxlen = 0;
  unsigned int maxi;
  
  for (i = 0; i <= len_s1; i++) {
    t[0][i] = 0;
  }
  
  for (i = 0; i <= len_s2; i++) {
    t[i][0] = 0;
  }
  
  for (i = 1; i <= len_s2; i++) {
    for (j = 1; j <= len_s1; j++) {
      
      if (s1[j-1] == s2[i-1]) {
        t[i][j] = 1 + t[i-1][j-1];
                
        if (t[i][j] > maxlen) {
          maxlen = t[i][j];
          maxi = i-1;
        }
      } else {
        t[i][j] = 0;
      }
    }
  }
  
  if (maxlen > 0) {
    char lcs[maxlen + 1];
    
    strncpy(lcs, &s1[maxi - (maxlen - 1)], maxlen);
    
    printf("%s\n", lcs);
  }
}

int main() {
  char *s1 = "abcdaf";
  char *s2 = "zbcdf";
  LongestCommonSubstring(s1, s2, strlen(s1), strlen(s2));
  return 0;
}