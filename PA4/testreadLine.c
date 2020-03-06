/*
 * Filename: testreadLine.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/29/2019
 * Sources of help: testprocessArgs.c
 */

#include <stdio.h>
#include <string.h>
#include <string.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for readLine.c
 *
 * char * readLine( FILE * inputFile );
 *
 * Reads single line from inputFile, stopping at newline or EOF
 *
 * Returns
 *  - NULL if reached EOF while string is empty or memory allocation fails,
 *  - otherwise returns pointer to null-terminated string containing file line.
 */
void testreadLine() {

  // Test small data
  FILE * file = fopen("/home/linux/ieng6/cs30x/cs30xax/pa4/testSmallData", "r");
  TEST( strcmp(readLine(file), "Hello World") == 0 );
  fclose(file);

  // Test empty file
  FILE * file1 = fopen("/home/linux/ieng6/cs30x/cs30xax/pa4/testEmptyData", "r");
  TEST( readLine(file1) == NULL );
  fclose(file1);

  // Test large data
  FILE * file2 = fopen("/home/linux/ieng6/cs30x/cs30xax/pa4/testData", "r");
  char * line =  "Twelve-year-old Percy Jackson is on the most dangerous "
  "quest of his life. With the help of a satyr and a daughter of Athena, "
  "Percy must journey across the United States to catch a thief who has "
  "stolen the original weapon of mass destruction - Zeus' master bolt.";
  TEST( strcmp(readLine(file2), line) == 0);
  fclose(file2);

  // Test newline file
  FILE * file3 = fopen("/home/linux/ieng6/cs30x/cs30xax/pa4/testNewlineData", "r");
  TEST( strcmp(readLine(file3), "")  == 0);
  fclose(file3);

  // Test exact length
  FILE * file4 = fopen("/home/linux/ieng6/cs30x/cs30xax/pa4/testExactSize", "r");
  line = "aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa "
  "aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa aa";
  TEST( strcmp(readLine(file4), line) == 0); 
  fclose(file4);

  
}

int main( void ) {
  
  fprintf( stderr, "Running tests for readLine.c...\n" );
  testreadLine();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
