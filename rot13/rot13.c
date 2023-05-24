#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    for (int j = 0; j < strlen(argv[i]); j++) {
      if (isalpha(argv[i][j])) {
        char letter = argv[i][j];
      for (int i = 0; i < 13; i++) {
      //rotation
      if (letter == 'z') {
        letter = 'a';
        } else if (letter == 'Z') {
        letter = 'A';
        } else {
        letter = letter + 1;
        }
      }   
        putchar(letter);
      } else {
        putchar(argv[i][j]);
      }
    }
  }
  printf("\n");
  return 0;
}
