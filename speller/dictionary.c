// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Prototypes of functions
//uint32_t jenkins_one_at_a_time_hash(const char *key, size_t length);
unsigned djb_hash(void *key, int len);
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// Define hash table size
#define HTSIZE 262144

// Define singly linked list node of type struct node
typedef struct _node
{
    char word[LENGTH + 1];
    struct _node *next;
}
node;

// Initialize a hash table of size HTSIZE (each element is a pointer to type struct node)
node *hashtable[HTSIZE] = {NULL};

// Initialize pointer to traverse through the linked list for checking
node *trav = NULL;

// Initialize HT size counter and a bool variable to indicate status of loading
bool loaded = false;
unsigned int count = 0;

// Initialize variable to store hash values
int hashval = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Convert word to lowercase before hashing
    char wordcopy[strlen(word) + 1];
    strcpy(wordcopy, word);

    for (int i = 0; i < strlen(wordcopy); i++)
    {
        if (isalpha(wordcopy[i]))
        {
            if (isupper(wordcopy[i]))
            {
                wordcopy[i] = tolower(wordcopy[i]);
            }
        }
    }

    // Hash the word to get the head pointer of the linked list it belongs to
    //hashval = jenkins_one_at_a_time_hash(wordcopy, strlen(wordcopy)) & (HTSIZE - 1);
    hashval = djb_hash(wordcopy, strlen(wordcopy)) & (HTSIZE - 1);

    // Point the node trav pointer to the head of the linked list
    trav = hashtable[hashval];

    // Traverse that linked list to check if the word exists
    while (trav != NULL)
    {
        if (!strcasecmp(word, trav->word))
        {
            // Report success
            return true;
        }

        // Move cursor to next node
        trav = trav->next;
    }

    // Report failure
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Create file pointer to dictionary and open for reading
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // Create a node pointer for each new node
    node *new_node;

    // Initialize string buffer to hold the read word
    char str[LENGTH + 1];

    // Iterate through words in dictionary and add them to the hash table
    while (fscanf(inptr, "%46s", str) != EOF)
    {
        // Allocate memory for new node
        new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy word into value field of struct node head
        strcpy(new_node->word, str);

        // Set the next field of node to point to what head is pointing to
        //hashval = jenkins_one_at_a_time_hash(str, strlen(str)) & (HTSIZE - 1);
        hashval = djb_hash(str, strlen(str)) & (HTSIZE - 1);
        new_node->next = hashtable[hashval];

        // Set the head pointer to point to the new node after it is linked to the rest of the linked list
        hashtable[hashval] = new_node;

        // Update size counter
        count++;
    }

    // Close the dictionary file
    fclose(inptr);

    // Set loaded to true
    loaded = true;

    // Return success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Create a pointer to traverse through the list
    node *cursor = NULL;

    // Create a temporary node to aid in freeing a node
    node *temp = NULL;

    // Loop through the indices of the hash table
    for (int i = 0; i < HTSIZE; i++)
    {
        // Set cursor to head of the current linked list
        cursor = hashtable[i];

        // Travserse through the linked list and free the nodes
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        // Check for failure
        if (cursor != NULL)
        {
            return false;
        }
    }

    // Report success
    return true;
}

// Bob Jenkins One-at-a-Time Hash function code: http://burtleburtle.net/bob/hash/doobs.html
// uint32_t jenkins_one_at_a_time_hash(const char *key, size_t length)
// {
//   size_t i = 0;
//   uint32_t hash = 0;
//   while (i != length)
//   {
//     hash += key[i++];
//     hash += hash << 10;
//     hash ^= hash >> 6;
//   }

//   hash += hash << 3;
//   hash ^= hash >> 11;
//   hash += hash << 15;
//   return hash;
// }

// Dan Bernstein's hash function
unsigned djb_hash(void *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;

    for (int i = 0; i < len; i++)
    {
        h = 33 * h + p[i];
    }

    return h;
}
