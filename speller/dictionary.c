// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

//Number of word in dictionnary
int words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    if (strlen(word) == 1)
    {
        if (strcasecmp(word, table[index]->word) == 0)
        {
            //printf("true\n");
            return true;
        }
    }
    else
    {
        for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(word, tmp->word) == 0)
            {
                //printf("true\n");
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    // the number is indexed by 26 if it's only one letter
    if (strlen(word) == 1)
    {
        if (isupper(word[0]))
        {
            index = (word[0] - 65) * 26;
            return index;
        }
        else
        {
            index = (word[0] - 97) * 26;
            return index;
        }
    }
    //
    else
    {
        if (isupper(word[0]))
        {
            index += (word[0] - 65) * 26;
        }
        else
        {
            index += (word[0] - 97) * 26;
        }
        if (isupper(word[1]))
        {
            index += word[1] - 65;
        }
        else
        {
            index += word[1] - 97;
        }
        return index;
    }

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *fdict = fopen(dictionary, "r");
    if (fdict == NULL)
    {
        printf("Could not open dictionnary\n");
        return 1;
    }
    char mot[46];
    while (fgets(mot, sizeof(mot), fdict))
    {
        if (strcmp(mot, "\n") != 0)
        {
            mot[strcspn(mot, "\n")] = 0;

            // asking malloc to create an adress and the place to store the new node
            node *buffer = malloc(sizeof(node));

            // copying mot into the buffer
            strcpy(buffer->word, mot);

            // Asking hash function the number index in the alphabet
            unsigned int letter = hash(buffer->word);

            // if it's the first input next is NULL
            if (table[letter] == NULL)
            {
                buffer->next = NULL;
            }
            else
            {
                buffer->next = table[letter];
            }
            table[letter] = buffer;
            words++;
        }
    }
    fclose(fdict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        free(table[i]);
    }
    return true;
}