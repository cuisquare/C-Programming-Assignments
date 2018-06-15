#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DoubleLinkedListFunctions.h"
#include "ParameterConstants.h"
#include "Types.h"

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