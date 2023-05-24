#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gate {
  char lim[17];
  int cnum, xnum;
  int *I, *O, *selectorI;
};

int counter(char *a, char **x, int len) {
  for (int i = 0; i < len; i++) {
    if (strcmp(x[i], a) == 0)
      return i;
  }
  return -1;
}

void clearDirectives(struct gate *f, int r) {
  for (int i = 0; i < r; i++) {
    free(f[i].I);
    free(f[i].O);
    free(f[i].selectorI);
  }
  free(f);
}

int breakBool(int *x, int y) {
  for (int i = y + 1; i >= 2; i--) {
    x[i] = !x[i];
    if (x[i] == 1)
      return 1;
  }
  return 0;
}
void MULTIPLEXER(int *array, int n, int *i, int *sel, int o) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += array[sel[i]] * pow(2, n - i - 1);
    }
    array[o] = array[i[s]];
}


void pleaseFreeThis(char **h, int r) {
  for (int i = 0; i < r; i++) {
    free(h[i]);
  }
  free(h);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    return EXIT_SUCCESS;
  }
  FILE *f = fopen(argv[1], "r");
  if (!f) {
    return EXIT_SUCCESS;
  }
  struct gate *circuit = NULL;
  int ctr = 0;
  int input = 0;
  int output = 0;
  int tmpc = 0;
  char in[17];
  char **var;
  int len = 2;
  int *truth = malloc(len * sizeof(int));
  fscanf(f, " %s", in);
  fscanf(f, "%d", &input);
  len += input;
  var = malloc(len * sizeof(char *));
  var[1] = malloc(2 * sizeof(char));
  var[1] = "1\0";
  var[0] = malloc(2 * sizeof(char));
  var[0] = "0\0";

  for (int i = 0; i < input; i++) {
    var[i + 2] = malloc(17 * sizeof(char));
    fscanf(f, "%*[: ]%16s", var[i + 2]);
  }
  fscanf(f, " %s", in);
  fscanf(f, "%d", &output);
  len += output;
  var = realloc(var, len * sizeof(char *));
  for (int i = 0; i < output; i++) {
    var[i + input + 2] = malloc(17 * sizeof(char));
    fscanf(f, "%*[: ]%16s", var[i + input + 2]);
  }
  while (!feof(f)) {
    int Inum = 2;
    int Onum = 1;
    struct gate newLogic;
    int e = fscanf(f, " %s", in);
    if (e != 1) {
      break;
    }
    ctr++;
    newLogic.cnum = 0;
    newLogic.xnum = 0;
    strcpy(newLogic.lim, in);

    if (strcmp(in, "NOT") == 0) {
      Inum = 1;
    }
    if (strcmp(in, "MULTIPLEXER") == 0) {
      fscanf(f, "%d", &Inum);
      newLogic.xnum = Inum;
      Inum = pow(2, Inum);
    }
    if (strcmp(in, "DECODER") == 0) {
      fscanf(f, "%d", &Inum);
      newLogic.cnum = Inum;
      Onum = pow(2, Inum);
    }
    if (strcmp(in, "PASS") == 0) {
      Inum = 1;
    }

    char con[17];
    newLogic.I = malloc(Inum * sizeof(int));
    newLogic.O = malloc(Onum * sizeof(int));
    newLogic.selectorI = malloc(newLogic.xnum * sizeof(int));

    for (int i = 0; i < Inum; i++) {
      fscanf(f, "%*[: ]%16s", con);
      newLogic.I[i] = counter(con, var, len);
    }

    for (int i = 0; i < newLogic.xnum; i++) {
      fscanf(f, "%*[: ]%16s", con);
      newLogic.selectorI[i] = counter(con, var, len);
    }

    for (int i = 0; i < Onum; i++) {
      fscanf(f, "%*[: ]%16s", con);
      int foo = counter(con, var, len);
      if (foo == -1) {
        len++;
        tmpc++;
        var = realloc(var, len * sizeof(char *));
        var[len - 1] = malloc(17 * sizeof(char));
        strcpy(var[len - 1], con);
        newLogic.O[i] = len - 1;
      } else {
        newLogic.O[i] = foo;
      }
    }

    if (!circuit) {
      circuit = malloc(sizeof(struct gate));
    } else {
      circuit = realloc(circuit, ctr * sizeof(struct gate));
    }
    circuit[ctr - 1] = newLogic;
  }
  pleaseFreeThis(var, len);
  
  truth = malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    truth[i] = 0;
  }
  truth[1] = 1;

  while (1 < 2) {
    for (int i = 0; i < input; i++) {
      printf("%d ", truth[i + 2]);
    }
    printf("|");

    for (int i = 0; i < ctr; i++) {
      struct gate newLogic = circuit[i];
      if (strcmp(newLogic.lim, "NOT") == 0) {
        truth[newLogic.O[0]] = !truth[newLogic.I[0]];
      }
      if (strcmp(newLogic.lim, "AND") == 0) {
        truth[newLogic.O[0]] = truth[newLogic.I[0]] && truth[newLogic.I[1]];
      }
      if (strcmp(newLogic.lim, "OR") == 0) {
        truth[newLogic.O[0]] = truth[newLogic.I[0]] || truth[newLogic.I[1]];
      }
      if (strcmp(newLogic.lim, "NAND") == 0) {
        truth[newLogic.O[0]] = !(truth[newLogic.I[0]] && truth[newLogic.I[1]]);
      }
      if (strcmp(newLogic.lim, "NOR") == 0) {
        truth[newLogic.O[0]] = !(truth[newLogic.I[0]] || truth[newLogic.I[1]]);
      }
      if (strcmp(newLogic.lim, "XOR") == 0) {
        truth[newLogic.O[0]] = truth[newLogic.I[0]] ^ truth[newLogic.I[1]];
      }
      if (strcmp(newLogic.lim, "PASS") == 0) {
        truth[newLogic.O[0]] = truth[newLogic.I[0]];
      }
      if (strcmp(newLogic.lim, "DECODER") == 0) {
        int tmp = 0;
        for (int i = 0; i < pow(2, newLogic.cnum); i++) {
          truth[newLogic.O[i]] = 0;
        }
        for (i = 0; i < newLogic.cnum; i++) {
          tmp += truth[newLogic.I[i]] * pow(2, newLogic.cnum - i - 1);
        }
        truth[newLogic.O[tmp]] = 1;
      } 
      if(strcmp(newLogic.lim, "MULTIPLEXER") == 0){
        MULTIPLEXER(truth, newLogic.xnum, newLogic.I, newLogic.selectorI, newLogic.O[0]);
      }
    }

    for (int i = 0; i < output; i++) {
      printf(" %d", truth[input + i + 2]);
    }
    printf("\n");

    if (!breakBool(truth, input)) {
      break;
    }
  }
  clearDirectives(circuit, ctr);

  return EXIT_SUCCESS;
}

