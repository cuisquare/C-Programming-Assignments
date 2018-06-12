#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Types.h"
#include "ErrorCodes.h"
#include "ParameterConstants.h"

#include "DoubleLinkedListFunctions.h"
#include "MenuFunctions.h"

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