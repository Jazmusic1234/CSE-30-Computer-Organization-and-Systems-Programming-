/*
 * Filename: drawCoolS.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/22/2019
 * Sources of Help: writeup
 */

#include "pa1.h"

/*
 * Function Name: drawStraight()
 * Funciton Prototype: void drawStraight( int size, char fillChar )
 * DescriptionL Prints the straight portion of the CoolS
 * Parameters: size - width of CoolS
 *             fillChar - char to fill CoolS with
 * Side Effects: prints to stdout
 * Error Conditions: None
 * Return Value: None
 */
void drawStraight( int size, char fillChar ) {
  int i;
  int j;
  for(i = 0; i < (size/HALF_DIVISOR - 1); i++ ) {
    for(j = 0; j < size; j++) {
      if(j == 0 || j == (size/HALF_DIVISOR) || j == size-1) {
        outputChar(PIPE_CHAR);    
      }
      else {
        outputChar(fillChar);
      }
    }
    outputChar(NEWLINE_CHAR);
  }
}

 /*
  * Function Name: drawCoolS()
  * Function Prototype: void drawCoolS( int size, char fillChar )
  * Description: Prints out CoolS
  * Parameters: size - width of CoolS
  *             fillChar - char to fill CoolS with
  * Side Effects: prints to stdout
  * Error Conditions: None
  * Return Value: None
  */
void drawCoolS( int size, char fillChar ) {
  drawCap(size, fillChar, DIR_UP); 
  drawStraight(size, fillChar);
  drawCrissCross(size, fillChar);
  drawStraight(size, fillChar);
  drawCap(size, fillChar, DIR_DOWN);
}


