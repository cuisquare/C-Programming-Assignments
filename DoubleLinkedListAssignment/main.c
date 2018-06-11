#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

////////////
//TYPEDEFS//
////////////

//Struct type for a double linked list element. 
//Contains:  
//	integer value - val
//	pointer to next element in list - *fwd
//	pointer to previous element in list - *bck
typedef struct listitem {
	struct listitem *fwd;	
	struct listitem *bck;	 
	int val;					
} LISTITEM;

//Struct type for a header to a linked list of type LISTITEM elements.
//Contains:
//	pointer to first element in list - *first
//	pointer to last element in list - *last
typedef struct header {
	struct listitem *first;
	struct listitem *last;
} HEADER;

////////////////
//END TYPEDEFS//
////////////////

/////////////
//FUNCTIONS//
/////////////

//Checks whether a list is empty
bool IsEmptyList(HEADER* head) {
	return ((head->first == (LISTITEM*)head));
}

//Prints all values of linked list with header head
void PrintList(HEADER* head) {
	printf("***START PRINT*** \n");
	if (!IsEmptyList(head)) {
		LISTITEM* temp = head->first;
		int i = 0;
		int NMax = 50; // avoiding infinite loop
		while (i < NMax) {
			printf("Val number %d = %d\n", i, temp->val);
			if (temp == head->last) {
				break;
			}
			else {
				i++;
				temp = temp->fwd;
			}
		}
	}
	else {
		printf("No elements to print (empty list).\n");
	}
	printf("***END PRINT*** \n");
}

//Creates an Empty List
HEADER* CreateEmptyList() {
	HEADER* head = malloc(sizeof(HEADER));
	head->first = (LISTITEM*)head;
	head->last = head->first;
	return head;
}

//Returns element in head that has smallest value greater or equal to val
LISTITEM* GetSmallestGreaterEltByVal(HEADER* head, int val) {
	LISTITEM* temp;
	if ((IsEmptyList(head)) || head->last->val<val) {
		//If List is empty, or all elements in list are smaller than val (aka there is no elements greater in list), we return pointer to NULL
		//this works only if list is ordered by ascending val going forward through list
		temp = NULL;
	}
	else {
		//the list is not empty and there is an elt in it with value greater or equal than val
		bool posfound = 0;
		bool loopedthrough = 0;
		bool searchfinished = 0;

		temp = head->first;
		//enter loop if search is not finished
		while (!searchfinished)
		{
			posfound = (temp->val >= val); //elt found if its value is greater or equal than value searched
			loopedthrough = (temp == head->last);  // loop through list over if temp is last element in list
			searchfinished = (posfound || loopedthrough); //search finished if elt found or loop through list over
			if (!searchfinished) { // proceed to next elt in list ifsearch is not finished //&& !loopedthrough
				temp = temp->fwd;
			}
		}
	}
	return temp;
}

//Inserts an Element in forward order based on its value, updating branching
HEADER* InsertElementForwardByVal(HEADER* head, int valtoins) {
	LISTITEM* nextelt = GetSmallestGreaterEltByVal(head, valtoins);
	printf("Attemping to insert elt with value %d...\n", valtoins);
	if (nextelt == NULL) {
		//there is no element in list greater than the one to insert. 
		//Therefore : Insert Element at End
		LISTITEM* newelt = malloc(sizeof(LISTITEM));  //CreateEltFromVal(valtoins);
		newelt->val = valtoins;
		newelt->bck = head->last; // newelt points backward to soon-to-be-old last element
		head->last->fwd = newelt; // soon-to-be-old last element points forward to newelt
		head->last = newelt; // newelt is new last element
	}
	else if (nextelt->val == valtoins) {
		//There already is elt with value valtoins in the list
		//Therefore : we do nothing
		printf("Value %d is already in the list and will not be inserted.\n", valtoins);
	}
	else {
		if (nextelt == head->first) {
			//First element in the list is greater than val to insert 
			//Therefore : Insert Element at Start
			LISTITEM* newelt = malloc(sizeof(LISTITEM));  //CreateEltFromVal(valtoins);
			newelt->val = valtoins;
			newelt->fwd = head->first; // newelt points forward to soon-to-be-old first element
			head->first->bck = newelt; // soon-to-be-old first element points back to newelt
			head->first = newelt; // newelt is new first element
		}
		else
		{
			//Smallest greater element is list element neither first nor last
			//Therefore : insert new element before that element, updating branching
			LISTITEM* newelt = malloc(sizeof(LISTITEM));
			newelt->val = valtoins;
			newelt->bck = nextelt->bck; //branch new element back, maintaining link to next element soon-to-be-old prev element 
			newelt->fwd = nextelt; //branch new element forward to next element 
			nextelt->bck->fwd = newelt; //branch next elt old prev element forward to new elt
			nextelt->bck = newelt; //branches next element back to new element 
		}
	}
	printf("Updated List: \n");
	PrintList(head);
	return head;
}

//Deletes One Element with value val, updating branching
HEADER* DeleteElementByVal(HEADER* head, int valtodel) {
	printf("Attemping to delete elt with value %d...\n", valtodel);
	LISTITEM* elttodel = GetSmallestGreaterEltByVal(head, valtodel);
	if ((elttodel == NULL) || (elttodel->val != valtodel))
	{
		printf("There is no element with value %d in the list.\n", valtodel);
	}
	else {
		if (elttodel == head->first) {
			head->first = elttodel->fwd; // branch head first to old 2nd element - elttodel now inaccessible going through list
		}
		else if (elttodel == head->last) {
			head->last = elttodel->bck; //branch head last to old one but last element - elttodel now inaccessible going through list
		}
		else {
			elttodel->bck->fwd = elttodel->fwd; // branch forward around element deleted - elttodel is now inaccessible going forward through list
			elttodel->fwd->bck = elttodel->bck; // branch backward around element to be deleted - elttodel now inacessible going backward through list
		}
		free(elttodel); //free memory previously held by elttodel
	}
	printf("Updated List: \n");
	PrintList(head);
	return head;
}

void TestProgram() {
	HEADER* head = CreateEmptyList();
	PrintList(head);
	head = InsertElementForwardByVal(head, 7);
	head = InsertElementForwardByVal(head, 13);
	head = InsertElementForwardByVal(head, 9);
	head = InsertElementForwardByVal(head, 5);
	head = InsertElementForwardByVal(head, 28);
	head = InsertElementForwardByVal(head, 11);
	head = InsertElementForwardByVal(head, 5);
	head = InsertElementForwardByVal(head, 9);
	head = DeleteElementByVal(head, 5);
	head = DeleteElementByVal(head, 11);
	head = InsertElementForwardByVal(head, 11);
	head = DeleteElementByVal(head, 28);
	head = DeleteElementByVal(head, 45);
	PrintList(head);

	HEADER* head2 = CreateEmptyList();
	PrintList(head2);
	PrintList(head2);
	for (int i = 0; i < 20; i++) {
		head2 = InsertElementForwardByVal(head2, i);
	}
	PrintList(head2);

	for (int i = 15; i < 40; i++) {
		head = InsertElementForwardByVal(head, i);
	}
	PrintList(head);

	printf("Press ENTER to continue.\n");

	getchar();
}

void PrintMenu() {
	system("cls");
	printf("*****Double Linked List Program*****\n");
	printf("Please choose from the following options : \n");
	printf("	1 : Print List\n");
	printf("	2 : Insert Value In List\n");
	printf("	3 : Delete Value From List\n");
	printf("	0 : Exit Program\n");
}

int getMenuChoice() {
	char charinput[20];
	scanf("%1s", &charinput);
	int output = atoi(charinput);
	/*printf("Your choice was : %d!\n", output);
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
	printf("Press ENTER to continue.\n");
	getchar();*/
	return output;
}

/////////////////
//END FUNCTIONS//
/////////////////



int main() {
	int choice;

	do {
		PrintMenu();
		choice = getMenuChoice();
	} while (choice != 0);

	return 0;
}