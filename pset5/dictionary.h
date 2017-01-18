/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// the maximum number of paths
#define MPATH 27

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);


/** 
 * Defines a trie struct
 */

typedef struct trie
{
    bool isword;
    // 27 possible paths 26 for alphabet and 1 for apostrophe
    struct trie* paths[MPATH];
}
trie;

/**
 * Unloads dictionary recursively
 */
void unload_r(trie* ptr);


#endif // DICTIONARY_H
