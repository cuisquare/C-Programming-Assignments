//////////////////
//MENU FUNCTIONS//
//////////////////
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"
#include "ParameterConstants.h"
#include "ErrorCodes.h"
#include "DoubleLinkedListFunctions.h"
#include "MenuFunctions.h"


void PrintMenu() {
	system("cls");
	printf("*****Double Linked List Program*****\n");
	printf("Please choose from the following options : \n");
	printf("	1 : Insert Value In List\n");
	printf("	2 : Delete Value From List\n");
	printf("	3 : Print List\n");
	printf("	4 : Clear List\n");
	printf("	5 : Input Multiple values in List\n");
	printf("	6 : Delete Multiple values in List\n");
	printf("	7 : Input Range in List\n");
	printf("	8 : Delete Range in List\n");
	printf("	0 : Exit Program\n");
}

// gets input from keyboard and convert to integer
int getIntValue(int *errstatus) {
	char charinput[10];
	char *garbagestring;
	bool invalidinput = 1;
	int choice;

	scanf_s("%9s", &charinput, 9);
	//int choice = atoi(charinput);
	choice = strtol(charinput, &garbagestring, 10);
	/*printf("Your choice was : %d!\n", choice);
	PressEnterToContinue();*/
	//printf("charinput = %s; invalidinput = %s", charinput, garbagestring);
	//input is invalid if the invalid part of input is equal to the whole input
	invalidinput = (garbagestring == charinput);
	if (invalidinput) {
		printf("invalidinput = %s, the input was invalid.", garbagestring);
		*errstatus = 0;
	}
	else {
		*errstatus = 1;
	}

	return choice;
}

int getMenuChoice(int *errstatus) {
	printf("Menu choice : ");
	int output = getIntValue(errstatus);
	printf("\n");
	//catching additional error that the input it outside of range allowed for menu choices even though input is integer
	if (*errstatus == 1) {
		if ((output<0) || (output>8)) {
			*errstatus = MenuOutOfRangeError;
		}
	}
	return output;
}

//flushes buffer and wait for getchar to resume
void PressEnterToContinue() {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
	printf("Press ENTER to continue.\n");
	getchar();
}

//Carry out choice from user input
HEADER* carryOutChoice(HEADER* head, int choice) {
	int errstatus;
	int inputval;
	switch (choice) {
	case 0:
		printf("Exiting Program.\n");
		break;
	case 1:
		printf("Input Single Value to Insert:  ");
		inputval = getIntValue(&errstatus);
		if (errstatus == 1) {
			head = InsertElementForwardByVal(head, inputval);
			printf("Value Inserted.\n");
		}
		else {
			printf("Input error. No value Inserted.\n");
		}
		break;
	case 2:
		printf("Input Single Value to Delete:  ");
		inputval = getIntValue(&errstatus);
		if (errstatus == 1) {
			head = DeleteElementByVal(head, inputval);
			printf("Value Deleted.\n");
		}
		else {
			printf("Input error. No value Deleted.\n");
		}
		break;
	case 3:
		PrintList(head);
		printf("List Printed.\n");
		break;
	case 4:
		head = CreateEmptyList();
		printf("List Cleared.\n");
		break;
	case 5:
		printf("Input Number of Values to Insert:  ");
		int NbValToInsert = getIntValue(&errstatus);
		for (int i = 0; i<NbValToInsert; i++) {
			printf("Input Value %d / %d: ", i + 1, NbValToInsert);
			inputval = getIntValue(&errstatus);
			if (errstatus == 1) {
				head = InsertElementForwardByVal(head, inputval);
			}
			else {
				printf("\nInput error. Value will not be inserted.\n");
			}
		}
		printf("Input of values to insert over.\n");
		break;
	case 6:
		printf("Input Number of Values to Delete:  ");
		int NbValToDelete = getIntValue(&errstatus);
		for (int i = 0; i<NbValToDelete; i++) {
			printf("Value To Be Deleted %d / %d: ", i + 1, NbValToDelete);
			inputval = getIntValue(&errstatus);
			if (errstatus == 1) {
				head = DeleteElementByVal(head, inputval);
			}
			else {
				printf("\nInput error. No value will be deleted.\n");
			}
		}
		printf("Input of values to be deleted over.\n");
		break;
	case 7:
		printf("Input Start of Range - inclusive - to Insert:  ");
		int RangeStartForIns = getIntValue(&errstatus);
		printf("\n");
		printf("Input End of Range - exclusive - to Insert:  ");
		int RangeEndForIns = getIntValue(&errstatus);
		for (int i = RangeStartForIns; i<RangeEndForIns; i++) {
			head = InsertElementForwardByVal(head, i);
		}
		printf("Range to be Inserted Defined.\n");
		break;
	case 8:
		printf("Input Start of Range - inclusive - to Delete:  ");
		int RangeStartForDel = getIntValue(&errstatus);
		printf("\n");
		printf("Input End of Range - exclusive - to Delete:  ");
		int RangeEndForDel = getIntValue(&errstatus);
		for (int i = RangeStartForDel; i<RangeEndForDel; i++) {
			head = DeleteElementByVal(head, i);
		}
		printf("Range to be Deleted Defined.\n");
		break;
	}
	PressEnterToContinue();
	return head;
}
