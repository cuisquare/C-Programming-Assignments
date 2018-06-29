#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"

//Maximum number of elements to print out
static int NMaxPrint = 100;

//Maximum number of elements to print out in each line
static int ChunkSize = 10;

// Gets next element depending on Direction
static LISTITEM* GetNext(HEADER* head, LISTITEM* item)
{
	if (head->direction == fwd) 
	{
		return item->fwd;
	}
	else if (head->direction == bck) 
	{
		return item->bck;
	}
	else
	{
		return item->fwd;
	}
}

// Gets first element in list depending on Direction
static LISTITEM* GetFirst(HEADER* head) 
{
	if (head->direction == fwd) 
	{
		return head->smallest;
	}
	else if (head->direction == bck) 
	{
		return head->greatest;
	}
	else
	{
		return head->smallest;
	}
}

// Gets last element in list depending on Direction
static LISTITEM* GetLast(HEADER* head) 
{
	if (head->direction == fwd) 
	{
		return head->greatest;
	}
	else if (head->direction == bck) 
	{
		return head->smallest;
	}
	else
	{
		return head->greatest;
	}
}

// Checks whether a list is empty
bool IsEmptyList(HEADER* head)
{
    return ((head->smallest == (LISTITEM*)NULL));
}

// Gets number of elements in list
static int GetListLength(HEADER* head)
{
	int ListLength = 0;
	if (!IsEmptyList(head))
	{
		for (LISTITEM* temp = head->smallest; temp != NULL; temp = temp->fwd)
		{
			ListLength++;
		}
	}
	return ListLength;
}

// Checks if a list is valid in fwdending Direction
static bool IsAValidOrderedList(HEADER* head)
{
	bool output = true;
	if (GetListLength(head)>1)
	{
		for (LISTITEM* temp = head->smallest->fwd; temp != NULL; temp = temp->fwd)
		{
			if (temp->val <= (temp->bck)->val)
			{
				output = false;
				break;
			}
		}
	}
	return output;
}

// changes Direction of head
HEADER* ReverseDirection(HEADER* head)
{
	if (head->direction == fwd)
	{
		head->direction = bck;
	}
	else if (head->direction == bck)
	{
		head->direction = fwd;
	}
	return head;
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
static bool PrintNItemsFromPosAndUpdate(HEADER* head, LISTITEM** pos, int NbItemsToPrint)
{
    printf("[");
    if(*pos == GetFirst(head))
	{
	    printf("     ");
	}
	else
	{
	    printf("..., ");
	}
	
    bool ChunkPrintFinished = 0;
    bool LastReached = 0;
    bool NbItemsToPrintPrinted = 0;
    int i = 0;

    while(!ChunkPrintFinished)
	{
	    printf("%4d", (*pos)->val);
		i++;
		//we reached the last element in the list?
	    LastReached = (*pos == GetLast(head));
		//NbItems have been printed?
	    NbItemsToPrintPrinted = (i == NbItemsToPrint);
		//The print is finished if either we reached the last element in the list, or NbItems have been printed
	    ChunkPrintFinished = (LastReached || NbItemsToPrintPrinted);
		//if the print is not finished, update i and pos
	    if(!ChunkPrintFinished)
		{
		    *pos = GetNext(head,*pos);
		}
		// there are still elements to print in the list, that will be printed at the next iteration
		// so we print ", " to separate with next value
	    if(!LastReached)
		{
		    printf(", ");
		}
	}
    // Print of Chunk is finished
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

//Reset already existing list without erasing possible previously linked element
HEADER* ResetListNoClear(HEADER* head)
{
	head->smallest =  NULL;
    head->greatest =  NULL; 
    return head;
}

// Creates an Empty List
HEADER* CreateEmptyList()
{
    HEADER* head = malloc(sizeof(HEADER));
	//default Direction is fwd. 
	head->direction = fwd;
    head = ResetListNoClear(head);
    return head;
}

// Clears a List
HEADER* ClearList(HEADER* head)
{
	if (!IsEmptyList(head))
	{
		if (GetListLength(head)>1)
		{
			LISTITEM* temp = head->smallest->fwd;
			while (temp)
			{
				free(temp->bck);
				temp = temp->fwd;
			}
		}
		free(head->greatest);
		head = CreateEmptyList();
	}
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
	newelt->bck = NULL;
	newelt->fwd= NULL;
    return newelt;
}

// outputs integer matching index of searched item
// with index defined as 0 for head->smallest and incremented going fwd the list
// returns -1 if the element was not found in the list
static int GetIndexFromElt(HEADER* head, LISTITEM* item) 
{
	int outputint = 0;
	bool ItemFound = 0;
	for (LISTITEM* temp = head->smallest;temp;temp = temp->fwd)
	{
		if (temp == item)
		{
			ItemFound = 1;
			break;
		}
		outputint++;
	}
	if (!ItemFound)
	{
		outputint = -1;
	}
	return outputint;
}

// Gets Element at corresponding Index or NULL if index out of range
static LISTITEM* GetEltByIndex(HEADER* head, int IndexSearched)
{
	LISTITEM* temp;
	bool IndexFound=0;
	
	if (!IsEmptyList(head))
	{
		LISTITEM* temp = head->smallest;
		int i = 0;
		for(temp= head->smallest; temp;temp=temp->fwd)
		{
			if (i==IndexSearched)
			{
				IndexFound = 1;
				break;
			}
			i++;
		}
	}
	if (!IndexFound)
	{
		temp = NULL;
	}
	return temp;
}

// Returns element in head that has value equal to val
static LISTITEM* GetFirstEqualEltByVal(HEADER* head, int inputval)
{
	//default output is NULL
	LISTITEM* output = NULL;
	if (!IsAValidOrderedList(head))
	{
		printf("Warning: the List is not validly Directioned - any value found might have a duplicate further in the list.\n");
	}
	// the list is not empty and there is an elt in it with value greater than, or equal to val
	if (!IsEmptyList(head))
	{
		// the list is not empty, a value might be found in list with val equal to inputval
		LISTITEM* temp;
		for (temp = head->smallest;temp;temp = temp->fwd)
		{
			if (temp->val == inputval) 
			{
				output = temp;
				break;
			}
		}
	}
	return output;
}

// outputs pointer to list of pointer to all elements in list head with val matching inputval
static LISTITEM** GetAllEqualEltByVal(HEADER* head, int inputval)
{
	LISTITEM** MatchingElements= malloc(GetListLength(head)*sizeof(LISTITEM*)); // or -static +GetListLength(head) gives warning "function returns address of local variable"
	//LISTITEM* MatchingElements[GetListLength(head)];
	int i = 0;	
	LISTITEM* temp;
	for (temp = head->smallest;temp;temp = temp->fwd)
	{
		if (temp->val == inputval)
		{
			MatchingElements[i]=temp;
			i++;
		}
	}
	realloc(MatchingElements,(i+1)*sizeof(LISTITEM*)); //reallocate size to match actual content of MatchingElements list plus 1 element
	MatchingElements[i]= (LISTITEM*) NULL;
	return MatchingElements;
}

// Returns element in head that has smallest value greater or equal to val
// static as it requires list to be in fwdending Direction of values going forward through list
static LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val)
{
	LISTITEM* temp = NULL;
	if (IsAValidOrderedList(head)) 
	{
		if(!(IsEmptyList(head)) && !(head->greatest->val < val))
		{
			// here the list is not empty and there is an elt in it with value greater than, or equal to val.
			for (temp = head->smallest;temp;temp = temp->fwd)
			{
				if (temp->val >= val)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("Warning: the List is not validly Directioned. Output of GetSmallestGreaterEltByVal will be NULL.");
	}
	return temp;
}

// Inserts a new element of value valtoins at the start of the list maintaining branching, without check on value.
// Static so end user in main cannot insert an element out of Direction or duplicate.
static void InsertSmallest(HEADER* head, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
	if (IsEmptyList(head))
	{
		head->smallest = newelt;
		head->greatest = newelt;
	}
	else
	{
		newelt->fwd = head->smallest; // newelt points forward to soon-to-be-old first element
		head->smallest->bck = newelt; // soon-to-be-old first element points back to newelt
		head->smallest = newelt;      // newelt is new first element
	}
}

// Inserts a new element of value valtoins at the end of the list maintaining branching, without check on value.
// Static so end user in main cannot insert an element out of Direction or duplicate.
static void InsertGreatest(HEADER* head, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
	if (IsEmptyList(head))
	{
		head->smallest = newelt;
		head->greatest = newelt;
	}
	else
	{
		newelt->bck = head->greatest; // newelt points backward to soon-to-be-old last element
		head->greatest->fwd = newelt; // soon-to-be-old last element points forward to newelt
		head->greatest = newelt;      // newelt is new last element
		//head->greatest->fwd = NULL; //makes next element from greatest NULL for looping //unecessary as bck and fwd of newelt is NULL from CreateEltFromVal
	}
}

HEADER* InsertAtEndUnchecked(HEADER* head, int valtoins)
{
	InsertGreatest(head, valtoins);
	return head;
}

// Inserts an element before element nextelt. Assumes that nextelt exists in list.
// Static so end user in main cannot insert an element out of Direction or duplicate.
static void InsertBefore(HEADER* head, LISTITEM* nextelt, int valtoins)
{
    LISTITEM* newelt = CreateEltFromVal(valtoins);
    newelt->bck = nextelt->bck; // branch new element back, maintaining link to next element soon-to-be-old prev element
    newelt->fwd = nextelt;      // branch new element forward to next element
    nextelt->bck->fwd = newelt; // branch next elt old prev element forward to new elt
    nextelt->bck = newelt;      // branches next element back to new element
}

// Inserts an Element in forward Direction based on its value, updating branching
// Requires list values to be in fwdending Direction going forward for the Direction to be meaningful
// if list is not Directioned, element is added at the end. 
HEADER* InsertElement(HEADER* head, int valtoins)
{
    LISTITEM* nextelt = GetSmallestGreaterEltByVal(head, valtoins);
    // printf("Attemping to insert elt with value %d...\n", valtoins);
    if(nextelt == NULL)
	{
	    // there is no element in list greater than the one to insert or list is not validly Directioned
	    // Therefore : Insert Element as new greatest
	    InsertGreatest(head, valtoins);
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
		    // Therefore : Insert Element as new smallest element
		    InsertSmallest(head, valtoins);
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

// deletes element in list
// requires that elettodel exists in the list otherwise meaningless
static HEADER* DeleteElementByRef(HEADER* head, LISTITEM* elttodel)
{
	if (elttodel == head->smallest)
		{
			head->smallest = elttodel->fwd; // branch head smallest to old 2nd element - elttodel now inaccessible
											// going through list
			head->smallest->bck = NULL; // necessary as it still points back to old head->smallest
		}
	else if (elttodel == head->greatest)
		{
			head->greatest = elttodel->bck; // branch head greatest to old one but last element - elttodel now
											// inaccessible going through list
			head->greatest->fwd =  NULL; // necessary as it still points fwd to old head->greatest
		}
	else
	{
		elttodel->bck->fwd = elttodel->fwd; // branch forward around element deleted - elttodel is now
											// inaccessible going forward through list
		elttodel->fwd->bck = elttodel->bck; // branch backward around element to be deleted - elttodel now
											// inacessible going backward through list
	}
	free(elttodel); // free memory still held by elttodel
	return head;
}


// Deletes One Element with value val, updating branching
// Multiple searches single deletion at each pass
static HEADER* DeleteElementByValMultipleSearch(HEADER* head, int valtodel)
{
    // printf("Attemping to delete elt with value %d...\n", valtodel);
	bool FinishedDeleting = false;
	bool DeletedAtLeastOne = false;
	while (!FinishedDeleting)
	{ 
		LISTITEM* elttodel = GetFirstEqualEltByVal(head, valtodel);
		FinishedDeleting = (elttodel == NULL);
		if (FinishedDeleting)
		{
			if (!DeletedAtLeastOne)
			{
				printf("There is no element with value %d in the list.\n", valtodel);
			}
		}
		else
		{
			if (GetListLength(head) > 1)
			{
				head = DeleteElementByRef(head,elttodel);
			}
			else
			{
				//there is only one element left in the list, we clear the list which includes 
				//reverting head->smallest and head->greatest to empty list attributes.
				head = ClearList(head);
			}
			DeletedAtLeastOne = true;
			printf("Deleted one instance of %d.\n", valtodel);
		}
	}
    // printf("Updated List: \n");
    // PrintList(head);
	return head;
}

// Deletes One Element with value val, updating branching
// Single search multiple deletions
HEADER* DeleteElementByVal(HEADER* head, int valtodel)
{
	// printf("Attemping to delete elt with value %d...\n", valtodel);
	bool NothingToDelete = ((IsAValidOrderedList) && ((valtodel < head->smallest->val) || (valtodel > head->greatest->val)));
	if (!NothingToDelete)
	{
		LISTITEM** EltsToDel = GetAllEqualEltByVal(head, valtodel);
		LISTITEM* temp = EltsToDel[0];
		int i = 0;
		while (temp)
		{
			if (GetListLength(head) > 1)
			{
				head = DeleteElementByRef(head, temp);
			}
			else
			{
				//there is only one element left in the list, we clear the list which includes 
				//reverting head->smallest and head->greatest to empty list attributes.
				head = ClearList(head);
			}
			i++;
			temp = EltsToDel[i];
		}
		printf("Deleted %d element", i);
		if (i > 1)
		{
			printf("s");
		}
		printf(".\n");
	}
	else
	{
		//printf("Value to delete %d out of range of ordered list [%d - %d], so cannot be deleted.",valtodel, head->smallest->val, head->greatest->val);
	}
	return head;
}

// Gets descriptive string for list Direction
static char* GetDirectionDesc(Direction direction)
{
	char* output;
	switch (direction)
	{
	case fwd:
		output = "forward";
		break;
	case bck:
		output = "backward";
		break;
	}
	return output;
}


// Takes a list in input and outputs a valid Ordered list
HEADER* MakeValidOrderedList(HEADER* head)
{
	HEADER* outputhead = head;
	if (!IsAValidOrderedList(head))
	{
		outputhead = CreateEmptyList();
		for (LISTITEM* temp = head->smallest;temp!=head->greatest;temp = temp->fwd) 
		{
			outputhead = InsertElement(outputhead,temp->val);
		}
		outputhead = InsertElement(outputhead,(head->greatest)->val);
		ClearList(head);
	}
	else
	{
		printf("List was already Directioned. No action taken.\n");
	}
	return outputhead;
}



// Prints out info on list head
void PrintListInfo(HEADER* head)
{
	printf("Number of elements: %d\n", GetListLength(head));
	printf("Valid Ordered List: %d\n", IsAValidOrderedList(head));
	printf("Print Direction: %s\n", GetDirectionDesc(head->direction));
}
