#include <cs50.h>
#include <stdio.h>

/* 
 Takes in number of minutes
 Outputs number of bottles
*/
int main(void)
{
    int minutes;
    // get minutes from user
    printf("minutes: ");
    minutes = GetInt();
    
    // output result to user
    printf("bottles: %d\n", minutes * 12);
}