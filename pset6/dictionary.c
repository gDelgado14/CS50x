/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define h_sz 50000
#define myDict "/home/jharvard/Dropbox/pset6/pdict.txt"

//prototypes
int hash(char *str); // delipity hash (source: reddit, user: delipity)
void insert_node(int ind, char *insert);


// node definition
typedef struct node
{
    // size of biggest possible word + 1 for null terminator
    char word[LENGTH+1];
    struct node *next;
}
node;


/** global hash table declaration
 *  global means that array buckets all null initially
 **/
node *h_table[h_sz];

//global var to keep track of words in dictionary
int dSize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    char checker[LENGTH+1];
    strcpy(checker, word);
    
    for(int i = 0; checker[i]; i++)
    {
        checker[i] = tolower(checker[i]);
    }
    
    int index = hash(checker);
    
    //create current and previous pointers
    node *curr = h_table[index];
    node *prev = NULL;

    // go through list
    while (curr != NULL)
    {
        // found!
        if (strcmp(checker,curr->word) == 0)     
        {
            return true;
        }
        
        // if value > this node
        else if (strcmp(checker,curr->word) > 0)
        {
            
            //go to next node
            prev = curr;
            curr = curr->next;  
            
            if (curr == NULL)
            {
                break;
            }
        }
        
        // if value < this node
        else if (strcmp(checker,curr->word) < 0)
        {
            break;
        }
        
    }
    
    return false;  
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    
    int index;
    
    char temp[LENGTH+1];
    
    // for each word in dict
    while (fscanf(dict,"%s", temp) == 1)
    { 
        index = hash(temp);

        //insert word into hash table
        insert_node(index, temp);
        
        dSize++;
    }


    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return dSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int bucket = 0; bucket < h_sz; bucket++)
    {
        //dont' lose the rest of the list
        node *curr = h_table[bucket];
        node *prev = NULL;
        
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    
    } 
    
    return true;
}

int hash(char *str)
{
    // source: user delipity
    //         http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/ 
    

    unsigned int hashNum = 0;
    
    for (int i=0, n=strlen(str); i<n; i++)
        hashNum = (hashNum << 2) ^ str[i];
        
    return hashNum % h_sz;

}

void insert_node(int ind, char *insert)
{
    // create a new node
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
      return;  
    }   

    strcpy(new_node->word, insert);
    
    //first insertion
    if (h_table[ind] == NULL)
    {
        new_node->next = h_table[ind];
        h_table[ind] = new_node;
        return;
    }
    
    //create current and previous pointers
    node *curr = h_table[ind];
    node *prev = NULL; 
 
    
    // go through list
    while (curr != NULL)
    {
        
        // don't insert duplicates
        if (strcmp(insert,curr->word) == 0)
        {
            free(new_node);
            return;
        }
        
        // if value > this node
        else if (strcmp(insert,curr->word) > 0)
        {
            
            //go to next node
            prev = curr;
            curr = curr->next;  
            
            if (curr == NULL)
            {
                break;
            }
        }
        
        // if value < this node
        else if (strcmp(insert,curr->word) < 0)
        {
            break;
        }
        
    }   
    
    // must be at end of list
    new_node->next = curr;
    
    if (prev == NULL)
    {
        h_table[ind] = new_node;
    }
    else
    {
        prev->next = new_node;
    }
 
    
    return;
}
