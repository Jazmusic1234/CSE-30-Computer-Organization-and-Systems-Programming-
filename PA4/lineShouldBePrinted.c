/*
 * Filename: lineShouldBePrinted.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/25/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa4.h"

/*
 * Function Name: lineShouldBePrinted()
 * Function Prototype: int lineShouldBePrinted( cont char * line, 
 *    const argInfo_t * info );
 * Description: Checks if line should be printed in search()
 * Parameters: line - line to check
 *             info - where to find regex pattern to check against line
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: if line should be printed, return 1
 *               if line should not be printed, return 0
 */

int lineShouldBePrinted( const char * line, const argInfo_t * info ) {
  int match = lineMatchesRegex(&(info->pattern), line);

  if((info->flags & ARG_V_FLAG) == ARG_V_FLAG) {
    if( match  == 0 ) {
      return 1;
    } else if( match == 1) {
      return 0;
    }
  }

  return match;
}
