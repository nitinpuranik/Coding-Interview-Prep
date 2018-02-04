#include <stdio.h>
#include <string.h>

unsigned djb2(const char *str, unsigned size) {
  unsigned hash = 5381;

  while (size) {
    hash = (hash << 5) + hash + *str;
    str++; size--;
  }
  
  return hash;
}

/*
 * This is not exactly an efficient implementation of Rabin-Karp
 * because you're recomputing the hash for the text strings and
 * aren't making use of the computation that came beforehand.
 * But I'm ignoring that limitation and moving on with my life.
 */
void RabinKarp(const char *text, const char *pattern) {
  int n, m;
  int i;
  unsigned hash_pattern, hash_text;

  n = strlen(text);
  m = strlen(pattern);
  
  hash_pattern = djb2(pattern, m);
  
  for (i = 0; i <= n - m; i++) {
    hash_text = djb2(&text[i], m);
    if (hash_text == hash_pattern) {
      unsigned index = i;
      unsigned size = m;
      while (text[index] == pattern[index - i] && size) {
        index++; size--;
      }
      
      if (size == 0) {
        printf("Found substring at index %u\n", i);
        return;        
      }
    }
  }
  
  printf("Substring not found.\n");
}

int main() {
  const char *text = "algorithm";
  const char *pattern = "rithm";
  
  RabinKarp(text, pattern);
  return 0;
}