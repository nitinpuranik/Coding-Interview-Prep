#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool Foo (char **set, char *target, int items) {
  int i;

  if (set == NULL || *set == NULL || target == NULL) {
    return false;
  }

  for (i = 0; i < items; i++) {

    if (target[0] == set[i][0]) {

      if (strlen(target) >= strlen(set[i])) {

        if (strncmp(target, set[i], strlen(set[i])) == 0) {

          if (strlen(target) == strlen(set[i])) {
            return true;
          }

          // Important step! If you simply return Foo() instead of checking return value, you will fail.
          // Note that you need to continue looping if Foo() returns false.
          if (true == Foo (set, target + strlen(set[i]), items)) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

int main () {
  char *set[] = {"ono", "two", "four", "on", "one"};
  char *target = "fouronone";

  if (true == Foo(set, target, sizeof(set)/sizeof(char*))) {
    printf("\"%s\" created from set.\n", target);
  } else {
    printf("Can't be created from set.\n");
  }

  return 0;
}