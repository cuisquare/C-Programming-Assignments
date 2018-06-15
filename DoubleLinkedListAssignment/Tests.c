#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"

#include "DoubleLinkedListFunctions.h"

void TestProgram()
{
    HEADER* head = CreateEmptyList();
    PrintList(head);
    InsertElementForwardByVal(head, 7);
    InsertElementForwardByVal(head, 13);
    InsertElementForwardByVal(head, 9);
    InsertElementForwardByVal(head, 5);
    InsertElementForwardByVal(head, 28);
    InsertElementForwardByVal(head, 11);
    InsertElementForwardByVal(head, 5);
    InsertElementForwardByVal(head, 9);
    DeleteElementByVal(head, 5);
    DeleteElementByVal(head, 11);
    InsertElementForwardByVal(head, 11);
    DeleteElementByVal(head, 28);
    DeleteElementByVal(head, 45);
    PrintList(head);

    HEADER* head2 = CreateEmptyList();
    PrintList(head2);
    PrintList(head2);
    for(int i = 0; i < 20; i++)
	{
	    InsertElementForwardByVal(head2, i);
	}
    PrintList(head2);

    for(int i = 15; i < 40; i++)
	{
	    InsertElementForwardByVal(head, i);
	}
    PrintList(head);

    printf("Press ENTER to continue.\n");

    getchar();
}

void TestHeadRefTry()
{
    HEADER* head = CreateEmptyList();

    printf("Inserting value 7 without ref...\n");
    InsertElementForwardByVal(head, 7);
    printf("Inserting value 13 without ref...\n");
    InsertElementForwardByVal(head, 13);

    printf("Results:\n");
    PrintList(head);
    printf("Press ENTER to continue.\n");

    getchar();
}

static void MovePosFwdBy(HEADER* head, LISTITEM** pos, int NbMoves)
{
    for(int i = 0; i < NbMoves; i++)
	{
	    *pos = (*pos)->fwd;
	}
}

void TestUpdatePos()
{
    HEADER* head = CreateEmptyList();
    for(int i = 1; i < 21; i++)
	{
	    InsertElementForwardByVal(head, i);
	}
    int NbMoves = 5;
    LISTITEM* pos = head->first;
    pos = pos->fwd;
    printf("Before Move, pos val = %d\n", pos->val);
    MovePosFwdBy(head, &pos, NbMoves);
    printf("After %d Move, pos val = %d\n", NbMoves, pos->val);

    printf("Press Enter to Continue...");
    getchar();
}

// Reverses order of list
static HEADER* ReverseList(HEADER* head) {
	
	bool LastReached = 0;
	bool FirstReached = 0;
	LISTITEM* temp = head->first;
	while (!LastReached) {
		printf("Before the change...\n");
		printf("temp val = %d\n", temp->val);
		printf("temp val next = %d\n", temp->fwd->val);
		printf("temp val prev = %d\n", temp->bck->val);
		LastReached= (temp = head->last);
		temp->bck = temp->fwd;
		if(!LastReached) 
		{
			temp = temp->fwd;
		}
		else 
		{
			temp->bck = NULL;
		}
		printf("After the change...\n");
		printf("temp val = %d\n", temp->val);
		printf("temp val next = %d\n", temp->fwd->val);
		printf("temp val prev = %d\n", temp->bck->val);
	}
	temp = head->last;
	while (!FirstReached) {
		printf("Before the change...\n");
		printf("temp val = %d\n", temp->val);
		printf("temp val next = %d\n", temp->fwd->val);
		printf("temp val prev = %d\n", temp->bck->val);
		FirstReached = (temp = head->first);
		temp->fwd = temp->bck;
		if(!FirstReached) 
		{
			temp = temp->bck;
		}
		else
		{
			temp->fwd = NULL;
		}
		printf("After the change...\n");
		printf("temp val = %d\n", temp->val);
		printf("temp val next = %d\n", temp->fwd->val);
		printf("temp val prev = %d\n", temp->bck->val);
	}
	temp = head->first;
	head->first = head->last;
	head->last = temp;
	head->order = desc;
	return head;
}

static HEADER* ReverseListNEW(HEADER* head) {
	
	HEADER* headoutput = CreateEmptyList();
	headoutput->first = head->last;
	headoutput->last = head->first;
	
	LISTITEM* temp = head->first;
	bool Finished = 0;
	while (!Finished) 
	{
		Finished = (temp == head->last);
		LISTITEM* temp2 = CreateEltFromVal(temp->val);
		temp2->fwd = temp->bck;
		temp2->bck = temp->fwd;
		if (!Finished) 
		{
			temp = temp->fwd;
		}
	}
	 
	
	return headoutput;
}

//Testing ReverseList function
void TestReverse() {
	HEADER* head = CreateEmptyList();
    for(int i = 1; i < 4; i++)
	{
	    InsertElementForwardByVal(head, i);
	}
	printf("Before Reversing : \n");
	PrintListVerbose(head);
	HEADER* head2 = ReverseListNEW(head);
	printf("After Reversing : \n");
	PrintListVerbose(head2);
}