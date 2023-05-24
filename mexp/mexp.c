#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void printmatrix(int** arr,int n, int exp){
  if(exp == 0) {
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        if(i == j) {
          if(j == (n-1)) {
            printf("%i", 1);
          }else{
            printf("%i ", 1);
          }
        }else{
            if(j == (n-1)){
              printf("%i", 0);
            }else{
              printf("%i ", 0);
            }
        }
      }
      printf("\n");
    }
  }else{
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        int k = arr[i][j];
        if(j==n-1){
        printf("%d",k);
        }else{
          printf("%d ",k);
        }  
      }
      printf("\n");
    }
  }
}

void dealloc(int** arr, int n){
  for(int i = 0; i < n; i++) {
    free(arr[i]);
  }
  free(arr);
}


int main(int argc, char **argv) {
  if(argc != 2) {
    return 0;
  }
  char *name = argv[1];
  FILE *file;
  char str[255];
  file = fopen(name, "r"); 
  if(file == NULL) {
    printf("error\n");
    return 0;
  }
  fscanf(file, "%s", str);
  int row = atoi(str);
  fgetc(file);
  int** basematrix = (int**) malloc(row * sizeof(int*));
  for (int i = 0; i < row; i++)
      basematrix[i] = (int*)malloc(row * sizeof(int));
  for(int i = 0; i < row; i++) {
      for(int j = 0; j < row; j++) {
        fscanf(file, "%s", str);
        if((strcmp(str,"\n") == 0) || (strcmp(str," ") == 0)) {
          j = j-1;
        }
        else {
          basematrix[i][j] = atoi(str);
          }
      }
  }
  fgetc(file);
  fscanf(file, "%s", str);
  int power = atoi(str);
  
  if(power == 0) {
    printmatrix(basematrix, row, power);
    return 0;
    }
  if(power == 1) {
    printmatrix(basematrix, row, power);
    return 0;
    }
  int** expm;
  int** added;
  expm = malloc(sizeof(int*) * row);   
      for(int i = 0; i < row; i++) {
        expm[i] = malloc(sizeof(int*) * row);
      }
      for(int i = 0; i < row; i++) {
          for(int j = 0; j < row; j++) {
            expm[i][j] = basematrix[i][j];
          }
      }
      for(int i = 0; i < power-1; i++) {
        added = malloc(sizeof(int*) * row);
     
        for(int i = 0; i < row; i++) {
          added[i] = malloc(sizeof(int*) * row);
        }
        for(int i = 0; i < row; i++) {
          for(int j = 0; j < row; j++) {
            added[i][j] = 0;
          }
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < row; j++) {
                for (int f = 0; f < row; f++) {
                  added[i][j] += (expm[i][f] * basematrix[f][j]);
                }
            }
        }
        for(int i = 0; i < row; i++) {
          for(int j = 0; j < row; j++) {
            expm[i][j] = added[i][j];
          }
        }
        for(int i = 0; i < row; i++) {
            free(added[i]);
          }
        free(added);
      }
  
  printmatrix(expm,row,power);
  dealloc(basematrix, row);
  dealloc(expm, row);
  return 0;
}
