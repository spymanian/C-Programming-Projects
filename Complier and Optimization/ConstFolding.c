/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2023                              *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

/*
* Will traverse instructions in groups of 3, searching for a patten of LOADI, LOADI, and ADD | SUB | MUL instructions 
*/

Instruction *constant_folding(Instruction *head) {

		/* STUDENTS - BEGIN */
	Instruction *previous = NULL, *current = head, *nextUp = head->next;

	while (nextUp != NULL) {
		if (current->opcode == LOADI && nextUp->opcode == LOADI &&
			(nextUp->next->opcode == ADD || nextUp->next->opcode == SUB || nextUp->next->opcode == MULT)) {

			int win1 = current->field1;
			int win2 = nextUp->field1;
			int win3;

			switch (nextUp->next->opcode) {
				case ADD:
					win3 = win1 + win2;
					break;
				case SUB:
					win3 = win1 - win2;
					break;
				case MULT:
					win3 = win1 * win2;
					break;
				default:
					previous = current;
					current = nextUp;
					nextUp = nextUp->next;
					continue;
			}

			Instruction *x = malloc(sizeof(Instruction));
			x->opcode = LOADI;
			x->field1 = win3;
			x->field2 = nextUp->next->field3;
			x->field3 = 0;
			x->prev = previous;
			x->next = nextUp->next->next;

			if (previous != NULL) {
				previous->next = x;
			} else {
				head = x;
			}

			free(current);
			free(nextUp);
			current = x;
			nextUp = x->next;
		}

		previous = current;
		current = nextUp;
		nextUp = nextUp->next;
	}
 		/* STUDENTS - END */
	return head;
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	head = constant_folding(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

