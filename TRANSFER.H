#ifndef _TRANSFER_C_
 #define _TRANSFER_C_

 /* functions which emulate the 8085 data transfer instructions */

/*------------------------------------------------------------------------*/
 int _StaxB(void)
 {
   /* copy the data byte from the accumulator into the memory location
      specified by register pair
   */
   SetMemWord(GetBC(),GetA());
   return STAX_LEN;
    /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _StaxD(void)
 {
   /* copy the data byte from the accumulator into the memory location
      specified by register pair
   */
   SetMemWord(GetDE(),GetA());
   return STAX_LEN;
     /* return the no. of bytes by which ip should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _LdaxB(void)
 {
   /* load the accumulator with the contents of memory location pointed
      by register pair 'BC'.  1 byte instruction
   */
   SetA(GetMemWord(GetBC()));
   return LDAX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LdaxD(void)
 {
   /* load the accumulator with the contents of memory location pointed
      by register pair 'DE'.  1 byte instruction
   */
   SetA(GetMemWord(GetDE()));
   return LDAX_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LHLd(void)
 {
   /* load HL direct.
      load HL register with contents of memory location whose address
      is provided as immediate
   */
   SetHL(GetMemWord(GetMemWord(GetIP()+1)));
   return LHLD_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LdA(void)
 {
   /* Load accumulator direct.
      Load accumulator with contents of memory location whose
      address is given as immediate value
   */
   SetA(GetMemByte(GetMemWord(GetIP()+1)));
   return LDA_LEN;
 }
/*------------------------------------------------------------------------*/
 int _SHLd(void)
 {
   /* store HL direct
      store the contents of HL register into memory location specified as
      immediate operand
   */
   SetMemWord(GetMemWord(GetIP()+1), GetHL());
   return SHLD_LEN;
 }
/*------------------------------------------------------------------------*/
 int _StA(void)
 {
   /* Store accumulator direct
      The contents of accumulator are copied onto memory location as
      specified by the 16 bit immediate address
   */

   SetMemByte(GetMemWord(GetIP()+1),GetA());
   return STA_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LxiB(void)
 {
   /* load register pair immediate  */
   SetBC(GetMemWord(GetIP()+1));
   return LXI_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LxiD(void)
 {
   /* load register pair immediate  */
   SetDE(GetMemWord(GetIP()+1));
   return LXI_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LxiH(void)
 {
   /* load register pair immediate  */
   SetHL(GetMemWord(GetIP()+1));
   return LXI_LEN;
 }
/*------------------------------------------------------------------------*/
 int _LxiSP(void)
 {
   /* load register pair immediate  */
   SetSP(GetMemWord(GetIP()+1));
   return LXI_LEN;
 }
/*------------------------------------------------------------------------*/
 int _SPHL(void)
 {
   /* copy H and L registers to the stack pointer */
   SetSP(GetHL());
   return SPHL_LEN;
 }
/*------------------------------------------------------------------------*/
 int _XtHL(void)
 {
  /* exchange HL with top of stack */


   SetTemp(GetHL());              /* temporarily save HL */
   SetHL(GetMemWord(GetSP()));    /* get top of stack */
   SetMemWord(GetSP(),GetTemp()); /* move temp to top of stack */
   /* this could be alternatively achieved by push and pop */
   return XTHL_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Xchg(void)
 {
   /* exchange HL and DE */

   SetTemp(GetHL());   /* temporarily save hl */
   SetHL(GetDE());
   SetDE(GetTemp());
   return XCHG_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Out(void)
 {
   /* the contents of the accumulator are copied into the I/O port
      specified by the operand
   */
   outportb(GetMemByte(GetIP()+1),GetA());
   return OUT_LEN;
 }
/*------------------------------------------------------------------------*/
 int _In(void)
 {
   /* the contents of the input port designated in the operand are read
      and loaded into the accumulator.
   */
   SetA(inportb(GetMemByte(GetIP()+1)));
   return IN_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PushB(void)
 {
   SetSP(GetSP()-2);                 /* decrement SP first */
   SetMemWord(GetSP(),GetBC());      /* push the data */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PushD(void)
 {
   SetSP(GetSP()-2);                 /* decrement SP first */
   SetMemWord(GetSP(),GetDE());      /* push the data */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PushH(void)
 {
   SetSP(GetSP()-2);                 /* decrement SP first */
   SetMemWord(GetSP(),GetHL());      /* push the data */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PushPSW(void)
 {
   SetSP(GetSP()-2);                 /* decrement SP first */
   SetMemWord(GetSP(),GetPsw());      /* push the data */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PopB(void)
 {
   SetBC(GetMemWord(GetSP()));  /* get the word and save it into reg pair */
   SetSP(GetSP()+2);            /* increment sp */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PopD(void)
 {
   SetDE(GetMemWord(GetSP()));  /* get the word and save it into reg pair */
   SetSP(GetSP()+2);            /* increment sp */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PopH(void)
 {
   SetHL(GetMemWord(GetSP()));  /* get the word and save it into reg pair */
   SetSP(GetSP()+2);            /* increment sp */
   return PUSH_LEN;
 }
/*------------------------------------------------------------------------*/
 int _PopPSW(void)
 {
   SetPsw(GetMemWord(GetSP())); /* get the word and save it into reg pair */
   SetSP(GetSP()+2);            /* increment sp */
   return POP_LEN;
 }
/*------------------------------------------------------------------------*/
#endif