#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *next;
};

int pop(struct node **first){
    
	if( *first == NULL ){
		exit(EXIT_FAILURE);
	}else{
		struct node *top = *first;
		int value = top->data;
		*first = top->next;
		free(top);
		return value;
  }
}
void push(struct node **first, int x){
	struct node* node = malloc(sizeof(struct node));
	if( node == NULL ){
		exit(EXIT_FAILURE);
	}else{
		node->data = x;
		node->next = *first;
		*first = node;
	}
}

int calc(char math, struct node** start ){
	int before;
	switch(math) {
		case '+': 
      return pop(start) + pop(start);
    case '-': 
      before = pop(start); 
      return pop(start) - before;
		case 'x': 
      return pop(start) * pop(start);
		
		case '/': 
      before = pop(start); 
      return pop(start) / before;
	}
}

int main( int argc, char* argv[]){
  int i = 0;
	struct node* head = NULL;

	if(argc == 2){
    return 0;


  return 0;
  }else{
    exit(EXIT_FAILURE);
  }
}
