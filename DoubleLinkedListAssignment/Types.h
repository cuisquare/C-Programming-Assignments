#ifndef TYPES_H
#define TYPES_H

//enum defining direction that list goes when accessing next element
// asc means first element is smallest, last is greatest, next is ascending
// desc means first element is greatest, last is smallest and next is descending
// in memory the list will however be stored in ascending order going fwd and this will remain unchanged
// only used effectively in print functions
typedef enum 
{
	fwd, 
	bck
} Direction;

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
	struct listitem *smallest;
	struct listitem *greatest;
	Direction direction;
} HEADER;

#endif /* TYPES_H */
