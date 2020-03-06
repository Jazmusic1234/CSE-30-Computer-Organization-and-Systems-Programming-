/*
 * Filename: openFile.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 6/1/2019
 * Sources of Help: writeup, Week 9 and 7 Discussion Worksheet
 */

#include <stdio.h>
#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <sys/stat.h>
#include <errno.h>

/*
 * Function Name: openFile()
 * Function Prototype: FILE * openFile( const char * filename );
 * Description: Opens filename so that it can be read. If filename is "-", use
 *        stdin instead.
 * Parameters: filename - name of file to be opened
 * Side Effects: None
 * Error Conditions: if can't stat file, error
                     if file is directory, error
                     if file could not be opened, error
 * Return Value: if error, return NULL
 *               else, return pointer to open file
 */

FILE * openFile( const char * filename ) {

  // If file name is "-", return stdin
  if(strcmp(filename, "-") == 0) {
    return stdin;
  }

  // Check if file is regular file
  struct stat sbuf;

  errno = 0;
  stat(filename, &sbuf);

  // If error when calling stat on file
  if(errno != 0) {
    fprintf(stderr, STR_ERR_OPEN_FILE, filename, strerror(errno));
    return NULL;
  }

  // Check if file is directory
  if(S_ISDIR(sbuf.st_mode)) {
    fprintf(stderr, STR_ERR_OPEN_FILE, filename, strerror(EISDIR));
    return NULL;
  }

  // Try opening file
  FILE * file = fopen(filename, "r");
  if(errno != 0) {
    fprintf(stderr, STR_ERR_OPEN_FILE, filename, strerror(errno));
    return NULL;
  }

  return file;

}
