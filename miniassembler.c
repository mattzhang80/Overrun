/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai,                                  */
/* Editors: Matthew Zhang, Alex Delisthathis                          */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   unsigned int mask;
   assert(puiDest != NULL);

   /* Extract the relevant bits from uiSrc. */
   mask = ((1 << uiNumBits) - 1) << uiSrcStartBit;
   uiSrc = (uiSrc & mask) >> uiSrcStartBit;

   /* Shift these bits to the correct position in puiDest. */
   uiSrc <<= uiDestStartBit;

   /* Merge with the destination. */
   *puiDest |= uiSrc;

}

/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "mov reg, immed" where
   reg is a W register.

   Parameters:
      uiReg: the number of reg.  0 <= uiReg <= 31.
      iImmed: the immed value. -32768 <= iImmed <= 32767      */
unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* MOVZ (Move wide with zero) instruction base*/
    unsigned int uiInstr = 0x52800000; 
    assert(uiReg <= 31);
    assert(iImmed >= -32768 && iImmed <= 32767);

    /* Position the immediate value and the register number in the instruction */
    setField(uiReg, 0, &uiInstr, 0, 5);
    setField((unsigned int)iImmed, 0, &uiInstr, 5, 16);

    return uiInstr;
}

/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "adr reg, addr".

   Parameters:
      uiReg: the number of reg. 0 <= uiReg <= 31.
      ulAddr: the address denoted by addr.
      ulAddrOfThisInstr: the address of the adr instruction itself
                         (must be a multiple of 4).                   */

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "strb fromreg,[toreg]",
   where fromreg is a W register and toreg is a X register.

   Parameters:
      uiFromReg: the number of fromreg. 0 <= uiFromReg <= 31.
      uiToReg: the number of toreg.     0 <= uiToReg <= 31.           */
unsigned int MiniAssembler_strb(unsigned int uiFromReg, unsigned int uiToReg)
{
   /* STRB instruction base */
    unsigned int uiInstr = 0x39000000; 
    assert(uiFromReg <= 31);
    assert(uiToReg <= 31);

    /* Position the register numbers in the instruction */
    setField(uiFromReg, 0, &uiInstr, 0, 5); 
    setField(uiToReg, 0, &uiInstr, 5, 5);  

    return uiInstr;
}

/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "b addr".

   Parameters:
      ulAddr: the address denoted by addr, that is, the address to
         which the branch should occur (must be a multiple of 4).
      ulAddrOfThisInstr: the address of the b instruction itself
         (must be a multiple of 4).                                   */
unsigned int MiniAssembler_b(unsigned long ulAddr, unsigned long ulAddrOfThisInstr)
{
   /*B instruction base*/
    unsigned int uiInstr = 0x14000000; 

   /*Calculate offset, divide by 4 for instruction size */
   long offset = (ulAddr - ulAddrOfThisInstr) >> 2; 

   /* Position the offset in the instruction */
   setField((unsigned int)offset, 0, &uiInstr, 0, 26);

   return uiInstr;
}
