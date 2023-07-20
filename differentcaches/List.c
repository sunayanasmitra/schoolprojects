
// Include statements
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

// structs --------------------------------------------------------------------
typedef struct NodeObj *Node;

typedef struct NodeObj {
    Node previous;
    char *data;
    int bit;
    Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes data fields.
Node newNode(char *data) {
    Node N = malloc(sizeof(NodeObj));
    N->previous = NULL;
    N->data = data;
    N->bit = 0;
    N->next = NULL;
    return (N);
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        Node N = *pN;
        if (N->data != NULL) {
            free(N->data);
            N->data = NULL;
        }
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->cursor = NULL;
    L->back = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL) {
    if (pL != NULL && *pL != NULL) {
        List L = *pL;
        while (L->length != 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int indx(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        L->index = -1;
        return (L->index);
    }
    if (L->cursor == NULL) {
        L->index = -1;
        return (L->index);
    } else {
        return (L->index);
    }
}

int getBit(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling getBit() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        fprintf(stderr, "List Error: calling getBit() when cursor is undefined\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->bit;
}

// Returns front element data of L. Pre: length()>0
char *front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->front->data);
}

// Returns back element data of L. Pre: length()>0
char *back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->back->data);
}

// Returns cursor element data of L. Pre: length()>0, index()>=0
char *get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "Index Error: calling get() on a negative index\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor->data);
}

// Returns true iff Lists A and B are in samestate, and returns false otherwise.
/*
bool equals(List A, List B){
	if ( A->length != B->length ){
		return false;
	}
	
	Node aNode = A->front;
	Node bNode = B->front;
	
	while( aNode != NULL ){
		if( aNode->data != bNode->data ){
			return false;
		}
		aNode = aNode->next;
		bNode = bNode->next;
	}
	
	return true;
}
*/
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while (L->length > 0) {
        deleteFront(L);
    }
    L->index = -1;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
}

void setBit(List L, int i) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling setBit() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling setBit() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "Index Error: calling setBit() on a negative index\n");
        exit(EXIT_FAILURE);
    }

    Node cursor = L->cursor;
    if (cursor != NULL) {
        cursor->bit = i;
    }
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0 otherwise does nothing.
void set(List L, char *x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "Index Error: calling set() on a negative index\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling moveFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
    L->index = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling moveFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
    L->index = L->length - 1;
}

// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling movePrev() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->previous;
            L->index = L->index - 1;
        }
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling moveNext,() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL) {
        if (L->cursor == L->back) {
            if (L->cursor != L->front) {
                L->cursor = NULL;
                L->index = -1;
            } else {
                L->cursor = L->cursor->next;
            }
            L->index = L->index + 1;
        } else {
            L->cursor = L->cursor->next;
            L->index = L->index + 1;
        }
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, char *x) {
    Node N = newNode(x);

    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 0) {
        L->front = L->back = N;
        N->previous = N->next = NULL;
    } else if (L->length > 0) {
        L->front->previous = N;
        N->next = L->front;
        N->previous = NULL;
        L->front = N;
        if (L->cursor != NULL) {
            L->index = L->index + 1;
        }
    }
    L->length = L->length + 1;
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, char *x) {
    Node N = newNode(x);

    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 0) {
        L->back = L->front = N;
        N->next = N->previous = NULL;
    } else if (L->length > 0) {
        L->back->next = N;
        N->previous = L->back;
        N->next = NULL;
        L->back = N;
    }
    L->length = L->length + 1;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, char *x) {
    Node N = newNode(x);

    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index == -1) {
        fprintf(stderr, "Index Error: calling insertBefore() on a list with no cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL) {
        N->previous = L->cursor->previous;
        N->next = L->cursor;
        L->cursor->previous = N;
        if (L->cursor == L->front) {
            L->front = N;
        } else if (N->previous != NULL) {
            N->previous->next = N;
        }
        L->length = L->length + 1;
        L->index = L->index + 1;
    }
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, char *x) {
    Node N = newNode(x);

    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index == -1) {
        fprintf(stderr, "Index Error: calling insertAfter() on a list with no cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->back) {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    } else {
        N->next = L->cursor->next;
        L->cursor->next->previous = N;
        L->cursor->next = N;
        N->previous = L->cursor;
    }
    L->length = L->length + 1;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    Node N = NULL;

    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    N = L->front;

    if (L->cursor != NULL) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->index = L->index - 1;
        }
    }

    if (length(L) > 1) {
        L->front = L->front->next;
        L->front->previous = NULL;
    } else {
        L->front = L->back = NULL;
    }
    L->length = L->length - 1;

    freeNode(&N);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    Node N = NULL;

    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    N = L->back;

    if (L->cursor != NULL) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        }
    }

    if (length(L) > 1) {
        L->back = L->back->previous;
        L->back->next = NULL;
    } else {
        L->back = L->front = NULL;
    }
    L->length = L->length - 1;

    freeNode(&N);
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete (List L) {
    Node N = NULL;
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index == -1) {
        fprintf(stderr, "Index Error: calling delete() on a negative index\n");
        exit(EXIT_FAILURE);
    }
    N = L->cursor;
    L->index = -1;
    if (length(L) > 1) {
        if (L->cursor == L->front) {
            L->front = N->next;
        } else if (L->cursor == L->back) {
            L->back = N->previous;
        } else {
            N->previous->next = N->next;
            N->next->previous = N->previous;
        }
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->front = L->back = NULL;
    }
    L->length = L->length - 1;
    freeNode(&N);
}

// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L) {
    Node N = NULL;
    if (out == NULL) {
        fprintf(stderr, "File Error: calling printList() on NULL File reference\n");
        exit(EXIT_FAILURE);
    }
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        printf("List Error: calling printList() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    N = L->front;
    while (N != NULL) {
        fprintf(out, "%s ", N->data); // change
        N = N->next;
    }
}

// Returns 1 if the element exists in the list, 0 otherwise.
int ExistsInList(List L, char *x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling ExistsInList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node current = L->front;
    while (current != NULL) {
        if (strcmp(current->data, x) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
/*
List copyList(List L){
	List M = newList();
	Node N = L->front;
	while( N != NULL ){
		append(M,N->data);
		N = N->next;
	}
	return M;
}
*/
// Returns a new List which is the concatenation of A and B. The cursor in the new List is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged.
/*
List concatList(List A, List B){
	List C = copyList(A);
	Node N = B->front;
	while( N != NULL ){
		append(C,N->data);
		N = N->next;
	}
	return C;
}*/
