#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *next;
};

struct node *head = NULL;
struct node *val = NULL;

int len() {
  int n = 0;
  struct node *point = head;
  while (point != NULL) {
    n++;
    point = point->next;
  }
  return n;
}

void print() {
  printf("%i :", len());
  struct node *point = head;
  while (point != NULL) {
    printf(" %i", point->data);
    point = point->next;
  }
}

void deleteN(int x) {
  struct node *var = head;
  struct node *previous = NULL;
  if (head == NULL) {
    return;
  }
  while (var->data != x) {
    if (var->next == NULL) {
      return;
    } else {
      previous = var;
      var = var->next;
    }
  }
  if (previous == NULL) {
    head = head->next;
    free(var);
  } else {
    previous->next = var->next;
    free(var);
  }
}

void insert(int x) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->data = x;
  if (head == NULL) {
    temp->next = head;
    head = temp;
    return;
  }
  struct node *varNode = head->next;
  struct node *prev = head;
  while ((varNode != NULL)) {
    if (prev->data == x) {
      free(temp);
      return;
    }
    if ((prev->data < x) && (x < varNode->data)) {
      break;
    }
    prev = varNode;
    varNode = varNode->next;
  }
  if (prev->data == x) {
    free(temp);
    return;
  }
  if (prev->data > x) {
    temp->next = head;
    head = temp;
    return;
  }
  prev->next = temp;
  temp->next = varNode;
}

void dealloc() {
  struct node *val = head;
  struct node *prev = NULL;
  while (val != NULL) {
    prev = val;
    val = val->next;
    free(prev);
  }
}

int main(void) {
  char letter;
  int num;
  while (scanf("%c %i", &letter, &num) == 2) {
    //command characters
    if (letter == 'd') {
      deleteN(num);
    } else if (letter == 'i') {
      insert(num);
    } else {
      printf("invalid response");
    }
    print();
    getchar();
    printf("\n");
  }
  dealloc();
  return 0;
}
