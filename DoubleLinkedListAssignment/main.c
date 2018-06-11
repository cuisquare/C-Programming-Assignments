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

int ErrorInt = 99;

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
		int NMax = 100; // avoiding infinite loop
		while (i < NMax) {
			printf("Val number %d = %d\n", i+1, temp->val);
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
	//printf("Attemping to insert elt with value %d...\n", valtoins);
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
	//printf("Updated List: \n");
	//PrintList(head);
	return head;
}

//Deletes One Element with value val, updating branching
HEADER* DeleteElementByVal(HEADER* head, int valtodel) {
	//printf("Attemping to delete elt with value %d...\n", valtodel);
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
	//printf("Updated List: \n");
	//PrintList(head);
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
	printf("	1 : Insert Value In List\n");
	printf("	2 : Delete Value From List\n");
	printf("	3 : Print List\n");
	printf("	4 : Clear List\n");
	printf("	5 : Input Multiple values in List\n");
	printf("	6 : Delete Multiple values in List\n");
	printf("	7 : Input Range in List\n");
	printf("	8 : Delete Range in List\n");
	printf("	0 : Exit Program\n");
}

// gets input from keyboard and convert to integer
int getIntValue() {
	char charinput[10];
	scanf_s("%9s", &charinput, 9);
	int choice = atoi(charinput);
	/*printf("Your choice was : %d!\n", choice);
	PressEnterToContinue();*/
	return choice;
}

int getMenuChoice() {
	printf("Menu choice : ");
	int output = getIntValue();
	printf("\n");
	if ((output<0)||(output>8)) {
		output = ErrorInt;
	}
	return output;
}

//flushes buffer and wait for getchar to resume
void PressEnterToContinue() {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
	printf("Press ENTER to continue.\n");
	getchar();
}

//Carry out choice from user input
HEADER* carryOutChoice(HEADER* head, int choice) {
	switch (choice) {
		case 0:
			printf("Exiting Program.\n");
			PressEnterToContinue();
			break;
		case 1:
			printf("Input Single Value to Insert:  ");
			head = InsertElementForwardByVal(head, getIntValue());
			printf("Value Inserted.\n");
			PressEnterToContinue();
			break;
		case 2:
			printf("Input Single Value to Delete:  ");
			head = DeleteElementByVal(head, getIntValue());
			printf("Value Deleted.\n");
			PressEnterToContinue();
			break;
		case 3:
			PrintList(head); 
			printf("List Printed.\n");
			PressEnterToContinue();
			break;
		case 4:
			head = CreateEmptyList();
			printf("List Cleared.\n");
			PressEnterToContinue();
			break;
		case 5:
			printf("Input Number of Values to Insert:  ");
			int NbValToInsert = getIntValue();
			for (int i=0; i<NbValToInsert ;i++) {
				printf("Input Value %d / %d: ", i+1 , NbValToInsert);
				head = InsertElementForwardByVal(head, getIntValue());
			} 
			printf("Input of values to insert over.\n");
			PressEnterToContinue();
			break;
		case 6:
			printf("Input Number of Values to Delete:  ");
			int NbValToDelete = getIntValue();
			for (int i = 0; i<NbValToDelete; i++) {
				printf("Value To Be Deleted %d / %d: ", i + 1, NbValToDelete);
				head = DeleteElementByVal(head, getIntValue());
			}
			printf("Input of values to be deleted over.\n");
			PressEnterToContinue();
			break;
		case 7:
			printf("Input Start of Range - inclusive - to Insert:  ");
			int RangeStartForIns = getIntValue();
			printf("\n");
			printf("Input End of Range - exclusive - to Insert:  ");
			int RangeEndForIns = getIntValue();
			for (int i = RangeStartForIns; i<RangeEndForIns; i++) {
				head = InsertElementForwardByVal(head, i);
			}
			printf("Range to be Inserted Defined.\n");
			PressEnterToContinue();
			break;
		case 8:
			printf("Input Start of Range - inclusive - to Delete:  ");
			int RangeStartForDel = getIntValue();
			printf("\n");
			printf("Input End of Range - exclusive - to Delete:  ");
			int RangeEndForDel = getIntValue();
			for (int i = RangeStartForDel; i<RangeEndForDel; i++) {
				head = DeleteElementByVal(head, i);
			}
			printf("Range to be Deleted Defined.\n");
			PressEnterToContinue();
			break;
	}
	return head;
}


/////////////////
//END FUNCTIONS//
/////////////////



int main() {

	HEADER* head = CreateEmptyList();

	int choice;
	do {
		PrintMenu();
		choice = getMenuChoice();
		if (choice != ErrorInt) {
			head = carryOutChoice(head, choice);
		}
		else {
			printf("Incorrect Input. Only allowed inputs are integers 0-8.\n");
			PressEnterToContinue();
		}
	} while (choice != 0);

	return 0;
}