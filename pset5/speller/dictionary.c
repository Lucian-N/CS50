
//Implements a dictionary's functionality using a trie

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// Maximum size of the alphabet to be used
#define ALPHAS (27)
// Number of elements in an array
#define ARRAYS(a) sizeof(a)/sizeof(a[0)
// Tracks the number of words loaded in the dictionary
unsigned int d_size = 0;

// converts current letter to index number
int c_index(char c) {
  if (c == '\'')
    return 26;
  else if (c >= 'A' && c <= 'Z')
    return c - 65;
  else
    return c - 97;
}

// node declaration
typedef struct node
{
    struct node* children[ALPHAS];
    // Marks the end of a word
    bool isendofword;
}node;

// creates a node and its children :)
node* createnode(void)
{
    node* pnode = NULL;
    pnode = (node*)malloc(sizeof(node));

    if (pnode)
    {
        int i;
        pnode->isendofword = false;
        for (i = 0; i< ALPHAS; i++)
            pnode->children[i] = NULL;
    }
    return pnode;
}

// root declaration
node* root;



//Returns true if word is in dictionary else false.
bool check(const char *word)
{
    // node declaration

    node* head;
    int i;
    int len = strlen(word);
    int index = 0;
    head = root;
    for(i = 0; i < len; i++)
    {
        index = c_index(word[i]);
        if (head->children[index] == NULL)
            return false;

        head = head->children[index];
    }
    return head->isendofword;
}


//Loads dictionary into memory
bool load(const char *dictionary)
{
    // Create space for root
    root = createnode();


    // Read dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    node* head = root;

    // Read each character in dictionary
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // Check if newline
        if (c == '\n')
        {
            head->isendofword = true;
            head = root;
            d_size++;
        }
        else
        {
            int index = c_index(c);

            if (head->children[index] == NULL)
                head->children[index] = createnode();
            head = head->children[index];
        }
    }


    fclose(fp);
    return true;
}


//Returns number of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void)
{
    return d_size;
}

// deletes node and its children :(
void freenode(node* pnode)
{
    int i;
    for (i = 0; i <ALPHAS; i++)
    {
        if (pnode->children[i] !=NULL)
            freenode(pnode->children[i]);
    }
    free(pnode);
}


//Unloads dictionary from memory. Returns true if successful else false.
bool unload(void)
{
    freenode(root);
    return true;
}

