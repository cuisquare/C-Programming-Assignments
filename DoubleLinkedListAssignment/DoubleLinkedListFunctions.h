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

// outputs new list that is reverse of input list
HEADER* ReverseList(HEADER* head);

// Inserts an Element in correct order based on list order and value to insert its value, updating branching
HEADER* InsertElementInOrder(HEADER* head, int valtoins);

// Deletes an Element in correct order based on list order and value to delete, updating branching
HEADER* DeleteElementInOrder(HEADER* head, int valtoins);

// Prints out info on list head
void PrintListInfo(HEADER* head);

#endif /* DOUBLELINKEDLISTFUNCTIONS_H */