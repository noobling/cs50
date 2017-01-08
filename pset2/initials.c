#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

/*
 * Compile and run program.
 * Enter a name in the prompt.
 * Output will be that name initalised 
 * in all capitals.
 *
 * Example: outputs "MB" for "Milo Banana"
 *
 */
int main(void) 
{
    // Get their name 
    string name = GetString();
    int s_length = strlen(name);
    
    // capitalise and print first
    // letter of name
    printf("%c", toupper(name[0]));
    
    // look for white spaces then
    // capitalise the proceeding letter
    for (int i = 0; i < s_length; i++) 
    {
        if (isspace(name[i]))
        {
            printf("%c", toupper(name[i+1]));
        }
    }
 
    printf("\n");
}
