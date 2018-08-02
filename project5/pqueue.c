/*
 Course: COEN 12 (Data Structures & Algorithms)
 Filename: pqueue.c
 Name: Connor Brereton
 Date: 03/07/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"
#define START_LENGTH 10
#define p(x) (((x)-1)/2)    // parent node
#define l(x) (((x)*2)+1)    // left node
#define r(x) (((x)*2)+2)    // right node


// create pqueue struct and its functions: creating/destroying/add/remove queue
struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
};


// O(1)
PQ *createQueue(int (*compare)())
{
    PQ *pq = malloc(sizeof(PQ));  // allocate memory
    assert(pq != NULL);
    
    pq->count = 0;
    pq->length = START_LENGTH; // ten
    pq->data = malloc(sizeof (void*) *START_LENGTH); // ten
    
    pq->compare = compare;
    assert(compare != NULL);
    
    return pq; // returns the function
}


// O(n)
void destroyQueue(PQ *pq)
{
    int i;
    
    for(i = 0; i < pq->count; i++)
    {
        free(pq->data[i]); // delete the data in the index
    }
    free(pq->data); // delete the array
    free(pq); // delete the pointer to the array
}


// O(1)
int numEntries(PQ *pq)
{
    return pq->count; // tells us how many items are in the array
}


// O(log n)
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);
    
    if (pq->count == pq->length)
    {
        pq->data = realloc(pq->data, sizeof(void*)*pq->length *2); // Full array? Double the size but keep current data
        pq->length = pq->length * 2;
    }
    
    pq->data[pq->count] = entry;                                   // Put element at end of array
    int index = pq->count;                                         // Locates position when swapping
    
    while (pq->compare(pq->data[index], pq->data[p(index)])<0)     // Reheapup by continually comparing with parent "p"
    {
        // Swap with parent
        void* temp = pq->data[p(index)];                           // Set "temp" node = parent node
        pq->data[p(index)] = pq->data[index];                      // Move parent node below child node since its bigger
        pq->data[index] = temp;                                    // Store the data in the node in "temp"
        
        index = p(index);                                          // Update the index to be at the current node which is now parent node
    }
    pq->count++;                                                   // Increase count
}


// O(log n)
void *removeEntry(PQ *pq)
{
    void* root = pq->data[0];                                      // "Root" points to the first node
    int index = 0, smallestIndex = 0;                              // "Index" is current index. "smallestIndex" is smallest index.
    pq->data[index] = pq->data[pq->count-1];                       // Swap element with previous element
    
    pq->count--;                                                   // Decrease count
    while (l(index) < pq->count)                                   // Run loop if left child exists
    {
        smallestIndex = l(index);
        if (r(index) < pq->count)                                  // Compare the two children
        {
            if (pq->compare(pq->data[l(index)], pq->data[r(index)]) <0)
            {
                smallestIndex=l(index);     // Smallest is LHS
            }
            else
            {
                smallestIndex=r(index);     // Smallest is RHS
            }
        }
        
        if (pq->compare(pq->data[smallestIndex],pq->data[index])<0) // in either case, which ever children is hypothetically smallest. If it is smaller than the parent, then we swap
        {
            void* temp = pq->data[smallestIndex];
            pq->data[smallestIndex] = pq->data[index];
            pq->data[index] = temp;
            index=smallestIndex;
        }
        else
        {
            break;
        }
    }
    return root;                                                            // return the data stored in the beginning
}
