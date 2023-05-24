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


Instruction *dead_code_elimination(Instruction *head) {

		/* STUDENTS - BEGIN */
	Instruction *current = head, *previous = NULL;
    	int a, b;

    while (current != NULL) 
    {
        if (current->opcode == LOADI && current->field1 == 0) {
            if (previous != NULL && previous->opcode == STOREAI && previous->field2 == current->field2) {
                free(current);
                current = previous->prev;
                if (current != NULL)
                    current->next = previous->next;
                free(previous);
                if (current != NULL)
                    previous = current->prev;
            }
        }
        else if (current->opcode == MULT) {
            a = current->field1;
            b = current->field2;
            if (previous != NULL && previous->opcode == ADD && previous->field1 == a && previous->field2 == b) {
                free(current); 
                current = previous;
                if (current != NULL)
                    current->next = previous->next;
                free(previous);
                if (current != NULL)
                    previous = current->prev;
            }
        }
        previous = current;
        current = current->next;
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

	head = dead_code_elimination(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

