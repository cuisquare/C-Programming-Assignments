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

//Testing ReverseList function
void TestReverse() {
	HEADER* head = CreateEmptyList();
    for(int i = 10; i < 20; i++)
	{
	    InsertElementForwardByVal(head, i);
	}
	printf("Before Reversing, head: : \n");
	PrintListVerbose(head);
	HEADER* head2 = ReverseList(head);
	printf("After Reversing, head2 : \n");
	PrintListVerbose(head2);
	printf("After Reversing, head : \n");
	PrintListVerbose(head);

	//Inserting new value in head2
	printf("INSERTING 5 in head...\n");
	head = InsertElementInOrder(head, 5);
	printf("INSERTING 3 in head...\n");
	head = InsertElementInOrder(head, 3);
	printf("After Inserting new values 5 then 3, head : \n");
	PrintListVerbose(head);
	printf("INSERTING 25 in head2...\n");
	head2 = InsertElementInOrder(head2, 25);
	printf("INSERTING 23 in head2...\n");
	head2 = InsertElementInOrder(head2, 23);
	printf("After Inserting new values 25 then 23, head2 : \n");
	PrintListVerbose(head2);
}