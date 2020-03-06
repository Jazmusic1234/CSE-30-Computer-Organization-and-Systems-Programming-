/*
 * Filename: readLine.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/25/2019
 * Sources of Help: writeup, piazza, geeksforgeeks, stack overflow
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: readLine()
 * Function Prototype: char * readLine( FILE * inputFile );
 * Description: Reads single line from inputFile, stopping at newline or EOF
 * Parameters: inputFile - file to read line from
 *
 * Side Effects: if error, print error statement to stderr
 * Error Conditions: Reached EOF
 *                   Memory allocation fails
 *                   
 * Return Value: if error occurs, return NULL
 *               else, return pointer to null-terminated string containing line
 */

char * readLine( FILE * inputFile ) {
  char * temp;

  char * s = calloc(1, sizeof(char));
  
  // If calloc fails
  if(s == NULL) {
    printf(STR_ERR_MEM_EXCEEDED);
    free(s);
    return NULL;
  }

  char buf[LINE_BUFFER_SIZE];

  // Loop through line
  while(1) {
    char * t = fgets(buf, LINE_BUFFER_SIZE, inputFile);

    // If empty file
    if(t == NULL && (s[0] == '\0')) {
      free(s);
      return NULL;
    }

    // Replace newline char with NULL char
    char * newline = strchr(buf, NEWLINE_CHAR);
    if(newline != NULL) {
      *newline = '\0';
      
      if(buf[0] == '\0' && (strcmp(s, "") == 0)) {    // If ""
        temp = realloc(s, sizeof(char));
        s = temp;
        strncat(s, buf, sizeof(char)); 
        break;
      }
      temp = realloc(s, strlen(buf) + strlen(s) + sizeof(char));
      s = temp;
      strncat(s, buf, strlen(buf)); 
      break;
    } 

    
    // Realloc string s
    if(strcmp(s, "") == 0) {
      temp = realloc(s, LINE_BUFFER_SIZE * sizeof(char));
    } else { 
      temp= realloc(s, (LINE_BUFFER_SIZE * sizeof(char)) + strlen(s));
    }

    // Reallocation failed
    if(temp == NULL) {
      printf(STR_ERR_MEM_EXCEEDED);
      free(s);
      return NULL;
    } else {    // Reallocation successful
      s = temp;
      strncat(s, buf, (LINE_BUFFER_SIZE + 1) * sizeof(char));
    }

  }


  return s;

}
