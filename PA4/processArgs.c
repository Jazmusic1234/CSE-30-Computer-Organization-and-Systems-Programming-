/*
 * Filename: processArgs.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/25/2019
 * Sources of Help: writeup, Week 8 and 7 Discussion Worksheet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa4.h"
#include <getopt.h>
#include <regex.h>

static struct option options[] = {
  {PATTERN_LONG, required_argument, NULL, PATTERN_FLAG},
  {IGNORE_CASE_LONG, no_argument, NULL, IGNORE_CASE_FLAG},
  {INVERT_MATCH_LONG, no_argument, NULL, INVERT_MATCH_FLAG},
  {COUNT_LONG, no_argument, NULL, COUNT_FLAG},
  {LINE_NUMBER_LONG, no_argument, NULL, LINE_NUMBER_FLAG},
  {HELP_LONG, no_argument, NULL, HELP_FLAG},
  {0, 0, 0, 0}
};

/*
 * Function Name: processArgs()
 * Function Prototype: int processArgs( argInfo_t * info, int argc, 
 *    char * argv[] );
 * Description: Populates info with regex pattern and bit pattern representing
 *    which flags were set in command args
 * Parameters: info - struct to store regex pattern and bit pattern with
 *             argc - number of args
 *             argv - array of command line args
 *
 * Side Effects: None
 * Error Conditions: invalid flag or no pattern arg
 *                   regcomp() returns non-zero value
 *                   
 * Return Value: if error occurs while parsing flags, return ARG_PARSING_ERROR
 *               if pattern failed to compile, return REGEX_ERROR
 *               else, return 0
 */
int processArgs( argInfo_t * info, int argc, char * argv[] ) {
  // local vars
  int c;
  
  int patternSet = 0;
  int cflags = REG_EXTENDED | REG_NOSUB;

  // Setting pattern 
  int rc = 0;
  char * p = "";

  // Setting flags in info
  info->flags = 0;

  while((c = getopt_long(argc, argv, SHORT_OPTS, options, NULL)) != -1) {
    
    switch(c) {

      // Regexp case flag detected
      case PATTERN_FLAG:
        patternSet = 1;
        p = optarg;
        break;
      
      // Help flag detected
      case HELP_FLAG:
        info->flags = info->flags | ARG_HELP_FLAG;
        return 0;

      // Ignore case flag detected
      case IGNORE_CASE_FLAG:
        info->flags = info->flags | ARG_I_FLAG;
//        cflags = cflags | REG_ICASE;
        break;
        
      // Invert match flag detected
      case INVERT_MATCH_FLAG:
        info->flags = info->flags | ARG_V_FLAG;
        break;

      // Count flag detected
      case COUNT_FLAG:
        info->flags = info->flags | ARG_C_FLAG;
        break;

      // Line number flag detected
      case LINE_NUMBER_FLAG:
        info->flags = info->flags | ARG_N_FLAG;
        break;

      // Unexpected flag detected
      default:
        return ARG_PARSING_ERROR;
  
    }
  }

  // If multiple files
  if((argc - optind) > 1) {
    info->flags = info->flags | ARG_MULTI_FILE;
  }

  if((info->flags & ARG_I_FLAG) == ARG_I_FLAG) {
    cflags = cflags | REG_ICASE;
  }


  if(patternSet == 0) {    
    if(optind >= argc) {
      return ARG_PARSING_ERROR;
    } else {
      p = argv[optind];
      optind++;
    }
  } 
  
  // Compile pattern into regex_t and store into first parameter
  rc = regcomp(&(info->pattern), p, cflags);

  // If error
  if(rc != 0) {
    return REGEX_ERROR;
  }


  return 0;  

}
