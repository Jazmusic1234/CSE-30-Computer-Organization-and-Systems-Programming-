/*
 * Filename: say.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/6/2019
 * Sources of help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function Name: say.c
 * Function Prototype: void say( const char * str, char on, char off );
 * Description: Print out each character in str
 * Parameters: str - string to print
 *             on - on char
 *             off - off char
 *
 * Side Effects: Print to stdout
 * Error conditions: if a char in str is not valid, print error statement
 * Return Value: None
 */

void say( const char * str, char on, char off ) {

  unsigned int pattern[PATTERN_LEN] = {0};

  const char * alpha[] = ALPHABET_PATTERNS;
  const char * digit[] = DIGIT_PATTERNS;
  
  for(int i = 0; i < strlen(str); i++) {
    int value = character(pattern, str[i], alpha, digit);
    if(value == -1) {
      printf("%s", STR_ERR_SAY_INVALID_CHAR); 
    } else {
      printPattern(pattern, on, off);
    }
  }


}
