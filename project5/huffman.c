/*
 Course: COEN 12 (Data Structures & Algorithms)
 Project: Project 5
 Filename: huffman.c
 Date: 03/07/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE;

// O(n)
int hopNumber(struct node *leaf)
{
    int hops = 0;
    while (leaf -> parent != NULL)
    {
        leaf = leaf -> parent;
        hops++;
    }
    return hops;
}

// O(1)
int compare(struct node *first, struct node *second)
{
    return (first -> count < second -> count) ? -1 : (first -> count > second -> count);
}

int main(int argc, char *argv[])
{
    int i;
    FILE *fp = fopen(argv[1],"r");   // Opens the file passed as arg in CLI
    int occurences[257] = {0};      // Createa an array of size 257. All values hold "0"
    
    if (fp == NULL)
    {
        return 0;
    }
    
    do      // Run a do-while loop to always grab the next character
    {
        int c;
        c = fgetc(fp);
        
        if( feof(fp) )                    // EOF t.f. break
        {
            break;
        }
        occurences[c]++;        // Add an occurance to the array
    }
    while(1);                 // Continouosly loop
    
    
    PQ *pqueue = createQueue(compare);
    
    struct node* leaves[257] = {0};            // Create leaves array thats init to all "0"
    
    for (i = 0; i < 257; i++)
    {
        leaves[i] = NULL;       // Init values to NULL
    }
    
    
    for (i = 0; i < 256; i++)       // Create a new node, add to the pqriority queue, add to the leaves array
    {
        if (occurences[i] > 0)
        {
            NODE *thenode = malloc(sizeof(struct node));
            thenode -> count = occurences[i];
            thenode -> parent = NULL;
            addEntry(pqueue,thenode);
            leaves[i] = thenode;
        }
    }
    
    // Create a tree with a zero EOF
    NODE *zeroCountNode = malloc(sizeof(struct node));
    zeroCountNode -> count = 0;
    zeroCountNode -> parent = NULL;
    addEntry(pqueue,zeroCountNode);
    leaves[256] = zeroCountNode;
    

    while (numEntries(pqueue) > 1)
    {
        NODE *first = removeEntry(pqueue);                // First lowest priority trees
        NODE *second = removeEntry(pqueue);               // Second lowest priority trees
        NODE *third = malloc(sizeof(struct node));        // This new node's count is the two childrens count
        
        third -> count = first -> count + second -> count;      // Third is the parent node to the first and second node. Sum them up
        third -> parent = NULL;     // Null because it is the parent node
        first -> parent = third;    // Child node no. 1
        second -> parent = third;   // Child node no. 2
        addEntry(pqueue, third);    // Next put into pqueue
    }
    
    
    for (i = 0; i < 257; i++)
    {
        int numberOfHops;
        
        if (leaves[i] != NULL)      // Check for a valid node
        {
            numberOfHops = hopNumber(leaves[i]);
            
            if (isprint(i))                                // Printable?
                printf("\n Occurances %c: Num. Hops %d * %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
            
            else
                printf("%03o: %d * %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
        }
    }
    pack(argv[1],argv[2],leaves);
}
