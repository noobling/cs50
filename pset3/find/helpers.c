/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

// prototype
bool bin_search(int low, int high, int values[], int value);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return bin_search(0, n, values, value);
}

bool bin_search(int low, int high, int values[], int value)
{
    if (low > high) { return false; }
    
    int midpoint = (high+low) / 2;
    if (values[midpoint] > value) 
    {
        return bin_search(low, midpoint-1, values, value);
    }
    else if (values[midpoint] < value)
    {
        return bin_search(midpoint+1, high, values, value);
    }
    else
    {
        return true;
    }
}
/**
 * Sorts array of n values.
 * 
 * Using bubble sort
 */
void sort(int values[], int n)
{
    int end = n - 1;
    for (int i = 0; i < end; i++)
    {
        for (int j = 0; j < end - i; j ++)
        {
            if (values[j] > values[j+1]) 
            {
                // swap values
                int temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
    
    return;
}