//////////////////
// MENU FUNCTIONS//
//////////////////
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"
#include "DoubleLinkedListFunctions.h"

//continues looping through menu after invalid menu choice 1 - or not
static bool ContinueAfterMenuChoiceInputError = 1;

//error status given if integer not in range for menu items
static int MenuOutOfRangeError = 99;

// Actions available, Direction will determine Direction of print in PrintMenu. 
// Enum is defined to start at 0 then a dummy action NbAction is added at the end that will be equal to the number of relevant actions
typedef enum 
{
	ActionExit=0,
	ActionPrintList,
	ActionPrintListInfo,
	ActionReverseDirection,
	ActionInsertSingleValue,
	ActionDeleteSingleValue,
	ActionInsertMultipleValues,
	ActionDeleteMultipleValues,
	ActionInsertRange,
	ActionDeleteRange,
	ActionMakeValidOrderedList,
	ActionClearList,
	ActionInsertAtEndUnchecked,
	NbActions
} Action;

char* GetActionsdesc(Action action)
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
	else if (action == ActionReverseDirection)
	{
		output = "Reverse Print Direction";
	}
	else if (action == ActionPrintListInfo)
	{
		output = "Print List Info";
	}
	else if (action == ActionInsertAtEndUnchecked)
	{
		output = "Insert at End Without check on Direction.";
	}
	else if (action == ActionMakeValidOrderedList)
	{
		output = "Change List to Valid Ordered List if not Valid";
	}
	else
	{
		output = "Unattributed Action";
	}
	return output;
}

//Direction of Menu dictated by enum Actions Direction and fact that loop is going from 0 to NBMENUITEMS fwdending
static void PrintMenu()
{
	system("cls");
	printf("*****Double Linked List Program*****\n");
	printf("Please choose from the following options : \n");
	//NbAction last element of enum Action, dummy action used to access the number of relevant element in Actiont 
	for (Action action = 0; action < NbActions; action++)
	{
		printf("	 %2d : %s\n", action, GetActionsdesc(action));
	}
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
	    printf("Input '%s'is invalid.\n", garbagestring);
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
	    if((output < 0) || (output >= NbActions))
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

static void MenuActionInsertSingleValue(HEADER* head) 
{
	int inputval;
	int errstatus;
	printf("Input Single Value to Insert:  ");
	inputval = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nInserting value: %d...", inputval);
		InsertNewElementByVal(head, inputval);
		printf("\nValue Inserted.\n");
	}
	else
	{
		printf("\nInput error. No value Inserted.\n");
	}
}

static void MenuActionInsertAtEndUnchecked(HEADER* head)
{
	int inputval;
	int errstatus;
	printf("Warning : Inserting a value at end will not check for Direction of values.\n ");
	printf("Input Single Value to Insert At End:  ");
	inputval = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nInserting value at End: %d...", inputval);
		InsertAtEndUnchecked(head, inputval);
		printf("\nValue Inserted at End.\n");
	}
	else
	{
		printf("\nInput error. No value Inserted.\n");
	}
}


static void MenuActionMakeValidOrderedList(HEADER** head)
{
	MakeValidOrderedList(head);
	printf("\nList Made Valid (duplicates removed, reordered).\n");
}

static void MenuActionInsertMultipleValues(HEADER* head)
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
				InsertNewElementByVal(head, inputval);
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
}

static void MenuActionInsertRange(HEADER* head)
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
				InsertNewElementByVal(head, i);
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
}

static void MenuActionDeleteSingleValue(HEADER* head)
{
	int inputval;
	int errstatus;
	printf("Input Single Value to Delete:  ");
	inputval = getInputValAsInt(&errstatus);
	if (errstatus == 1)
	{
		printf("\nDeleting value: %d...", inputval);
		DeleteElementByVal(head, inputval);
		printf("\nValue Deleted.\n");
	}
	else
	{
		printf("Input error. No value Deleted.\n");
	}
}

static void MenuActionDeleteMultipleValues(HEADER* head)
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
				DeleteElementByVal(head, inputval);
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
}

static void MenuActionDeleteRange(HEADER* head)
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
			DeleteElementByValRange(head,RangeStartForDel,RangeEndForDel);
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
}

static void MenuActionPrintList(HEADER* head)
{
	// PrintList(head);
	PrintByChunks(head);
	printf("List Printed.\n");
}

static void MenuActionReverseDirection(HEADER* head)
{
	ReverseDirection(head);
	printf("List Print Direction Reversed.\n");
	//return head;
}

static void MenuActionPrintListInfo(HEADER* head)
{
	PrintListInfo(head);
}

static void MenuActionClearList(HEADER** head)
{
	ClearList(head);
	//TODO modify so that reaffectation is not necessary
	printf("List Cleared.\n");
}



// Carry out choice from user input
static void carryOutChoice(HEADER** head, Action choice)
{
    switch(choice)
	{
	case ActionExit:
	    printf("Exiting Program.\n");
	    break;
	case ActionInsertSingleValue:
		MenuActionInsertSingleValue(*head);
	    break;
	case ActionDeleteSingleValue:
		MenuActionDeleteSingleValue(*head);
	    break;
	case ActionPrintList:
		MenuActionPrintList(*head);
	    break;
	case ActionClearList:
		MenuActionClearList(head);
	    break;
	case ActionInsertMultipleValues:
		MenuActionInsertMultipleValues(*head);
	    break;
	case ActionDeleteMultipleValues:
		MenuActionDeleteMultipleValues(*head);
	    break;
	case ActionInsertRange:
		MenuActionInsertRange(*head);
	    break;
	case ActionDeleteRange:
		MenuActionDeleteRange(*head);
	    break;
	case ActionReverseDirection:
		MenuActionReverseDirection(*head);
		break;
	case ActionPrintListInfo:
		MenuActionPrintListInfo(*head);
		break;
	case ActionInsertAtEndUnchecked:
		MenuActionInsertAtEndUnchecked(*head);
		break;
	case ActionMakeValidOrderedList:
		MenuActionMakeValidOrderedList(head);
		break;
	default: 
		printf("Not a valid choice.\n");
	}
    PressEnterToContinue();
}

// Menu Loop for program : 
// Prints out Menu then accepts inputs until 0 is pressed
void MenuLoop() {
    HEADER* head = CreateEmptyList();

    int choice;
    int errstatus;
	bool ContinueLoop;
    do
	{
	    PrintMenu();
	    choice = getMenuChoice(&errstatus);
	    if(errstatus == 1)
		{
		    carryOutChoice(&head, choice);
		}
	    else
		{
		    if(errstatus == MenuOutOfRangeError)
			{
			    printf("Menu Input Error: Menu Input should be integer in [0 - %d] range.\n", (NbActions-1));
			}
		    else
			{
			    printf("Menu Input Error: Menu Input could not succesfully be interpreted as integer "
			           "value.\n");
			}
			if (!ContinueAfterMenuChoiceInputError)
			{
				printf("Exiting Program...\n");
			}
		    PressEnterToContinue();
		}
		//Loop Continues if valid input choice not equal to zero, or invalid choice and ContinueAfterInputError is true
		ContinueLoop = (choice != 0) && ((errstatus == 1) || (ContinueAfterMenuChoiceInputError));
	}
    while(ContinueLoop);
}