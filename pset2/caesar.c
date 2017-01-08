#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

// prototype
void pshift_char(char c, int k);

/*
 * Compile and run program with a number
 * as argument. 
 * This number is the key to encrypting
 * your mesage.
 * Enter your message to encrypt.
 */
int main(int argc, string argv[]) 
{
    // throw error if user does not
    // enter correct number of arguments
    if (argc != 2) 
    { 
        printf("Usage: ./caesar [non-negative number]\n"); 
        return 1;
    }

    // getting the key
    int k = atoi(argv[1]);
    
    // get text to encrypt
    printf("plaintext: ");
    string text = GetString();
    int slen = strlen(text);
    
    // print out encrypted string
    printf("ciphertext: ");
    for (int i = 0; i < slen; i++)
    {
        char c = text[i];
        if (isalpha(c)) { pshift_char(c, k); }
        else            { printf("%c", c); }
    }
    
    printf("\n");
    return 0;
}

/* 
 * shift given char c, k places 
 * accounting for wrap around
 */
void pshift_char(char c, int k)
{
    char base = isupper(c) ? 'A' : 'a'; 
    printf("%c", base + ((c - base + k)%26));
}