/*
 
 Course      :   COEN 12 (Data Structures & Algorithms)
 Project     :   #3
 Filename    :   table_generic.c
 Date        :   02/12/18
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "set.h"

#define FLAG_EMPTY 0
#define FLAG_FULL 1
#define FLAG_TOMB -1

typedef struct set // Struct for the program
{
    int count; // size of the filled array
    int max_elts; // size of the array
    char **elts; // points to the character array(s)
    int *flags;
}SET;


/*
 Big O: O(1)
 Function Description: // Create an unsorted set
 */
SET *createSet(int maxElts, int (*compare), unsigned (*hash))
{
    int i;
    
    SET *sp = malloc(sizeof(SET)); // pointer to set make memory
    
    assert(sp != NULL); // check that the SET isn't empty
    
    sp->count = 0; // init count member
    
    sp->max_elts = maxElts; // init max_elts member to length of the array
    
    sp->elts = malloc(sizeof(char*)*maxElts); // create memory for the elements
    
    assert(sp->elts != NULL); // check that it's a non-empty
    
    sp->flags = malloc(sizeof(int)*maxElts); // create memory for the flag
    
    assert(sp->flags != NULL); // check that it's a non-empty
    
    for(i = 0; i < maxElts; i++) // set each flag slot to empty
    {
        sp->flags[i] = FLAG_EMPTY;
    }
    
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
    
    for(i=0; i < sp->max_elts; i++)
    {
        if(sp->flags[i] != FLAG_EMPTY)
            free(sp->elts[i]); // free each element in the array
    }
    
    free(sp->elts); // free the elts array
    free(sp->flags); // free the flag array
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
 Function Description: Return hash index for the string
 */
unsigned strhash(char *s)
{
    unsigned hash = 0;
    
    while(*s != '\0')
        hash = 31 * hash + *s ++; // arithmetic method used to compute the hash
    
    return hash;
}


/*
 Big O: O(n)
 Function Description: Return index of the element
 */
void findElement(SET *sp, char *elt)
{
    int i;
    
    assert(elt != NULL);
    if(elt == NULL)
        return false;
    
    unsigned home = strhash(elt) % sp->max_elts;
    int hash = home;
    int available = -1;
    int flag = sp->flags[hash]; // get hash value
    
    while(hash != home)
    {
        if(flag == FLAG_EMPTY) // hit an empty slot
        {
            if(available != -1)
                return available;
            return hash;
        }
        
        if(flag == FLAG_TOMB) // hit a deleted spot
        {
            if(available == -1)
                available = hash;
        }
        
        if(flag == FLAG_FULL) // hit a match
        {
            if(*sp->compare) == 0) // NOTE: doesnt work
                return hash;
        }
        
        hash = (hash + 1) % sp->max_elts; // linear probing
    }
    
    if(available == -1) // element wasnt found
        available = hash;
    return available;
    
}


/*
 Big O: O(n)
 Function Description: Get the number of elements in the set
 */
void getElements(SET *sp)
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
    int index = findElement(sp, elt); // sets the insertion index
    
    if(sp->count < sp->max_elts) // ensure not at the end of the array
    {
        if(findElement(sp, elt) == NULL)
        {
            sp->elts[index] = strdup(elt); // insert the string at index
            sp->flags[index] = FLAG_FULL; // flag for a match
            sp->count++; // change the count of elements in hash set
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
        sp->flags[index] = FLAG_TOMB;
        sp->count--;
        
        //free(sp->elts[index]); // free the indexs memory
        //sp->elts[index] = sp->elts[--sp->count]; // move element to end and decrease count
    }
}
