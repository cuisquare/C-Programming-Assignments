#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Types.h"
#include "ErrorCodes.h"
#include "ParameterConstants.h"

#include "DoubleLinkedListFunctions.h"
#include "MenuFunctions.h"


void TestProgram() {
	HEADER* head = CreateEmptyList();
	PrintList(head);
	head = InsertElementForwardByVal(head, 7);
	head = InsertElementForwardByVal(head, 13);
	head = InsertElementForwardByVal(head, 9);
	head = InsertElementForwardByVal(head, 5);
	head = InsertElementForwardByVal(head, 28);
	head = InsertElementForwardByVal(head, 11);
	head = InsertElementForwardByVal(head, 5);
	head = InsertElementForwardByVal(head, 9);
	head = DeleteElementByVal(head, 5);
	head = DeleteElementByVal(head, 11);
	head = InsertElementForwardByVal(head, 11);
	head = DeleteElementByVal(head, 28);
	head = DeleteElementByVal(head, 45);
	PrintList(head);

	HEADER* head2 = CreateEmptyList();
	PrintList(head2);
	PrintList(head2);
	for (int i = 0; i < 20; i++) {
		head2 = InsertElementForwardByVal(head2, i);
	}
	PrintList(head2);

	for (int i = 15; i < 40; i++) {
		head = InsertElementForwardByVal(head, i);
	}
	PrintList(head);

	printf("Press ENTER to continue.\n");

	getchar();
}

/////////////////
//END FUNCTIONS//
/////////////////



int main() {

	HEADER* head = CreateEmptyList();

	int choice;
	int errstatus;
	do {
		PrintMenu();
		choice = getMenuChoice(&errstatus);
		if (errstatus == 1) {
			head = carryOutChoice(head, choice);
		}
		else {
			printf("Incorrect Input. Only allowed inputs are integers 0-8.\n");
			choice = ContinueDefault;
			PressEnterToContinue();
		}
	} while (choice != 0);

	return 0;
}