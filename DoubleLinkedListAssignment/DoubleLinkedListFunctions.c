#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"

//Maximum number of elements to print out
static int NMaxPrint = 100;

//Maximum number of elements to print out in each line
static int ChunkSize = 10;

// Gets next element depending on order
static LISTITEM* GetNext(HEADER* head, LISTITEM* item)
{
	if (head->order == asc) 
	{
		return item->fwd;
	}
	else if (head->order == desc) 
	{
		return item->bck;
	}
	else
	{
		return (LISTITEM*)NULL;
	}
}

// Gets first element in list depending on order
static LISTITEM* GetFirst(HEADER* head) 
{
	if (head->order == asc) 
	{
		return head->smallest;
	}
	else if (head->order == desc) 
	{
		return head->greatest;
	}
	else
	{
		return (LISTITEM*)NULL;
	}
}

// Gets last element in list depending on order
static LISTITEM* GetLast(HEADER* head) 
{
	if (head->order == asc) 
	{
		return head->greatest;
	}
	else if (head->order == desc) 
	{
		return head->smallest;
	}
	else
	{
		return (LISTITEM*)NULL;
	}
}

// Checks whether a list is empty
bool IsEmptyList(HEADER* head)
{
    return ((head->smallest == (LISTITEM*)head));
}

// Prints all values of linked list with header head - Verbose
void PrintListVerbose(HEADER* head)
{
    printf("***START PRINT*** \n");
    if(!IsEmptyList(head))
	{
	    LISTITEM* temp = GetFirst(head);
	    int i = 0;
	    while(i < NMaxPrint)
		{
		    printf("Val number %d = %d\n", i + 1, temp->val);
		    if(temp == GetLast(head))
			{
			    break;
			}
		    else
			{
			    i++;
			    temp = GetNext(head,temp);
			}
		}
	    if(i == NMaxPrint)
		{
		    printf("\n Warning: Number of values in list is greater than NMaxPrint = %d. Print interrupted.\n",
		        NMaxPrint);
		}
	}
    else
	{
	    printf("No elements to print (empty list).\n");
	}
    printf("***END PRINT*** \n");
}

// Prints all values of linked list with header head
void PrintList(HEADER* head)
{
    printf("[");
    if(!IsEmptyList(head))
	{
	    LISTITEM* temp = GetFirst(head);
	    int i = 0;
	    while(i < NMaxPrint)
		{
		    printf("%d", temp->val);
		    if(temp == GetLast(head))
			{
			    break;
			}
		    else
			{
			    i++;
			    temp = GetNext(head,temp);
			    printf(", ");
			}
		}
	    if(i == NMaxPrint)
		{
		    printf("...]\n");
		    printf("Warning: Number of values in list is greater than NMaxPrint = %d. Print interrupted.\n",
		        NMaxPrint);
		}
	    else
		{
		    printf("]\n");
		}
	}
    else
	{
	    printf("]\n");
	}
}

// prints NbItems from list headed by head starting at position pos
// returns boolean true if the last element printed was head->greatest (print finished)
// updates the incoming pos pointer to the last element printed
// this assumes list is not empty and pos is an item of list
static bool PrintNItemsFromPosAndUpdate(HEADER* head, LISTITEM** pos, int NbItems)
{
    printf("[");
    if(*pos == GetFirst(head))
	{
	    printf("     ");
	}
    bool PrintFinished = 0;
    bool LastReached = 0;
    bool NItemsPrinted = 0;
    int i = 1;
    if(*pos != GetFirst(head))
	{
	    printf("..., ");
	}
    while(!PrintFinished)
	{
	    printf("%4d", (*pos)->val);
		//we reached the last element in the list?
	    LastReached = (*pos == GetLast(head));
		//NbItems have been printed?
	    NItemsPrinted = (i == NbItems);
		//The print is finished if either we reached the last element in the list, or NbItems have been printed
	    PrintFinished = (LastReached || NItemsPrinted);
		//if the print is not finished, update i and pos
	    if(!PrintFinished)
		{
		    i++;
		    *pos = GetNext(head,*pos);
		}
		// there are still elements to print in the list, that will be printed at the next iteration
		// so we print ", " to separate with next value
	    if(!LastReached)
		{
		    printf(", ");
		}
	}
    // Print is finished
    if(!LastReached)
	{
	    // there are still elements to print in the list, that will not be printed here (PrintFinished = true)
		// so we print "..." to reflect that situation
	    printf("...");
	}
    printf("]\n");
    return LastReached;
}


// Prints whole list headed by head in chunks of size NbItems
void PrintByNbItemsChunks(HEADER* head, int NbItems)
{
    if(!IsEmptyList(head))
	{
	    LISTITEM* pos = GetFirst(head);
	    bool LastReached = 0;
	    while(!LastReached)
		{
		    LastReached = PrintNItemsFromPosAndUpdate(head, &pos, NbItems);
		    if(!LastReached)
			{
			    // we move pos to the element to be printed first in the next chunk
			    pos = GetNext(head,pos);
			}
		}
	}
    else
	{
	    printf("[]\n");
	}
}

// Prints whole list headed by head in chunks of size Chunksize
void PrintByChunks(HEADER* head)
{
    PrintByNbItemsChunks(head, ChunkSize);
}

// Creates an Empty List
HEADER* CreateEmptyList()
{
    HEADER* head = malloc(sizeof(HEADER));
	head->order = asc;
    head->smallest = (LISTITEM*)head;
    head->greatest = head->smallest;
    return head;
}

// Clears a List
HEADER* ClearList(HEADER* head)
{
	if (!IsEmptyList(head))
	{
		if (head->smallest!=head->greatest) 
		{
			LISTITEM* temp = head->smallest->fwd;
			bool ListFinished = 0;
			while (!ListFinished)
			{
				ListFinished = (temp == head->greatest);
				free(temp->bck);
				if (!ListFinished)
				{
					temp = temp->fwd;
				}
			}
		}
		free(head->greatest);
	}
	enum Order saveheadorder = head->order;
	head = CreateEmptyList();
	head->order = saveheadorder;
	return head;
}

// Fully Deletes a List
static void DeleteList(HEADER* head) {
	ClearList(head);
	free(head);
}

// Creates new LISTITEM elt containing value val
LISTITEM* CreateEltFromVal(int val)
{
    LISTITEM* newelt = malloc(sizeof(LISTITEM));
    newelt->val = val;
    return newelt;
}

// Returns element in head that has smallest value greater or equal to val
// static as it requires list to be in ascending order
static LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val)
{
    LISTITEM* temp;
    if((IsEmptyList(head)) || head->greatest->val < val)
	{
	    // If List is empty, or all elements in list are smaller than val (aka there is no elements greater in
	    // list), we return pointer to NULL  this works only if list is ordered by ascending val going forward through
	    // list
	    temp = NULL;
	}
    else
	{
	    // the list is not empty and there is an elt in it with value greater or equal than val
	    bool posfound = 0;
	    bool loopedthrough = 0;
	    bool searchfinished = 0;

	    temp = head->smallest;
	    // enter loop if search is not finished
	    while(!searchfinished)
		{
		    posfound = (temp->val >= val); // elt found if its value is greater or equal than value searched
		    loopedthrough = (temp == head->greatest); // loop through list over if temp is last element in list
		    searchfinished =
		        (posfound || loopedthrough); // search finished if elt found or loop through list over
		    if(!searchfinished)
			{ // proceed to next elt in list ifsearch is not finished //&& !loopedthrough
			    temp = temp->fwd;
			}
		}
	}
    return temp;
}

// Inserts a new element of value valtoins at the start of the list maintaining branching, without check on value.
// Static so end user in main cannot insert an element out of order or duplicate.
static void InsertAtStart(HEADER* head, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
    newelt->fwd = head->smallest; // newelt points forward to soon-to-be-old first element
    head->smallest->bck = newelt; // soon-to-be-old first element points back to newelt
    head->smallest = newelt;      // newelt is new first element
}

// outputs new list that is reverse of input list
// assumes input list has valid element order with respect to claimed order
HEADER* ReverseList(HEADER* head)
{
	if (head->order == asc)
	{
		head->order = desc;
	}
	else if (head->order == desc)
	{
		head->order = asc;
	}
	return head;
}

// Inserts a new element of value valtoins at the end of the list maintaining branching, without check on value.
// Static so end user in main cannot insert an element out of order or duplicate.
static void InsertAtEnd(HEADER* head, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
    newelt->bck = head->greatest; // newelt points backward to soon-to-be-old last element
    head->greatest->fwd = newelt; // soon-to-be-old last element points forward to newelt
    head->greatest = newelt;      // newelt is new last element
}

// Inserts an element before element nextelt. Assumes that nextelt exists in list.
// Static so end user in main cannot insert an element out of order or duplicate.
static void InsertBefore(HEADER* head, LISTITEM* nextelt, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
    newelt->bck = nextelt->bck; // branch new element back, maintaining link to next element soon-to-be-old prev element
    newelt->fwd = nextelt;      // branch new element forward to next element
    nextelt->bck->fwd = newelt; // branch next elt old prev element forward to new elt
    nextelt->bck = newelt;      // branches next element back to new element
}

// Inserts an Element in forward order based on its value, updating branching
// Requires list values to be in ascending order going forward
HEADER* InsertElement(HEADER* head, int valtoins)
{
    LISTITEM* nextelt = GetSmallestGreaterEltByVal(head, valtoins);
    // printf("Attemping to insert elt with value %d...\n", valtoins);
    if(nextelt == NULL)
	{
	    // there is no element in list greater than the one to insert.
	    // Therefore : Insert Element at End
	    InsertAtEnd(head, valtoins);
	}
    else if(nextelt->val == valtoins)
	{
	    // There already is elt with value valtoins in the list
	    // Therefore : we do nothing
	    printf("Value %d is already in the list and will not be inserted.\n", valtoins);
	}
    else
	{
	    if(nextelt == head->smallest)
		{
		    // First element in the list is greater than val to insert
		    // Therefore : Insert Element at Start
		    InsertAtStart(head, valtoins);
		}
	    else
		{
		    // Smallest greater element is list element neither first nor last
		    // Therefore : insert new element before that element, updating branching
		    InsertBefore(head, nextelt, valtoins);
		}
	}
    // printf("Updated List: \n");
    // PrintList(head);
	return head;
}

// Deletes One Element with value val, updating branching
// requires list to be in ascending order because of use of GetSmallestGreaterEltByVal to get to element
HEADER* DeleteElement(HEADER* head, int valtodel)
{
    // printf("Attemping to delete elt with value %d...\n", valtodel);
    LISTITEM* elttodel = GetSmallestGreaterEltByVal(head, valtodel);
    if((elttodel == NULL) || (elttodel->val != valtodel))
	{
	    printf("There is no element with value %d in the list.\n", valtodel);
	}
    else
	{
	    if(elttodel == head->smallest)
		{
		    head->smallest = elttodel->fwd; // branch head first to old 2nd element - elttodel now inaccessible
		                                 // going through list
		}
	    else if(elttodel == head->greatest)
		{
		    head->greatest = elttodel->bck; // branch head last to old one but last element - elttodel now
		                                // inaccessible going through list
		}
	    else
		{
		    elttodel->bck->fwd = elttodel->fwd; // branch forward around element deleted - elttodel is now
		                                        // inaccessible going forward through list
		    elttodel->fwd->bck = elttodel->bck; // branch backward around element to be deleted - elttodel now
		                                        // inacessible going backward through list
		}
	    free(elttodel); // free memory still held by elttodel
	}
    // printf("Updated List: \n");
    // PrintList(head);
	return head;
}

// Gets descriptive string for list order
static char* GetOrderDesc(enum Order order) 
{
	char* output;
	if (order == asc) 
	{
		output = "Ascending";
	}
	if (order == desc)
	{
		output = "Descending";
	}
	return output;
}

// Gets number of elements in list
static int GetListLength(HEADER* head)
{
	int output = 0;
	if (!IsEmptyList(head))
	{
		for (LISTITEM* temp = head->smallest; temp != head->greatest; temp = temp->fwd)
		{
			output++;
		}
		output++;
	}
	return output;
}

// Prints out info on list head
void PrintListInfo(HEADER* head) 
{
	printf("Order: %s\n", GetOrderDesc(head->order));
	printf("Number of elements: %d\n", GetListLength(head));
}