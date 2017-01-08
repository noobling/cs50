/* standard beginner programming problem
 * a lot of code is reused from previous
 * programming problem about 80%
 */
 
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

// prototype
void pshift_char(char c, int k);

/* 
 * Run program adding a word (key) as argument 
 * Enter your message to encrypt
 */ 
 
int main(int argc, string argv[]) 
{
    // throw error if user does not
    // enter correct number of arguments
    if (argc != 2) 
    { 
        printf("Usage: ./vignere [keyword]\n"); 
        return 1;
    }

    // getting the word/key
    string word = argv[1];
    int wlen = strlen(word);
    int j = 0;
    
    // checking that no numbers are in word
    for (int i = 0; i < wlen; i ++) 
    {
        if (!isalpha(word[i])) 
        {
            printf("The keyword must contain only alphabetical characters\n"); 
            return 1;   
        }
    }
    
    // get text to encrypt
    printf("plaintext: ");
    string text = GetString();
    int slen = strlen(text);

    // print out encrypted string
    printf("ciphertext: ");
    for (int i = 0; i < slen; i++)
    {
        char c = text[i];
        
        // determine how many places to shift char c
        char base = isupper(word[j]) ? 'A' : 'a';
        int k = word[j] - base; // Getting shift value
        
        if (isalpha(c)) 
        { 
            pshift_char(c, k); 
            j = (j + 1)%wlen;
        }
        else 
        { 
            printf("%c", c);
        }
    }
    
    printf("\n");
    return 0;
}

/* shift given char c, k places 
 * accounting for wrap around
 */
void pshift_char(char c, int k)
{
    char base = isupper(c) ? 'A' : 'a'; 
    printf("%c", base + ((c - base + k)%26));
}