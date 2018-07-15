#include <stdio.h>
#include <string.h>

void PrintLCS (const char *str, int row, int col, int totalcols, unsigned t[][totalcols]) {
  
  if (t[row][col] == 0) {
    return;
  }

  if (t[row][col] == 1) {
  
    printf("%c ", str[row]);
  
  } else {
    
    if (str[row] == str[col]) {
      
      printf("%c ", str[row]);
      
      PrintLCS (str, row + 1, col - 1, totalcols, t);
      
      printf("%c ", str[row]);
    
    } else {
      
      if (t[row][col - 1] > t[row + 1][col]) {
        
        PrintLCS (str, row, col - 1, totalcols, t);

      } else {
        
        PrintLCS (str, row + 1, col, totalcols, t);

      }
    }
  }
}

void LongestPalindromicSubsequence (const char *str, int n) {
  int i, j, k;
  unsigned t[n][n];
  
  if (str == NULL || n <= 0) {
    return;
  }
  
  // Initialize the entire table although you'll only use the upper
  // triangular half of it because for strings like "abba", you might
  // end up using a garbage uninitialized value.
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      t[i][j] = 0;
    }
  }
  
  for (i = 0; i < n; i++) {
    t[i][i] = 1;
  }
  
  for (i = 2; i <= n; i++) {
    
    for (j = 0; j <= n - i; j++) {
      
      k = i + j - 1;
      
      if (str[j] == str[k]) {
      
        t[j][k] = t[j + 1][k - 1] + 2;
      
      } else {
        
        if (t[j][k - 1] > t[j + 1][k]) {
          
          t[j][k] = t[j][k - 1];
        
        } else {
         
          t[j][k] = t[j + 1][k];
        }
      }
    }
  }
  
  PrintLCS (str, 0, n - 1, n, t);
}

int main () {
  char *str = "agbdba";
  
  LongestPalindromicSubsequence (str, strlen(str));
  
  return 0;
}