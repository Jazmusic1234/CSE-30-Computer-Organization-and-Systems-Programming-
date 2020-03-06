/*
 * Filename: search.c
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
 * Function Name: search()
 * Function Prototype: int search( const argInfo_t * info, 
 *        const char * filename );   
 * Description: Opens filename and prints out all lines that match regex pattern
 *        found in info. All outputs go to stdout
 * Parameters: info -  pointer to argInfo_t struct where regex pattern is
 *             filename - name of file to open 
 *
 * Side Effects: Prints output to stdout
 * Error Conditions: If file could not be opened, error
 * Return Value: If file cound not be opened, return -1
 *               Else, return 0
 */

int search( const argInfo_t * info, const char * filename ) {
  
  FILE * file = openFile(filename);
  
  // Check if file can be opened
  if(file == NULL) {
    return -1;
  }

  // Print each line that matches regex pattern
  int lineNum = 1;
  char * line = readLine(file);
  while(line != NULL) {
    
    if(lineShouldBePrinted(line, info) == 1) {    // If matches regex pattern
      
      if((info->flags & ARG_MULTI_FILE) == ARG_MULTI_FILE) {  // If multi files
        printf(STR_FILENAME, filename);
      } else if((info->flags & ARG_N_FLAG) == ARG_N_FLAG) { // If num flag
        printf(STR_LINENUM, lineNum);
      }
      printf(STR_LINE, line);
    
    }
    free(line);
    line = readLine(file);
    lineNum++;  
  }
  fclose(file);
  return 0;

}
