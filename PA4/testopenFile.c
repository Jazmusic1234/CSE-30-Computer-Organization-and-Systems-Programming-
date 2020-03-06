/*
 * Filename: openFile.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 6/1/2019
 * Sources of help: testprocessArgs.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for openFile.c
 *
 * FILE * openFile( const char * filename );
 *
 * Opens filename so it can be read. If filename is "-", return stdin
 *
 * Returns
 *  - NULL, if error
 *  - pointer to opened file, otherwise
 */

void testopenFile() {
  const char * filename;

  // Test filename is "-"
  filename = "-";
  TEST( openFile(filename) == stdin );

  // Test can't stat file
  filename = "abc";
  TEST( openFile(filename) == NULL );

  // Test file is directory
  filename = "/home/linux/ieng6/cs30x/cs30xax/pa4";
  TEST( openFile(filename) == NULL );

  // Test file "testData"
  filename = "/home/linux/ieng6/cs30x/cs30xax/pa4/testData";
  FILE * file = fopen(filename, "r");
  TEST( openFile(filename) == file );
  
}

int main( void ) {
  
  fprintf( stderr, "Running tests for openFile.c...\n" );
  testopenFile();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
