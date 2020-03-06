/*
 * Filename: outputCharNTimes.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: writeup
 */

#include "pa1.h"

/*
 * Function Name: outputCharNTimes()
 * Function Prototype: void outputCharNTimes( char ch, int n )
 * Description: Prints the given character, ch, n times
 * Parameters: ch - given character to print
 *             n - number of times to print ch
 * Side Effects: prints to stdout
 * Error Conditions: None
 * Return Value: None
 */
void outputCharNTimes( char ch, int n ) {
  int i;
  for( i = 0; i < n; i++) {
    outputChar( ch );
  }
}

