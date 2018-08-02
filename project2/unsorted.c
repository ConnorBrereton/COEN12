/*
 
 Course      :   COEN 12 (Data Structures & Algorithms)
 Project     :   #2
 Filename    :   unsorted.c
 Date        :   01/22/18
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "set.h"


typedef struct set // Struct for the program
{
    int count; // size of the filled array
    int max_elts; // size of the array
    char **elts; // points to the character array(s)
}SET;


/*
 Big O: O(1)
 Function Description: // Create an unsorted set
*/
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET)); // pointer to set make memory
    
    assert(sp != NULL); // check that the SET isn't empty
    
    sp->count = 0; // init count member
    
    sp->max_elts = maxElts; // init max_elts member to length of the array
    
    sp->elts = malloc(sizeof(char*)*maxElts); // create memory for the elements
    
    assert(sp->elts != NULL); // check that it's a non-empty
    
    return sp;
}


/*
 Big O: O(n)
 Function Description: Destroy a set (reverse order)
*/
void destroySet(SET *sp)
{
    int i;
    assert(sp != NULL);
    
    for(i=0; i < sp->count; i++)
        free(sp->elts[i]); // free each element in the array
    
    free(sp->elts); // free the pointer to the array
    
    free(sp); // free the pointer itself
}


/*
 Big O: O(1)
 Function Description: Return the number of elements in the set
*/
int numElements(SET *sp)
{
    return sp->count;
}


/*
 Big O: O(n)
 Function Description: Return index of the element
*/
char *findElement(SET *sp, char *elt)
{
    int i;

    for(i=0; i < sp->count; i++)
    {
        if(strcmp(sp->elts, elt) == 0)
            return i;
    }
    return NULL;
}



/*
 Big O: O(n)
 Function Description: Get the number of elements in the set
*/
char **getElements(SET *sp)
{
    int i;

    assert(sp != NULL);

    for(i = 0; i < sp->count; i++)
        return sp->elts[i];
}


/*
 Big O: O(n)
 Function Description: Add an element to the set
*/
void addElement(SET *sp, char *elt)
{
    if(sp->count < sp->max_elts) // ensure not at the end of the array
    {
        if(findElement(sp, elt) == NULL)
        {
            sp->elts[sp->count] = strdup(elt); // malloc and then copy string to end of the list
            sp->count++; // increment count to make sure that strings apppend to end
        }
    }
}


/*
 Big O: O(n)
 Function Description: Remove element from the set
*/
void removeElement(SET *sp, char *elt)
{
    int i;

    int index = findElement(sp, elt);
    
    if(index >= 0) // get the index and ensure that its a valid position
    {
        free(sp->elts[index]); // free the indexs memory
        sp->elts[index] = sp->elts[--sp->count]; // move element to end and decrease count
    }
}
