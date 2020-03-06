/*
 * Filename: count.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 6/1/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: count()
 * Function Prototype: int count( const argInfo_t * info, 
 *        const char * filename); 
 * Description: Counts number of lines in filename that match pattern found in
 *        info
 * Parameters: info - pointer to argInfo_t struct where regex pattern is 
 *             filename - name of file to open
 *
 * Side Effects: Prints output to stdout
 * Error Conditions: If file could not be opened, error
 * Return Value: If file could not be opened, return -1
 *               Else, return 0
 */

int count( const argInfo_t * info, const char * filename ) {

  FILE * file = openFile(filename);
  
  // Check if file can be opened
  if(file == NULL) {
    return -1;
  }

  // Count number of matches in file
  int sumMatches = 0;
  char * line = readLine(file);
  while(line != NULL) {
    
    if(lineMatchesRegex(&(info->pattern), line) == 1) {
      sumMatches++;  
    }
    free(line);
    line = readLine(file);

  }

  if((info->flags & ARG_MULTI_FILE) == ARG_MULTI_FILE) {  // If multi files
    printf(STR_FILENAME, filename);
  }

  printf(STR_COUNT, sumMatches);
  fclose(file);
  return 0;

}
