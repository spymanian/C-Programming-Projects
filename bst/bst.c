#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *l;
  struct node *r;
};

struct node * val(struct node *node) {
  //minValue of bst
  struct node * x = node;
  while (x && x -> l!= NULL)
    x = x->l;
  return x;
}

struct node *create(int x) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  newNode->data = x;
  newNode->l = newNode->r = NULL;
  return newNode;
}

int s(struct node *curr, int x) {
  if (curr == NULL) return 0;
  if (curr->data == x) return 1;
  if (curr->data < x) return s(curr->r, x);
  return s(curr->l, x);
}

void p(struct node *node) {
  if (node != NULL) {
    printf("(");
    p(node->l);
    printf("%i", node->data);
    p(node->r);
    printf(")");
  }
}


struct node * d(struct node * node, int data) {
  if (node == NULL)
    return node;
  if (data < node -> data)
    node -> l = d(node -> l, data);
  else if (data > node -> data)
    node -> r = d(node -> r, data);
  else {
    if (node -> l == NULL) {
      struct node * tn = node -> r;
      free(node);
      return tn;
    } else if (node -> r == NULL) {
      struct node * tn = node -> l;
      free(node);
      return tn;
    }
    struct node * tn = val(node -> r);
    node -> data = tn -> data;
    node -> r = d(node -> r, tn -> data);
  }
  return node;
}

struct node *i(struct node *node, int x) {
  if (node == NULL) return create(x);
  if (x < node->data) {
    node->l = i(node->l, x);
  } else if (x > node->data) {
    node->r = i(node->r, x);
  }
  return node;
}

int main(int argc, char **argv) {
  int x;
  char letter;
  char str1[255], str2[255];
  struct node *subtree = NULL;
  
  while (scanf("%[^\n]%*c", str1) != EOF) {
    letter = str1[0];
    if (strlen(str1) != 1) {
      for (int i = 2; i < strlen(str1); i++) {
        str2[i - 2] = str1[i];
      }
      x = atoi(str2);
    }
    
    memset(str2, ' ', strlen(str1));
    
    //command characters
    if (letter == 'i') {
      if (s(subtree, x) == 0) {
        printf("inserted\n");
        subtree = i(subtree, x);
      } else {
        printf("not inserted\n");
      }
    } else if (letter == 's') {
      if (s(subtree, x) == 1) {
        printf("present\n");
      } else {
        printf("absent\n");
      }
    } else if (letter == 'd') {
      if (s(subtree, x) == 1) {
        printf("deleted\n");
        subtree = d(subtree, x);
      } else {
        printf("absent\n");
      }
    } else if (letter == 'p') {
      if (subtree == NULL) {
        printf("\n");
    } else {
        p(subtree);
        printf("\n");
      }
    }
  }
  return 0;
}
