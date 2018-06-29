#ifndef DOUBLELINKEDLISTFUNCTIONS_H
#define DOUBLELINKEDLISTFUNCTIONS_H

// completion message print out
void PrintCompletionMessage(char* ActionCompleted, int NbElementsConcerned);

//Checks whether a list is empty
bool IsEmptyList(HEADER* head);

// Prints all values of linked list with header head - Verbose
void PrintListVerbose(HEADER* head);

//Prints all values of linked list with header head
void PrintList(HEADER* head);

//Prints all values of linked list with header head, by chunks of size NbItems
void PrintByNbItemsChunks(HEADER* head, int NbItems);

// Prints whole list headed by head in chunks of size Chunksize defined as parameter
void PrintByChunks(HEADER* head);

//Creates an Empty List
HEADER* CreateEmptyList();

// Clears a List
HEADER* ClearList(HEADER* head);

// Creates new LISTITEM elt containing value val
LISTITEM* CreateEltFromVal(int val);

// outputs new list that is reverse of input list
void ReverseDirection(HEADER** head);

//Unsafe insert of value at end of list
void InsertAtEndUnchecked(HEADER* head, int valtoins);

// Takes a list in input and outputs a valid Ordered list
HEADER* MakeValidOrderedList(HEADER* head);

// Inserts an Element in forward order based on its value, updating branching
// Requires list values to be in ascending order going forward
void InsertElement(HEADER* head, int valtoins);

// Deletes One Element with value val, updating branching
// requires list to be in ascending order because of use of GetSmallestGreaterEltByVal to get to element
HEADER* DeleteElementByVal(HEADER* head, int valtodel);

// Delete all elements with value in range
HEADER* DeleteElementByValRange(HEADER* head, int RangeStart, int RangeEnd);

// Prints out info on list head
void PrintListInfo(HEADER* head);

#endif /* DOUBLELINKEDLISTFUNCTIONS_H */