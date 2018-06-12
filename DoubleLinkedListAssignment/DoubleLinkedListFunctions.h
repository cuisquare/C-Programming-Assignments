#ifndef DOUBLELINKEDLISTFUNCTIONS_H
#define DOUBLELINKEDLISTFUNCTIONS_H

//Checks whether a list is empty
bool IsEmptyList(HEADER* head);

//Prints all values of linked list with header head
void PrintList(HEADER* head);

//Creates an Empty List
HEADER* CreateEmptyList();

//Returns element in head that has smallest value greater or equal to val
LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val);

//Inserts an Element in forward order based on its value, updating branching
HEADER* InsertElementForwardByVal(HEADER* head, int valtoins);

//Deletes One Element with value val, updating branching
HEADER* DeleteElementByVal(HEADER* head, int valtodel);

#endif /* DOUBLELINKEDLISTFUNCTIONS_H */