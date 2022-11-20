// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1170;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int n = hash(word);
    node *temp = table[n];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int n = (toupper(word[0]) - 'A') * 45;
    n += (strlen(word) - 1);

    return n;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *D = fopen(dictionary, "r");
    if (D == NULL)
    {
        printf("couldn't open file\n");
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char *words = malloc(LENGTH + 1);
    while (fscanf(D, "%s", words) == 1)
    {
        int x = hash(words);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, words);
        if (table[x] == NULL)
        {
            n->next = NULL;
            table[x] = n;
        }
        else
        {
            n->next = table[x];
            table[x] = n;
        }
        count++;
    }
    free(words);
    fclose(D);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}