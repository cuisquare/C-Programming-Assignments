#ifndef DOUBLELINKEDLISTFUNCTIONS_H
#define DOUBLELINKEDLISTFUNCTIONS_H

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

//Returns element in head that has smallest value greater or equal to val
LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val);

// outputs new list that is reverse of input list
HEADER* ReverseList(HEADER* head);

// Inserts an Element in correct order based on list order and value to insert its value, updating branching
HEADER* InsertElementInOrder(HEADER* head, int valtoins);

// Inserts an Element in forward order based on its value, updating branching
// Assumes list is in ascending order
void InsertElementForwardByVal(HEADER* head, int valtoins);

//Deletes One Element with value val, updating branching
//assumes list is in ascending order
void DeleteElementByVal(HEADER* head, int valtodel);

// Deletes an Element in correct order based on list order and value to delete, updating branching
HEADER* DeleteElementInOrder(HEADER* head, int valtoins);

#endif /* DOUBLELINKEDLISTFUNCTIONS_H */