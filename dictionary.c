// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Initialise word counter to -1 to account for final call
unsigned int word_counter = -1;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash provided word
    unsigned int index = hash(word);

    // Create tmp cursor for traversal
    node *cursor = table[index];

    // Check whether word is in list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
        cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function DJB2 from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    // tolower() ensures same hash irrespective of case
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Allocate space in memory for word buffer
    char *buffer = malloc(sizeof(char) * LENGTH + 1);
    if (buffer == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        // Create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Put data in node
        strcpy(n->word, buffer);
        n->next = NULL;

        // Hash word to obtain index value
        unsigned int index = hash(buffer);

        // Set new node to point at what the head is already pointing at
        n->next = table[index];

        // Set head to point to new node
        table[index] = n;

        size();
    }
    fclose(dict);
    free(buffer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    word_counter++;
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1)
        {
            return true;
        }
    }
    return false;
}
