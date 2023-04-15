#ifndef _ADD_H_
#define _ADD_H_

 /* routines which emulate the 8085 'ADD' 'SUB' etc, Instructions  */

/*------------------------------------------------------------------------*/
 int _Adi(void)
 {
   /* Add immediate to accumulator */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetMemByte(GetIP()+1),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetTemp(GetA()+GetMemByte(GetIP()+1));
   /* get the byte data following 'IP' */
   SetA(GetTemp() & MAX_INT);
   Set8085Flag();
   return ADI_LEN; /* this instruction takes 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _Aci(void)
 {
  /* Add immediate to accumulator with carry */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),
               GetMemByte(GetIP()+1)+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetTemp(GetA()+GetMemByte(GetIP()+1) + GetCarry());
   /* get the byte data following 'IP' */
   SetA(GetTemp() & MAX_INT);
   Set8085Flag();
   return ACI_LEN; /* this instruction takes 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _AdcB(void)
 {
   /* The contents of the operand and the carry flag are added to the
      contents of the accumulator and the result placed in the accumulator
      The previous carry flag is reset
   */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetB()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetB()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcC(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetC()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetC()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcD(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetD()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetD()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcE(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetE()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetE()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcH(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetH()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetH()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcL(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetL()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetL()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcM(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),
               GetMemByte(GetHL())+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetMemByte(GetHL())+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AdcA(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetA()+GetCarry(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetA()+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return ADC_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddB(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetB(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetB()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddC(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetC(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetC()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddD(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetD(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetD()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddE(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetE(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetE()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddH(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetH(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetH()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddL(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetL(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetL()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddM(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetMemByte(GetHL()),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetMemByte(GetHL())) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _AddA(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetA(),PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() + GetA()) & LARGEST_INT);
   Set8085Flag();
   return ADD_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _Sui(void)
 {
   /* Sub immediate to accumulator */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetMemByte(GetIP()+1),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetTemp(GetA()-GetMemByte(GetIP()+1));
   /* get the byte data following 'IP' */
   SetA(GetTemp() & MAX_INT);
   Set8085Flag();
   return SUI_LEN; /* this instruction takes 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _Sbi(void)
 {
  /* Sub immediate to accumulator with borrow */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),
               GetMemByte(GetIP()+1)+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetTemp(GetA()-GetMemByte(GetIP()+1) - GetCarry());
   /* get the byte data following 'IP' */
   SetA(GetTemp() & MAX_INT);
   Set8085Flag();
   return SBI_LEN; /* this instruction takes 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _SbbB(void)
 {
   /* The contents of the operand (register or memory) and the Borrow
      flag are subtracted from the contents of the accumulator and the
      results are placed in the accumulator.  The contents of the operand
      are not altered; however, the previous Borrow flag is rest.
   */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetB()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetB()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN;
   /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbC(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetC()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetC()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN;
   /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbD(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetD()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetD()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbE(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetE()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetE()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbH(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetH()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetH()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbL(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetL()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetL()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbM(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),
               GetMemByte(GetHL())+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetMemByte(GetHL()))+GetCarry()) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SbbA(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetA()+GetCarry(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-(GetA()+GetCarry())) & LARGEST_INT);
   Set8085Flag();
   return SBB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/

 int _SubB(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetB(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetB()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubC(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetC(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetC()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubD(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetD(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetD()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubE(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetE(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetE()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubH(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetH(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetH()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubL(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetL(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetL()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubM(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetMemByte(GetHL()),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetMemByte(GetHL())) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _SubA(void)
 {
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),GetA(),MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA() - GetA()) & LARGEST_INT);
   Set8085Flag();
   return SUB_LEN; /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _DadB(void)
 {
   /* the 16 bit contents of the specified register pair are added to the
      contents of the HL, register and the sum is saved in the HL register.
      if the result is larger than sixteen bits the CY flag is set.
   */

   if(SetTemp32((dword)GetHL()+(dword)GetBC()) > (dword)DOUBLE_INT)
    SetCarry(1);
   SetHL((word)((dword)GetTemp32() & (dword)DOUBLE_INT));
   return DAD_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _DadD(void)
 {
   if(SetTemp32((dword)GetHL()+(dword)GetDE()) > (dword)DOUBLE_INT)
    SetCarry(1);
   SetHL((word)(GetTemp32() & (dword)DOUBLE_INT));
   return DAD_LEN;;
 }
/*-----------------------------------------------------------------------*/
 int _DadH(void)
 {
   if(SetTemp32((dword)GetHL()+(dword)GetHL()) >(dword)DOUBLE_INT)
    SetCarry(1);
   SetHL((word)(GetTemp32() & (dword)DOUBLE_INT));
   return DAD_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _DadSP(void)
 {
   if(SetTemp32((dword)GetHL()+(dword)GetSP()) > (dword)DOUBLE_INT)
    SetCarry(1);
   SetHL((word)(GetTemp32() & (dword)DOUBLE_INT));
   return DAD_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Daa(void)
 {
   /*
     1.  If the value of the low order 4-bits (D3-D0) in the accumulator
         is greater than 9 or if 'AC' flag is set, the instruction adds
         6 to the low order four bits.
     2.  If the value of the high order 4 bits (D7-D4) in the accumulator
         is greater than 9 or if the carry flag is set the innstruction
         adds 6 to the high order four bits.
   */

   if(GetAuxCarry() || ((GetA() & 0xf)>9))
   {
     SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),6,PLUS));
     /* set the auxillary flag if there is a carry from bit D3 to D4 */
     SetTemp(GetA()+6);
     SetA(GetTemp() & MAX_INT);
     Set8085Flag();
   }
   if(GetCarry() || ((GetA() & 0xf0)>0x90))
   {
     SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),6,PLUS));
     /* set the auxillary flag if there is a carry from bit D3 to D4 */
     SetTemp(GetA()+0x60);
     SetA(GetTemp() & MAX_INT);
     Set8085Flag();
   }
   return DAA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrB(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetB(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetB(SetTemp(GetB()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrC(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetC(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetC(SetTemp(GetC()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrD(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetD(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetD(SetTemp(GetD()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrE(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetE(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetE(SetTemp(GetE()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrH(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetH(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetH(SetTemp(GetH()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrL(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetL(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetL(SetTemp(GetL()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrM(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetMemByte(GetHL()),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetMemByte(GetHL(),SetTemp(GetMemByte(GetHL())+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InrA(void)
 {
   /* increment contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),1,PLUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()+1) & MAX_INT);
   SetAllButCarry();
   return INR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _InxB(void)
 {
   /* Increment the contents of a register pair */
   SetBC(GetBC()+1);
   return INX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _InxD(void)
 {
   /* Increment the contents of a register pair */
   SetDE(GetDE()+1);
   return INX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _InxH(void)
 {
   /* Increment the contents of a register pair */
   SetHL(GetHL()+1);
   return INX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _InxSP(void)
 {
   /* Increment the contents of a register pair */
   SetSP(GetSP()+1);
   return INX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrB(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetB(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetB(SetTemp(GetB()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrC(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetC(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetC(SetTemp(GetC()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrD(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetD(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetD(SetTemp(GetD()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrE(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetE(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetE(SetTemp(GetE()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrH(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetH(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetH(SetTemp(GetH()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrL(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetL(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetL(SetTemp(GetL()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcrM(void)
 {
   /* decrement contents of register or memory location by 1 */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetMemByte(GetHL()),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetMemByte(GetHL(),SetTemp(GetMemByte(GetHL())-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _DcrA(void)
 {
   /* Decrement the contents of register  */
   SetAuxCarry(ShouldSetAuxillaryFlag(GetA(),1,MINUS));
   /* set the auxillary flag if there is a carry from bit D3 to D4 */
   SetA(SetTemp(GetA()-1) & MAX_INT);
   SetAllButCarry();
   return DCR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcxB(void)
 {
   /* Decrement the contents of a register pair */
   SetBC(GetBC()-1);
   return DCX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcxD(void)
 {
   /* Decrement the contents of a register pair */
   SetDE(GetDE()-1);
   return DCX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcxH(void)
 {
   /* Decrement the contents of a register pair */
   SetHL(GetHL()-1);
   return DCX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _DcxSP(void)
 {
   /* Decrement the contents of a register pair */
   SetSP(GetSP()-1);
   return DCX_LEN;
 }
/*------------------------------------------------------------------------*/

#endif