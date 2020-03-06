/*
 * Filename: mygrep.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 6/1/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <getopt.h>

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Parses flags and arguments that are passed in and run 
 *        functionality of grep command
 * Parameters: argc - number of arguments passed in
 *             argv - array of arguments passed in
 *
 * Side Effects: Print error messages to stderr
 * Error Conditions: If arguments could not be parsed, error
 *                   If regular expression could not be parse, error
 * Return Value: If error, return EXIT_FAILURE
 *               Else, return EXIT_SUCCESS
 */

int main( int argc, char * argv[] ) {

  argInfo_t info;

  int loadInfo = processArgs(&info, argc, argv);
  if(loadInfo == ARG_PARSING_ERROR) {   // If parsing error
    fprintf(stderr, STR_SHORT_USAGE, argv[0], argv[0]);
    return EXIT_FAILURE;
  } else if(loadInfo == REGEX_ERROR) {   // If regex error
    fprintf(stderr, STR_ERR_REGEX);
    return EXIT_FAILURE;
  }

  if((info.flags & ARG_HELP_FLAG) == ARG_HELP_FLAG) {
    printf(STR_USAGE, argv[0], argv[0]);
    return EXIT_SUCCESS;
  }

  if(optind >= argc) {
    if((info.flags & ARG_C_FLAG) == ARG_C_FLAG) {
      count(&info, STR_STDIN);
    }
    search(&info, STR_STDIN);
  }

  while(optind < argc) {
    if((info.flags & ARG_C_FLAG) == ARG_C_FLAG) {
      count(&info, argv[optind]);
      optind++;
      continue;
    }
    search(&info, argv[optind]);
    optind++;
  }
  
  regfree(&(info.pattern));


}
