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

// Creates an Empty List
HEADER* ClearList();

// Creates new LISTITEM elt containing value val
LISTITEM* CreateEltFromVal(int val);

//Returns element in head that has smallest value greater or equal to val
LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val);

//Inserts an Element in forward order based on its value, updating branching
void InsertElementForwardByVal(HEADER* head, int valtoins);

//Deletes One Element with value val, updating branching
void DeleteElementByVal(HEADER* head, int valtodel);

#endif /* DOUBLELINKEDLISTFUNCTIONS_H */