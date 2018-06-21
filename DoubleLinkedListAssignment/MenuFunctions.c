//////////////////
// MENU FUNCTIONS//
//////////////////
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"
#include "DoubleLinkedListFunctions.h"

//continues looping through menu after invalid menu choice 1 - or not
static int ContinueDefault = 1; 

//error status given if integer not in range for menu items
static int MenuOutOfRangeError = 99;

// number of menu items
static int NBMENUITEMS = 11;

enum Action
{
	
	ActionExit,
	ActionInsertSingleValue,
	ActionDeleteSingleValue,
	ActionPrintList,
	ActionClearList,
	ActionInsertMultipleValues,
	ActionDeleteMultipleValues,
	ActionInsertRange,
	ActionDeleteRange,
	ActionReverseList,
	ActionPrintListInfo
};

char* GetActionsDesc(enum Action action)
{
	char* output;
	if (action == ActionExit)
	{
		output = "Exit Program";
	}
	else if (action == ActionInsertSingleValue)
	{
		output = "Insert Value In List";
	}
	else if (action == ActionDeleteSingleValue)
	{
		output = "Delete Value From List";
	}
	else if (action == ActionPrintList)
	{
		output = "Print List";
	}
	else if (action == ActionClearList)
	{
		output = "Clear List";
	}
	else if (action == ActionInsertMultipleValues)
	{
		output = "Insert Multiple values in List";
	}
	else if (action == ActionDeleteMultipleValues)
	{
		output = "Delete Multiple values from List";
	}
	else if (action == ActionInsertRange)
	{
		output = "Insert Range in List";
	}
	else if (action == ActionDeleteRange)
	{
		output = "Delete Range from List";
	}
	else if (action == ActionReverseList)
	{
		output = "Reverse List";
	}
	else if (action == ActionPrintListInfo)
	{
		output = "Print List Info";
	}
	else
	{
		output = "Unknown Action";
	}
	return output;
}

static void PrintMenu()
{
	system("cls");
	printf("*****Double Linked List Program*****\n");
	printf("Please choose from the following options : \n");
	for (int i = 0; i < NBMENUITEMS; i++)
	{
		printf("	 %d : %s\n", i, GetActionsDesc(i));
	}
}

static void PrintMenuOld()
{
    system("cls");
    printf("*****Double Linked List Program*****\n");
    printf("Please choose from the following options : \n");
	printf("	 0 : Exit Program\n");
    printf("	 1 : Insert Value In List\n");
    printf("	 2 : Delete Value From List\n");
    printf("	 3 : Print List\n");
    printf("	 4 : Clear List\n");
    printf("	 5 : Insert Multiple values in List\n");
    printf("	 6 : Delete Multiple values from List\n");
    printf("	 7 : Insert Range in List\n");
    printf("	 8 : Delete Range from List\n");
	printf("	 9 : Reverse List\n");
	printf("	10 : List Info\n");
}

// gets input from keyboard and convert to integer if possible
// updates error status pointer errstatus to 0 if input invalid
static int getInputValAsInt(int* errstatus)
{
    char charinput[10];
    char* garbagestring;
    bool invalidinput = 1;
    int inputval;

    scanf_s("%9s", &charinput, 9);
    inputval = strtol(charinput, &garbagestring, 10);
    // printf("Your choice was : %d!\n", choice);
    // PressEnterToContinue();
    // input is invalid if the invalid part of input is equal to the whole input
    invalidinput = (garbagestring == charinput);
    if(invalidinput)
	{
	    printf("invalidinput = %s, the input was invalid.", garbagestring);
	    *errstatus = 0;
	}
    else
	{
	    *errstatus = 1;
	}

    return inputval;
}

static int getMenuChoice(int* errstatus)
{
    printf("Menu choice : ");
    int output = getInputValAsInt(errstatus);
    printf("\n");
    // catching additional error that the input while integer is outside of range allowed for menu choices
    if(*errstatus == 1)
	{
	    if((output < 0) || (output > 10))
		{
		    *errstatus = MenuOutOfRangeError;
		}
	}
    return output;
}

// flushes buffer and wait for getchar to resume
static void PressEnterToContinue()
{
    int c;
    do
	{
	    c = getchar();
	}
    while(c != '\n' && c != EOF);
    printf("Press ENTER to continue.\n");
    getchar();
}

static HEADER* MenuActionInsertSingleValue(HEADER* head) 
{
	int inputval;
	int errstatus;
	printf("Input Single Value to Insert:  ");
	inputval = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nInserting value: %d...", inputval);
		head = InsertElement(head, inputval);
		printf("\nValue Inserted.\n");
	}
	else
	{
		printf("\nInput error. No value Inserted.\n");
	}
	return head;
}

static HEADER* MenuActionInsertMultipleValues(HEADER* head)
{
	int inputval;
	int errstatus;
	printf("Input Number of Values to Insert:  \n");
	int NbValToInsert = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		for (int i = 0; i < NbValToInsert; i++)
		{
			printf("\nInput Value %d / %d: ", i + 1, NbValToInsert);
			inputval = getInputValAsInt(&errstatus);
			if (errstatus == 1)
			{
				printf("\nInserting value: %d...", inputval);
				head = InsertElement(head, inputval);
				printf("\nValue Inserted.");
			}
			else
			{
				printf("\nInput error. Value will not be inserted.");
			}
		}
		printf("\nValid values Inserted.\n");
	}
	else
	{
		printf("\nInput error. No value will be inserted.\n");
	}
	return head;
}

static HEADER* MenuActionInsertRange(HEADER* head)
{
	int errstatus;
	printf("Input Start of Range - inclusive - to Insert:  ");
	int RangeStartForIns = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\n");
		printf("Input End of Range - exclusive - to Insert:  ");
		int RangeEndForIns = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			printf("\nRange to be Inserted Defined as [%d - %d[.\n", RangeStartForIns, RangeEndForIns);
			for (int i = RangeStartForIns; i < RangeEndForIns; i++)
			{
				head = InsertElement(head, i);
			}
			printf("\nRange Inserted.\n");
		}
		else
		{
			printf("\nInput error for End Range. No value will be inserted.\n");
		}
	}
	else
	{
		printf("\nInput error for Start Range. No value will be inserted.\n");
	}
	return head;
}

static HEADER* MenuActionDeleteSingleValue(HEADER* head)
{
	int inputval;
	int errstatus;
	printf("Input Single Value to Delete:  ");
	inputval = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nDeleting value: %d...", inputval);
		head = DeleteElement(head, inputval);
		printf("\nValue Deleted.\n");
	}
	else
	{
		printf("Input error. No value Deleted.\n");
	}
	return head;
}

static HEADER* MenuActionDeleteMultipleValues(HEADER* head)
{
	int inputval;
	int errstatus;
	printf("Input Number of Values to Delete:  ");
	int NbValToDelete = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		for (int i = 0; i < NbValToDelete; i++)
		{
			printf("\nValue To Be Deleted %d / %d: ", i + 1, NbValToDelete);
			inputval = getInputValAsInt(&errstatus);
			if (errstatus == 1)
			{
				printf("\nDeleting value: %d...", inputval);
				head = DeleteElement(head, inputval);
				printf("\nValue Deleted.\n");
			}
			else
			{
				printf("\nInput error. Value will not be deleted.\n");
			}
		}
		printf("\nValid values Deleted.\n");
	}
	else
	{
		printf("\nInput error. No value will be deleted.\n");
	}
	return head;
}

static HEADER* MenuActionDeleteRange(HEADER* head)
{
	int errstatus;
	printf("Input Start of Range - inclusive - to Delete:  ");
	int RangeStartForDel = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nInput End of Range - exclusive - to Delete:  ");
		int RangeEndForDel = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			printf("\nRange to be Deleted Defined as [%d - %d[.\n", RangeStartForDel, RangeEndForDel);
			for (int i = RangeStartForDel; i < RangeEndForDel; i++)
			{
				head = DeleteElement(head, i);
			}
			printf("\nRange Deleted.\n");
		}
		else
		{
			printf("\nInput error for End Range. No value will be deleted.\n");
		}
	}
	else
	{
		printf("\nInput error for Start Range. No value will be deleted.\n");
	}
	return head;
}

static void MenuActionPrintList(HEADER* head)
{
	// PrintList(head);
	PrintByChunks(head);
	printf("List Printed.\n");
}

static HEADER* MenuActionReverseList(HEADER* head)
{
	head = ReverseList(head);
	printf("List Reversed.\n");
	return head;
}

static void MenuActionPrintListInfo(HEADER* head)
{
	PrintListInfo(head);
}

static HEADER* MenuActionClearList(HEADER* head)
{
	head = ClearList(head);
	//TODO modify so that reaffectation is not necessary
	printf("List Cleared.\n");
	return head;
}


// Carry out choice from user input
static HEADER* carryOutChoice(HEADER* head, int choice)
{
    switch(choice)
	{
	case 0:
	    printf("Exiting Program.\n");
	    break;
	case 1:
		head = MenuActionInsertSingleValue(head);
	    break;
	case 2:
		head = MenuActionDeleteSingleValue(head);
	    break;
	case 3:
		MenuActionPrintList(head);
	    break;
	case 4:
		head = MenuActionClearList(head);
	    break;
	case 5:
		head = MenuActionInsertMultipleValues(head);
	    break;
	case 6:
		head = MenuActionDeleteMultipleValues(head);
	    break;
	case 7:
		head = MenuActionInsertRange(head);
	    break;
	case 8:
		head = MenuActionDeleteRange(head);
	    break;
	case 9:
		head = MenuActionReverseList(head);
		break;
	case 10:
		MenuActionPrintListInfo(head);
		break;
	}
    PressEnterToContinue();
	return(head);
}

// Menu Loop for program : 
// Prints out Menu then accepts inputs until 0 is pressed
void MenuLoop() {
    HEADER* head = CreateEmptyList();

    int choice;
    int errstatus;
    do
	{
	    PrintMenu();
	    choice = getMenuChoice(&errstatus);
	    if(errstatus == 1)
		{
		    head = carryOutChoice(head, choice);
		}
	    else
		{
		    if(errstatus == MenuOutOfRangeError)
			{
			    printf("Menu Input Error: Menu Input was integer but not between 0 and 10.\n");
			}
		    else
			{
			    printf("Menu Input Error: Menu Input could not succesfully be interpreted as integer "
			           "value.\n");
			}
		    choice = ContinueDefault;
		    PressEnterToContinue();
		}
	}
    while(choice != 0);
}