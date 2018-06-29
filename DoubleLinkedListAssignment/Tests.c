#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Types.h"

#include "DoubleLinkedListFunctions.h"



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
	    InsertElement(head, i);
	}
    int NbMoves = 5;
    LISTITEM* pos = head->smallest;
    pos = pos->fwd;
    printf("Before Move, pos val = %d\n", pos->val);
    MovePosFwdBy(head, &pos, NbMoves);
    printf("After %d Move, pos val = %d\n", NbMoves, pos->val);

    printf("Press Enter to Continue...");
    getchar();
}

//Testing ReverseDirection function
void TestReverse() {
	HEADER* head = CreateEmptyList();
    for(int i = 10; i < 20; i++)
	{
	    InsertElement(head, i);
	}
	printf("Before Reversing, head: : \n");
	PrintListVerbose(head);
	HEADER* head2 = head;
	ReverseDirection(head2);
	printf("After Reversing, head2 : \n");
	PrintListVerbose(head2);
	printf("After Reversing, head : \n");
	PrintListVerbose(head);

	//Inserting new value in head2
	printf("INSERTING 5 in head...\n");
	InsertElement(head, 5);
	printf("INSERTING 3 in head...\n");
	InsertElement(head, 3);
	printf("After Inserting new values 5 then 3, head : \n");
	PrintListVerbose(head);
	printf("INSERTING 25 in head2...\n");
	InsertElement(head2, 25);
	printf("INSERTING 23 in head2...\n");
	InsertElement(head2, 23);
	printf("After Inserting new values 25 then 23, head2 : \n");
	PrintListVerbose(head2);
}