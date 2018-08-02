/*
    Author: Connor Brereton
    Project 4: Amazing Sort Assignment
    Date: 2/27/18
    Filename: list.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node
{
    int data;           // the info in each node
    struct list* next;  // the next node
    struct list* prev;  // the prev node
} NODE;

struct list             // use for insertion and deletion at front/back cases
{
    int count;          // tracks the no. items in each queue
    NODE* head;         // head of deque. used for operations
} LIST;


// O(1); Return a pointer to a new node
NODE* createNode(void *item)
{
    LIST* nde = malloc(sizeof(LIST));
    assert(nde != NULL);
    nde->data = item;
    nde->next = NULL;
    nde->prev = NULL;
    return node;
}


// O(1); Return a pointer to a new deque
LIST* createList()
{
    LIST* lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = createNode(0);
    lp->head->next = lp->head;  // allign the head location
    lp->head->prev = lp->head;  // allign the tail location
    return lp;
}


// O(1); Deallocate memory allocated to the list
void destroyNode(NODE *nde)
{
    assert(nde != NULL);
    free(nde);
}


// O(1); Return the number of items in the deque pointed to by "lp"
int numItems(LIST *lp)
{
    return lp->count;
}


// O(n); Deallocate memory associated with the deque pointed to by "lp"
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    LIST* n = lp->head->next;   // "n" is set to the head node
    
    while(n != lp->head)        //  use "n" to check if queue is empty
    {
        n = n->next;            //  "n" is set to the next node
        destroyNode(n->prev);   //  "n" is set to prev node, then that node is destroyed
    }                           //  "n" is head? exit
    
    destroyNode(n);             //  "n" is destroyed since it is no longer useful
    free(lp);
}


// O(1); Inserts a new node in between two existing nodes
void insertNode(NODE* first, NODE* second, void *item)
{
    LIST* new = createNode(item);  // "new" points to the node created when "createList" is executed
    first->next = new;          // "new" node is placed after the "first"
    new->next = second;         // after "new" is "second" node
    new->prev = first;          // before "new" is "first" node
    second->prev = new;         // before "second" is the "new" node
}


// O(n); Remove & destroy a node from deque, returns the data in the node
void removeItem(NODE* remove, void *item)
{
    // comparison function
    
    item = remove->data;                // "data" is set to the data in the node to be deleted
    remove->prev->next = remove->next;  // we set the node behind us to the node in front to avoid segfault
    remove->next->prev = remove->prev;  // and vice versa
    destroyNode(remove);
    return item;
}


// O(1); Add "item" to first in deque. "item" is pointed to by "lp"
void addFirst(LIST *lp, void *item)
{
    insertNode(lp->head, lp->head->next, item);    // insert a new node between "head" and heads next
    lp->count++;
}


// O(1); Add "item" as last item in the deque. "item" is pointed to by "lp"
void addLast(LIST *lp, void *item)
{
    insertNode(lp->head->prev, lp->head, item);   // insert a new node between head->prev aka "prev" and head
    lp->count++;
}


// O(1); Remove & return the first item in the deque. "item" is pointed to by "lp"
void *removeFirst(LIST *lp)
{
    assert(lp->count > 0);  // check that we dont have an empty deque
    lp->count--;            // decrement the deque count
    
    return removeItem(lp->head->next);
}


// O(1); Remove & return the last item in the deque. "item" is pointed to by "lp"
void *removeLast(LIST *lp)
{
    assert(lp->count > 0);  // check that we dont have an empty deque
    lp->count--;            // decrement the deque count
    
    return removeItem(lp->head->prev);
}


// O(1); Return the first item in the deque. "item" is pointed to by "lp"
void *getFirst(LIST *lp)
{
    assert(numItems(lp) > 0);       // check that we dont have an empty deque
    return lp->head->next->data;    // return the contents of that first node
}


// O(1); Return the last item in the deque. "item" is pointed to by "lp"
void *getLast(LIST *lp)
{
    assert(numItems(lp)>0);
    return lp->head->prev->data;
}


// O(n); If "item" is present, return "item". If not, NULL
void *findItem(LIST *lp, LIST *cmp, void *item)
{
    int i;
    LIST* curr=head;
    
    assert(numItems(lp)>0);
    
    for(i=0; i<lp->count; i++) // Traverse the list index
    {
        curr = head[i];
        cmp = lp->head->next->data;
        
        while(curr != NULL)
        {
            ret = memcmp(curr->data, cmp);
            if(ret == 0)
                return cmp;
            else return NULL;
        }
    }
}


// O(n); Shows all of the data from traversing
void *getItems(LIST *lp)
{
    int i = 0;
    LIST *p=head;
    
    for(i=0; i<lp->count; i++)
    {
        p=head[i];
        
        while(p != NULL)
        {
            printf("\n%d\n", p->next->data);
            p=p->next;
        }
    }
}
