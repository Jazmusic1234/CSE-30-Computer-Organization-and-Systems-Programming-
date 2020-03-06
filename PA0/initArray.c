/*
 * Filename: initArray.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/7/2019
 * Sources of Help: Week 1 Discussion Worksheet 
 */

#include "pa0.h"

/*
 * Function Name: initArray()
 * Function Prototype: void initArray( int array[], int length );
 * Description: Initializes values in an array to be odd integers starting 
 *              from 1
 * Parameters: array - the array to initialize
 *             length - the length of the array
 * Side Effects: Initializes the values of the array
 * Error Conditions: None
 * Return Value: None
 */
void initArray( int array[], int length ) {
  int i = 0;
  while ( i < length ) {
    array[i] = ODD_MULTIPLIER * i + 1;
    i++;
  }
}
