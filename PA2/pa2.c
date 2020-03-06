/*
 * Filename: pa2.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/8/2019
 * Sources of help: writeup, Week 3 Discussion Worksheet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function Name: pa2.c
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Parse command line arguments and start interactive mode
 * Parameters: argc - number of arguments
 *             argv - array of command line arguments
 *
 * Side Effects: None
 * Error conditions: if number of args are not within range
 *                   if first arg is not single character
 *                   if first arg is not within ascii range
 *                   if second arg is not single character
 *                   if second arg is not within ascii range
 * Return Value: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main( int argc, char * argv[] ) {
  char * first;
  char * second;

  char on = DEFAULT_ON_CHAR;
  char off = DEFAULT_OFF_CHAR;
  argc = argc - 1;

  // If more than 2 args
  if(argc < MIN_EXPECTED_ARGS || argc > MAX_EXPECTED_ARGS) {
    printf(STR_USAGE, argv[PROG_NAME_IDX], DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR,
           MIN_ASCII, MAX_ASCII);
    return EXIT_FAILURE;
  }
  if(argc > 0) {
    first = argv[ON_CHAR_IDX];
    // If first arg is more than 1 character
    if(first[1] != '\0') {
      printf(STR_ERR_SINGLE_CHAR, ON_ARG_NAME, first);
      return EXIT_FAILURE;
    }

    int ascii1 = (int)first[0];
    // If first arg is out of range
    if(ascii1 < MIN_ASCII || ascii1 > MAX_ASCII) {
      printf(STR_ERR_CHAR_RANGE, ON_ARG_NAME, ascii1, MIN_ASCII, MAX_ASCII); 
      return EXIT_FAILURE;
    }
    on = *first;
  }
  if(argc > 1) {
    second = argv[OFF_CHAR_IDX];
    // If second arg is more than 1 character
    if(second[1] != '\0') {
      printf(STR_ERR_SINGLE_CHAR, OFF_ARG_NAME, second);
      return EXIT_FAILURE;
    }

    int ascii2 = (int)second[0];
    // If first arg is out of range
    if(ascii2 < MIN_ASCII || ascii2 > MAX_ASCII) {
      printf(STR_ERR_CHAR_RANGE, second, ascii2, MIN_ASCII, MAX_ASCII); 
      return EXIT_FAILURE;
    }
    off = *second;
  }
  commandLoop(on, off);
  return EXIT_SUCCESS;
}
