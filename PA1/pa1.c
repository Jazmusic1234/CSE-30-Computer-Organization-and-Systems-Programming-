/*
 * Filename: pa1.c
 * Author: Jasmine Chen
 * Userid: cs30xax
 * Date: 4/23/2019
 * Sources of Help: writeup, Week 3 Discussion Worksheet
 */

#include "pa1.h"
#include "pa1Strings.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define BASE 10

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Checks that arguments are valid and then prints CoolS
 *    with given width and fillChar
 * Parameters: argc - number of command line arguments
 *             argv[] - array of command line arguments
 * Side Effects: prints to stdout and stderr
 * Error Conditions: 
 *    - must have 2 arguments
 *    - size must be a number between 3 and 103 and be in the format 4n+3
 *    - fillChar must be a single char between ascii values of 32 and 126
 * Return Value: EXIT_FAILURE if errors, and EXIT_SUCCESS otherwise
 */
int main( int argc, char * argv[] ) {
  char *endPtr;  // Used a ssecond param of strtol
  char errStr[BUFSIZ];  // Used to build up error string in snprintf
  long result;  // Used to hold return value from strtol

  if(argc != ARG_NUM) {
    fprintf(stderr, COOL_S_USAGE, argv[PROG_NAME_IDX], MIN_SIZE,
      MAX_SIZE, MIN_CHAR, MAX_CHAR);
      return EXIT_FAILURE;
  }

  errno = 0;
    
  result = strtol(argv[SIZE_IDX], &endPtr, BASE);

  if(errno) {
    snprintf(errStr, BUFSIZ, SIZE_CONVERT_ERR, argv[SIZE_IDX], BASE);
    perror(errStr);
    fprintf(stderr, "\n");
    return EXIT_FAILURE;
  }

  if(*endPtr != '\0') {
    fprintf(stderr, SIZE_NOT_INT_ERR, BASE);
    return EXIT_FAILURE;
  }

  if(result < MIN_SIZE || result > MAX_SIZE) {
    fprintf(stderr, SIZE_RANGE_ERR, MIN_SIZE, MAX_SIZE);
    return EXIT_FAILURE;
  }

  if(isDividable(result-3, 4) == 0) {
    fprintf(stderr, SIZE_FORMAT_ERR);
    return EXIT_FAILURE;
  }

  char fillChar = *argv[CHAR_IDX];
  if(strlen(argv[CHAR_IDX]) != 1) {
    fprintf(stderr, SINGLE_CHAR_ERR);
    return EXIT_FAILURE;
  }

  int fillCharAscii = (int)(fillChar);
  if(fillCharAscii < MIN_CHAR || fillCharAscii > MAX_CHAR) {
    fprintf(stderr, CHAR_RANGE_ERR, MIN_CHAR, MAX_CHAR);
    return EXIT_FAILURE;
  }

  drawCoolS(result, fillChar);
  return EXIT_SUCCESS;
}
