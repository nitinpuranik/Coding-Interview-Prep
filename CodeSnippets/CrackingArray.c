#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
  false,
  true
} Bool;

Bool IsUnique (const char *str) {
  const char *ptr;
  
  for(; *(str + 1); str++) {
    for (ptr = str + 1; *ptr; ptr++) {
      if (*str == *ptr) {
        return false;
      }
    }
  }

  return true;
}

Bool IsUniqueBitArray (const char *str) {
  unsigned int i;
  unsigned char bitarray[32];
  
  for (i = 0; i < 32; i++) {
    bitarray[i] = 0;
  }
  
  while(*str) {
    unsigned int index;
    unsigned int offset;
    
    index = *str / 8;
    offset = *str % 8;
    
    if (bitarray[index] & (1 << offset)) {
      printf("character: %c.\n", *str);
      printf("characterValue: %u.\n", *str);
      printf("index: %u.\n", index);
      printf("offset: %u.\n", offset);
      return false;
    }
    
    bitarray[index] |= (1 << offset);
    str++;
  }
  
  return true;
}

void Reverse(char *str) {
  char *start, *end;
  
	if (str == NULL) {
		return;
	}
	
	start = str;
  end = str + strlen(str) - 1;

#define XOR_SWAP(a,b) do { \
  a ^= b; \
	b ^= a; \
	a ^= b; \
} while(0)

  while(start < end) {
    XOR_SWAP(*start, *end);
    start++; end--;
  }

#undef XOR_SWAP
	
	printf("%s\n", str);
}

void Uppercase(char *str) {
  while(*str) {
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - 'a' + 'A';
    }
    str++;
  }
}

Bool Anagram(const char *a, const char *b) {
  char asciitable[256];
  unsigned int count;
  
  if (strlen(a) != strlen(b)) {
    return false;
  }
  
  for (count = 0; count < 256; count++) {
    asciitable[count] = 0;
  }
  
  while(*a && *b) {
    asciitable[(unsigned char)*a]++;
    asciitable[(unsigned char)*b]--;
    a++; b++;
  }
  
  for (count = 0; count < 256; count++) {
    if (asciitable[count] != 0) {
      return false;
    }
  }
  
  return true;
}

const char* ReplaceSpace(const char *str) {
  unsigned int numspaces = 0;
  const char *ptr = str;
  char *newstring = NULL;
  char *spacestr = "%20";
  unsigned int startindex, endindex;
  
  while(*ptr) {
    if (*ptr++ == ' ') {
      numspaces++;
    }
  }
  
  if (numspaces == 0) {
    return str;
  }
  
  newstring = (char*) malloc(strlen(str) + numspaces * 2);

  if (newstring) {
    startindex = 0;
    endindex = 0;
  
    ptr = str;
    while(*ptr) {
      if (*ptr == ' ') {
        strncat(newstring, str, endindex - startindex);
        strcat(newstring, spacestr);
        startindex = endindex = endindex + 1;
        str = ptr + 1;
      } else {
        endindex++;
      }
      ptr++;
    }
    strcat(newstring, str);
  }
  
  return newstring;
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

int main(int argc, char **argv)
{
  char str[] = "water";
  RotateArray(str);
  /*
  MakeZeros(arr,3,5);
  printf("Newstring = %s\n", ReplaceSpace(str));
  Anagram(str1, str2)
  IsUniqueBitArray(str)
  Uppercase(str);
  Reverse(str);
  IsUniqueArr(str)
  */
  return 0;
}