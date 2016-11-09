/*
    Input a floating point number representing
    some amount of money.
    Output is the minimum number of coins you 
    get back consisting of only 25c/10c/5c/1c
    
*/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void) 
{
    int money;
    // Get money from user to calculate
    do 
    {
        printf("How much change is owed? ");
        // floats are not exact so we have to round
        money = round((GetFloat() * 100.0));
    } while (money < 0);
    
    // calculate minimum number of coins for
    // given money from user
    int count = 0;
    while (money > 0)
    {
        int change = 0;
        // find the biggest coin possible for
        // remaining money 
        if      (money - 25 >= 0) { change = 25; }
        else if (money - 10 >= 0) { change = 10; }
        else if (money - 5 >= 0)  { change = 5; }
        else                      { change = 1; }
        // update variables
        money = money - change;
        count++;
    }
    printf("%d\n", count);
}