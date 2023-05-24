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
#include <math.h>
#include "InstrUtils.h"
#include "Utils.h"

/*
* Will return log2(n) if it is an integer (meaning n is a power of 2), and -1 otherwise
*/
int int_log2(int n) {

	int s = 1, i = 0;

	while (s < n) {
		s = s << 1;
		i++;
	}

	if (s == n)
		return i;
	else
		return -1;

}

/*
* Will traverse instructions in groups of two, searching for a patten of LOADI and MUL | DIV instructions 
* where LOADI is a power of 2, and collapse these instructions into on shift operation of LSHIFTI | RSHIFTI
*/
Instruction *strength_reduction(Instruction *head) {

		/* STUDENTS - BEGIN */
    Instruction *previous = NULL, *current = head, *nextUp = current->next;

    while (nextUp != NULL) 
    {
        if (previous != NULL && current != NULL && nextUp != NULL && current->opcode == MUL && (nextUp->opcode == LOADI || nextUp->opcode == LOADAI) && int_log2(nextUp->field1) >= 0 && int_log2(nextUp->field1) <= 30) 
        {
            int shftpos = int_log2(nextUp->field1);
            if (shftpos >= 0 && shftpos <= 30) 
            {
                current->opcode = LSHIFTI;
                current->field3 = shftpos;
                current->next = nextUp->next;
                free(nextUp);
                nextUp = current->next;
                previous = current;
                current = nextUp;
                if (current != NULL) {
                    nextUp = current->next;
                }
            } else 
            {
                previous = current;
                current = nextUp;
                nextUp = nextUp->next;
            }
        } else if (previous != NULL && current != NULL && nextUp != NULL && current->opcode == DIV && (nextUp->opcode == LOADI || nextUp->opcode == LOADAI) && int_log2(nextUp->field1) >= 0 && int_log2(nextUp->field1) <= 30) 
        {
            int shftpos = int_log2(nextUp->field1);
            if (shftpos >= 0 && shftpos <= 30) {
                current->opcode = RSHIFTI;
                current->field3 = shftpos;
                current->next = nextUp->next;
                free(nextUp);
                nextUp = current->next;
                previous = current;
                current = nextUp;
                if (current != NULL) {
                    nextUp = current->next;
                }
            } else 
            {
                previous = current;
                current = nextUp;
                nextUp = nextUp->next;
            }
        } else 
        {
            previous = current;
            current = nextUp;
            nextUp = nextUp->next;
        }
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

	head = strength_reduction(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

