/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

trie* first = NULL;

// number of words in dictionary
int wc = 0;

/**
 * Returns true if word is in dictionary else false.
 * Traverses a trie to see if every letter in word exists in trie and
 * that the letters are in correct order.
 * Once we reach end of word and function has not been retunred prematurely 
 * we know word must exist in trie therefore a valid dictionary word
 */
bool check(const char* word)
{
    // the ith character of word
    int i = 0;
    
    trie* ptr = first;
    
    //debugging
    // for(int i = 0; i < 26; i++)
    // {
    //     if (ptr->paths[i] != NULL) {printf("s");}
    // }
    
    // go through each character of word
    while(word[i] != '\0')
    {
         // get trie array index
        int k;
        // when char is apostrophe
        if (word[i] == 39)
        {
            k = 26;
        }
        else
        {
            k = tolower(word[i]) - 'a';
        }
        
        // if path not there word must not exist in trie 
        if (ptr->paths[k] == NULL)
        {
            return false;
        }
        
        ptr = ptr->paths[k];
        
        // if the the word has ended and has isword to true, word exists in trie
        if (word[i+1] == '\0' && ptr->isword == true)
        {
            return true;
        }
        i++;
    }
    
    // letters exists in trie but isword is not true therefore word does not exist in trie
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    char word[LENGTH+1];
    
    first = calloc(1, sizeof(trie));
    // check for empty list
    if (first == NULL)
    {
        return false;
    }
    
    // Go through each word in dictionary and add them to trie
    while (fscanf(fp, "%s", word) == 1) 
    {
        int i = 0;
        trie* ptr = first;
        
        // go through each character in word
        while(word[i] != '\0')
        {
            // get trie array index
            int k;
            // when char is apostrophe
            if (word[i] == 39)
            {
                k = 26;
            }
            else
            {
                k = word[i] - 'a';
            }
            
            // check if path exists if not create one
            if (ptr->paths[k] == NULL)
            {
                // printf("s"); // debugging
                
                // make new trie at kth index
                ptr->paths[k] = calloc(1, sizeof(trie));
            } 
            
            // if true this means we have reached end of trie and word 
            if (word[i+1] == '\0')
            {
                // set isword to true because this represents the end of a word
                ptr->paths[k]->isword = true;
            }
            
            // move pointer to kth index since we know there will be a trie there
            ptr = ptr->paths[k];
            // increment i to evaluate next char in word
            i++;
        }
        // printf("\n"); // debugging
        
        // increment word count
        wc++;
    }
    
    // close dictionary file
    fclose(fp);
    
    // once every word has been added to trie return success
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wc;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unload_r(first);
    return true;
}

/** 
 * recursively frees allocated memory in trie
*/
void unload_r(trie* ptr)
{
    for(int i = 0; i < MPATH; i++)
    {
        if(ptr->paths[i] != NULL)
        {
            unload_r(ptr->paths[i]);    
        }
    }
    free(ptr);
}