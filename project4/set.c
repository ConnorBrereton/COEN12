/*
 
 Author: Connor Brereton
 Project 4: Amazing Sort Assignment - Implement hashing with chaining
 Date: 2/27/18
 Filename: set.c
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


struct node     // nodes in the linked list
{
    int key;
    int value;
    struct node *next;
}NODE;


struct arrayitem       // linked list pointers
{
    struct node *head;
    struct node *tail;
};


struct arrayitem *array;        // data in the nodes
int size = 0;
int max = 10;


int hashcode(int key)       // create an index of keys
{
    return (key % max);
}


// Prototypes
struct node* getElement(struct node *list, int findIndex);
void removeElement(int key);
void rehash();
void init_array();


// Inserting node function
void insert(int key, int value)
{
    float n = 0.0;                                               // Load factor
    int index = hashcode(key);                                   // Index we are working with
    struct node *list = (struct node*) array[index].head;        // Get the list at an index
    
    // Node and pointers for the SLL
    struct node *item = (struct node*) malloc(sizeof(struct NODE));
    item->key = key;
    item->value = value;
    item->next = NULL;
    
    // Case: empty list
    if (list == NULL)
    {
        printf("\nInserted key: %d  and value: %d\n", key, value);
        array[index].head = item;
        array[index].tail = item;
        size++;
    }
    
    else
    {
        int find_index = find(list, key);
        
        // Case: key wasnt found
        if (find_index == -1)
        {
            array[index].tail->next = item;
            array[index].tail = item;
            size++;
        }
        
        else
        {
            // Case: key found
            struct node *element = getElement(list, find_index);
            element->value = value;
        }
    }
    
    // Compute the load factor. If it exceeds we need to rehash the values
    n = (1.0 * size) / max;
    if (n >= 0.75)
    {
        printf("\nrehashing...\n");
        rehash();
    }
}


void rehash()
{
    // Set temp to current
    struct arrayitem *temp = array;
    
    int i = 0, n = max;
    size = 0;
    max = 2 * max;
    
    // Double the size of the current array for rehashing
    array = (struct arrayitem*) malloc(max * sizeof(struct node));
    init_array();
    
    for (i = 0; i < n; i++)
    {
        // List is the front of the hash table
        struct node* list = (struct node*) temp[i].head;
        
        // Case: empty list
        if (list == NULL)
            continue;
        
        else
        {
            while (list != NULL) // Insert and iterate
            {
                insert(list->key, list->value);
                list = list->next;
            }
        }
    }
    temp = NULL;    // Set temp null here so that it if it fails other criteria it is set NULL
}


// Search for the key in the hash table
int find(struct node *list, int key)
{
    int val = 0;
    struct node *temp = list;
    
    while (temp != NULL)
    {
        if (temp->key == key)       // Found match
            return val;
        
        temp = temp->next;
        val++;
    }
    return -1;
}


// Return node at given index
struct node* getElement(struct node *list, int findIndex)
{
    int i = 0;
    struct node *temp = list; // set to the head of the list
    
    while (i != findIndex)
    {
        temp = temp->next; // Iterate
        i++;               // Increase the count
    }
    return temp;
}


// Removes elements from hash table
void removeElement(int key)
{
    int index = hashcode(key); // set index to our hash key
    int findIndex = find(list, key);
    
    struct node *list = (struct node*) array[index].head;
    
    if (list == NULL || find_index == -1)
        printf("\n Key DNE\n");
    
    else
    {
        struct node *temp = list;
        if (temp->key == key)
        {
            array[index].head = temp->next;
            return;
        }
            
        while (temp->next->key != key) // traverse until a match is found
            temp = temp->next;
            
        if(array[index].tail == temp->next) // hit end of the list
        {
            temp->next = NULL;
            array[index].tail = temp;
        }
        
        else
        {
            temp->next = temp->next->next;
            printf("This key has been removed\n");
        }
    }
}

// List all of elements of the hash table
void Show()
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        struct node *temp = array[i].head; // temp begins at the node and traverses
        
        // Case: empty index
        if (temp == NULL)
            printf("\nindex:[%d] is empty\n", i);
        
        else
        {
            printf("\nindex:[%d] has elements-: ", i);
            while (temp != NULL) // loop thru and print it all out
            {
                printf("\nkey: %d  value: %d\t", temp->key, temp->value);
                temp = temp->next;
            }
        }
    }
}


// Initialize the array to empty to start
void init_array()
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        array[i].head = NULL;
        array[i].tail = NULL;
    }
    
}

// Tells the size of the array
int size_of_array()
{
    return size;
}
