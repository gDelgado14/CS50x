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
#include <math.h>
#include "helpers.h"
#include <stdbool.h>

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{

int lo, hi;

lo=0;
hi=n-1;

    while (lo < hi)
    {
       
        int middle = (lo + hi) / 2;
    
        if (value == values[middle])
        {
            return true;
        }
        else if (value > values[middle])
        {
            lo = middle + 1;
        }
        else
        {
            hi = middle - 1;
        }
    }
    
    return false;

}



/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

int swap;

    // TODO: implement an O(n^2) sorting algorithm
    for (int c = 0; c < (n -1); c++)
    {
        for (int d = 0; d < (n - c - 1); d++)
        {
            if (values[d] > values[d+1])
            {
             swap = values[d];
             values[d] = values[d+1];
             values[d+1] = swap;  
            }
        }
    }
    
    for (int c = 0; c < n;c++)
    {
        printf("value #%d is %d\n",c,values[c]);
    }
    return;
}
