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

static void PrintMenu()
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

// Carry out choice from user input
static HEADER* carryOutChoice(HEADER* head, int choice)
{
    int errstatus;
    int inputval;
    switch(choice)
	{
	case 0:
	    printf("Exiting Program.\n");
	    break;
	case 1:
	    printf("Input Single Value to Insert:  ");
	    inputval = getInputValAsInt(&errstatus);
	    if(errstatus == 1)
		{
			head = InsertElement(head, inputval);
		    printf("Value Inserted.\n");
		}
	    else
		{
		    printf("Input error. No value Inserted.\n");
		}
	    break;
	case 2:
	    printf("Input Single Value to Delete:  ");
	    inputval = getInputValAsInt(&errstatus);
	    if(errstatus == 1)
		{
			head = DeleteElement(head, inputval);
		    printf("Value Deleted.\n");
		}
	    else
		{
		    printf("Input error. No value Deleted.\n");
		}
	    break;
	case 3:
	    // PrintList(head);
	    PrintByChunks(head);
	    printf("List Printed.\n");
	    break;
	case 4:
	    head = ClearList(head);
		//TODO modify so that reaffectation is not necessary
	    printf("List Cleared.\n");
	    break;
	case 5:
	    printf("Input Number of Values to Insert:  \n");
	    int NbValToInsert = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			for (int i = 0; i < NbValToInsert; i++)
			{
				printf("Input Value %d / %d: ", i + 1, NbValToInsert);
				inputval = getInputValAsInt(&errstatus);
				if (errstatus == 1)
				{
					head = InsertElement(head, inputval);
				}
				else
				{
					printf("\nInput error. Value will not be inserted.\n");
				}
			}
			printf("Valid values Inserted.\n");
		}
		else
		{
			printf("\nInput error. No value will be inserted.\n");
		}
	    break;
	case 6:
	    printf("Input Number of Values to Delete:  ");
	    int NbValToDelete = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			for (int i = 0; i < NbValToDelete; i++)
			{
				printf("Value To Be Deleted %d / %d: ", i + 1, NbValToDelete);
				inputval = getInputValAsInt(&errstatus);
				if (errstatus == 1)
				{
					head = DeleteElement(head, inputval);
				}
				else
				{
					printf("\nInput error. Value will not be deleted.\n");
				}
			}
			printf("Valid values Deleted.\n");
		}
		else
		{
			printf("\nInput error. No value will be deleted.\n");
		}
	    break;
	case 7:
	    printf("Input Start of Range - inclusive - to Insert:  ");
	    int RangeStartForIns = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			printf("\n");
			printf("Input End of Range - exclusive - to Insert:  ");
			int RangeEndForIns = getInputValAsInt(&errstatus);
			if (errstatus == 1)
			{
				printf("Range to be Inserted Defined.\n");
				for (int i = RangeStartForIns; i < RangeEndForIns; i++)
				{
					head = InsertElement(head, i);
				}
				printf("Range Inserted.\n");
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
	    break;
	case 8:
	    printf("Input Start of Range - inclusive - to Delete:  ");
	    int RangeStartForDel = getInputValAsInt(&errstatus);
		if (errstatus == 1)
		{
			printf("\n");
			printf("Input End of Range - exclusive - to Delete:  ");
			int RangeEndForDel = getInputValAsInt(&errstatus);
			if (errstatus == 1)
			{
				printf("Range to be Deleted Succesfully Defined.\n");
				for (int i = RangeStartForDel; i < RangeEndForDel; i++)
				{
					head = DeleteElement(head, i);
				}
				printf("Range Deleted.\n");
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
	    break;
	case 9:
		head = ReverseList(head);
		printf("List Reversed.\n");
		break;
	case 10:
		PrintListInfo(head);
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