/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Binary Search

 int f=0, l=n, found =0;
 int m=(f+l)/2;
 while (1)
 {
  if (values[m]==value)
   {
    found =1;
    break;
   }
  else if (value <values[m]) 
   {
    f=m+1;
   }
  else 
   {
    l=m-1; 
   }
   m=(f+l)/2;
   if (f>l)
   {
    break;
   }
 } 

 if (found ==1)
 {
  return true;
 }
 else
 return false;

}

/**
 * Sorts array of n values.
 */
 // Bubble Sort 
void sort(int values[], int n)
{
   int swap , temp;
   for (int j=0; j < n; j++)
   { 
     
       for ( int i =0; i <= n; i++)
       {
           swap = 0;
           if ( values[i] < values[i+1])
           {
               temp = values[i];
               values[i] = values[i+1];
               values[i+1]=temp;
               swap = 1;
           }
       }
   }
    return;
}
