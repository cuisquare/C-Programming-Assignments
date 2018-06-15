#ifndef TYPES_H
#define TYPES_H

//enum defining direction that list goes when moving forward
// asc means ascending value list going forward
// desc means descending value list going forward
enum Order {asc, desc};

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
	enum Order *order;
} HEADER;

#endif /* TYPES_H */
