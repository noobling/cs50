/* 
    Generates a mario pyramid according to 
    given height by user
    
    ===============Thoughts===============
    A very challenging problem especially given
    the fact that it is only week 1. If it was
    my uni we would still be doing 1+1 in the ide.
    
    There are a lot of ways to go about this.
    I am sure you could reduce my code at least
    by a half making it more efficient and readable.
    
    My approach was to tackle this problem in
    increments. Rather then trying to solve
    the whole problem in one go i.e. I asking myself
    "how can I just print out the first line when 
    user enters 8?" 
*/

#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int height;
    int hashTimes = 2;
    int spaceTimes = 0;
    // get height from user
    do 
    {
        printf("Height: ");
        height = GetInt();    
    } while (height < 0 || height > 23);
    
    
    // generate pyramid
    spaceTimes = height + 1 - hashTimes;
    while (spaceTimes > -1)
    {
        int spaceLeft = spaceTimes;
        int hashLeft = hashTimes;
        
        while (spaceLeft > 0) 
        {
            printf(" ");
            spaceLeft--;
        }
        
        while (hashLeft > 0) 
        {
            printf("#");
            hashLeft--;
        }
        printf("\n");
        spaceTimes--;
        hashTimes++;
    }
}