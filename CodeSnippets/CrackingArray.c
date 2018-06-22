#include <iostream>
#include <cstring>

// Without using additional storage. CTCI 1.3
void RemoveUnique (char *str) {
  if (str == nullptr)
    return;

  if (strlen(str) < 2)
    return;

  unsigned tail = 1;

  for (unsigned i = 1; i < strlen(str); i++) {
    unsigned j;

    // Is str[i] a unique character? Can you replace tail with it?
    for (j = 0; j < tail; j++) {
      if (str[i] == str[j])
        break; // str[i] is not unique. It repeats somewhere in 0 <= j < tail.
    }

    // j == tail means you did not break from the above loop. So str[i] is unique.
    // Replace tail with it.
    if (j == tail) {
      str[tail] = str[i];
      tail++;
    }
  }

  str[tail] = 0;
}

// The above problem with additional storage.
void RemoveUnique (char *str) {
  bool table[256] {false};
  unsigned len;

  {
    char *temp = str;
    len = 0;

    while (*temp++) len++;
  }

  if (len < 2)
    return;

  unsigned tail = 1;
  unsigned char idx = str[0];
  table[idx] = true;

  for (unsigned i = 1; i < len; i++) {
    idx = str[i];

    if (table[idx] == false) {
      str[tail] = str[i];
      tail++;

      table[idx] = true;
    }
  }

  str[tail] = 0;
}

// CTCI 1.4
bool Anagram (string& str1, string& str2) {
  if (str1.length() != str2.length())
    return false;

  unsigned long hashtable[256] {0};

  for (unsigned i = 0; i < str1.length(); i++) {
    unsigned char idx = str1[i];
    hashtable[idx]++;

    idx = str2[i];
    hashtable[idx]--;
  }

  for (unsigned long item : hashtable) {
    if (item > 0) {
      return false;
    }
  }

  return true;
}

// CTCI 1.5
const char* ReplaceSpace (char *str) {
  unsigned strlen = 0;
  unsigned spaces = 0;

  {
    char *temp = str;

    while (*temp) {
      strlen++;

      if (*temp++ == ' ')
        spaces++;
    }
  }

  if (spaces == 0)
    return nullptr;

  char *newstr = new char[strlen + spaces * 2 + 1];
  char *temp = newstr;

  while (*str) {
    if (*str == ' ') {
      *temp++ = '%';
      *temp++ = '2';
      *temp++ = '0';
    } else {
      *temp++ = *str;
    }

    str++;
  }

  *temp = 0;

  return newstr;
}

void RotateArr(unsigned char foo[][3]) {
  unsigned char newarr[3][3];
  unsigned char rowind, colind;

  for (rowind = 0; rowind < 3; rowind++) {
    for (colind = 0; colind < 3; colind++) {
      newarr[colind][2 - rowind] = foo[rowind][colind];
    }
  }

  printf("Old array.\n");
  for (rowind = 0; rowind < 3; rowind++) {
    for (colind = 0; colind < 3; colind++) {
      printf("%hhu ", foo[rowind][colind]);
    }
    printf("\n");
  }

  printf("\nNew array.\n");
  for (rowind = 0; rowind < 3; rowind++) {
    for (colind = 0; colind < 3; colind++) {
      printf("%hhu ", newarr[rowind][colind]);
    }
    printf("\n");
  }
}

void MakeZeros(unsigned char (*arr)[5], unsigned int rowsize, unsigned int colsize) {
  unsigned int rowind, colind;

  for (rowind = 0; rowind < rowsize; rowind++) {
    for (colind = 0; colind < colsize; colind++) {
      if (arr[rowind][colind] == 0) {
        unsigned int i,j;
        for (j = 0; j < colsize;j++) {
          arr[rowind][j] = 0xFF;
        }
        for (i = 0; i < rowsize; i++) {
          arr[i][colind] = 0xFF;
        }
      }
    }
  }

  for (rowind = 0; rowind < rowsize; rowind++) {
    for (colind = 0; colind < colsize; colind++) {
      if (arr[rowind][colind] == 0xFF) {
        arr[rowind][colind] = 0;
      }
    }
  }

  for (rowind = 0; rowind < rowsize; rowind++) {
    for (colind = 0; colind < colsize; colind++) {
      printf("%hhu ", arr[rowind][colind]);
    }
    printf("\n");
  }
}

void RotateArray(char *str) {
  char lastchar;
  char *lastptr, *ptr;
  unsigned int count = strlen(str);

  /* Get to the last character. */
  for (lastptr = str; *(lastptr + 1); lastptr++);

  while (count--) {
    lastchar = *lastptr;
    ptr = lastptr - 1;

    while (ptr >= str) {
      *(ptr + 1) = *ptr;
      ptr--;
    }

    *str = lastchar;
    printf("[%u] %s\n", count + 1, str);
  }
}