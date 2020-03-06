/*
 * Filename: printReversed.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/7/2019
 * Sources of Help: 
 */

#include <stdio.h>

/*
 * Function Name: printReversed()
 * Function Prototype: void printReversed( int array[], int length );
 * Description: Prints out an array in reverse order
 * Parameters: array - the array to print
 *             length - the length of the array
 * Side Effects: Prints out the array in reverse order to stdout
 * Error Conditions: None
 * Return Value: None
 */
void printReversed( int array[], int length ) {
  int i;

  for ( i = length - 1; i >= 0; i-- ) {
    printf( "%d\n", array[i] );
  }
}

