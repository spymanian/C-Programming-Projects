#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    int num;
    char *word, *ptr;
    for (int i = 0; i < argc; i++) {
      word = argv[i + 1];
    num = i + 1;
    for (int j = i + 1; j < argc; j++) {
      if (strcmp(word, argv[j]) > 0) {
        word = argv[j];
        num = j;
      }
    }
    ptr = argv[i + 1];
    argv[i + 1] = argv[num];
    argv[num] = ptr;
  }
  for (int k = 1; k < argc; k++) {
    printf("%s\n", argv[k]);
  }
  return 0;
  }
}
