#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ErrorCodes.h"
#include "ParameterConstants.h"
#include "Types.h"

#include "DoubleLinkedListFunctions.h"
#include "MenuFunctions.h"

int main()
{
    // random comment to test push from codelite git
    HEADER* head = CreateEmptyList();

    int choice;
    int errstatus;
    do
	{
	    PrintMenu();
	    choice = getMenuChoice(&errstatus);
	    if(errstatus == 1)
		{
		    carryOutChoice(head, choice);
		}
	    else
		{
		    if(errstatus == MenuOutOfRangeError)
			{
			    printf("Menu Input Error: Menu Input was integer but not between 0 and 8.\n");
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

    return 0;
}