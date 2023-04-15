#ifndef _PARSE_H_
 #define _PARSE_H_

 /* functions to parse a given 8085 assembly language instruction.
    These functions return an appropriate error number if the instrucion
    is incorrect, else, insert the equivalent opcode at the position
    pointed by 'PTR()' and return the length of the instruction
 */

/*-----------------------------------------------------------------------*/
 int MovParse(void)
 {
  int   mem=0;  /* to validate an instruction from transfering data
		 from memory to memory, which is illegal */

   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN()))
     return REG_OR_MEM_EXPECT;
   if(IsMem(TOKEN())) ++mem;
   r1 = RegNumber(); /* get the register number */
   /* it was an identifier but was not a valid register or memory location*/
   if(Advance(0)!=COMMA) return COMMA_EXPECTED;
   /* should be a comma ',' */
   if(Advance(1)!=IDENTIFIER || (!IsRegs(TOKEN()) && !IsMem(TOKEN())))
     return REG_OR_MEM_EXPECT;
   if(IsMem(TOKEN()) && mem>=1) return MEM_TO_MEM_TRANSFER;
   /* tried to move from memory to memory */
   r2 = RegNumber();

   code = MOV_START+Displacement(r1,r2);
   return InsertMachineCode(code);
 }
/*-----------------------------------------------------------------------*/
 int MviParse(void)
 {
    if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
    /* should be an identifier to be the name of a register */
    if(!IsRegs(TOKEN()) && !IsMem(TOKEN()))
      return REG_OR_MEM_EXPECT;
    /* it was an identifier but was not a valid register or memory location*/
    r1 = RegNumber();
    if(Advance(0)!=COMMA) return COMMA_EXPECTED;  /* should be a ',' */
    if(Advance(0)!=NUMBER) return NUMBER_EXPECT; /* should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_INT) return LARGE_NUMBER;
    /* the number specified was too large */
    SetImmediate((unsigned)X);
    /* assign the value X to the variable 'immediate' in _8085 because
       necessary immediate values are taken from the variable 'immediate'
    */
    code =  MVI_START+Displacement(r1,0);
    return InsertCodeAnd8Bit(code,(char)X);
 }
/*-----------------------------------------------------------------------*/
 int LdaxParse(void)
 {
   /* load accumulator indirect */
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN())) return REGISTER_EXPECT;
   /* it was an identifier but was not a valid register */
   if((r1 = RegNumber())!= _B  && r1!=_D)
     return WRONG_REG;
   return InsertMachineCode(LDAX_START + Displacement(r1,0));
 }
/*----------------------------------------------------------------------*/
 int LHLdParse(void)
 {
   /* load HL direct */

   if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
   if((data=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(LHLD_START,(unsigned)data);
 }
/*-----------------------------------------------------------------------*/
 int LdAParse(void)
 {
   /* Load accumulator direct */

   if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
   if((data=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(LDA_START,(unsigned)data);
 }
/*-----------------------------------------------------------------------*/
 int StaxParse(void)
 {
   /* store accumulator indirect */

   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   if(!IsRegs(TOKEN())) return REGISTER_EXPECT;
   if((r1 = RegNumber())!= _B  && r1!=_D)
     return WRONG_REG;
   return InsertMachineCode(STAX_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int SHLdParse(void)
 {
   /* contents of HL register are stored in memory location as specified
      by 16 bit immediate address
   */
    if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
     /* The immediate data should be a number */
    if((addr=StrToNum()) > LARGEST_ADDR)
      return ADDR_TOO_LARGE; /* the address specified was too large */
    return InsertCodeAnd16Bit(SHLD_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int StAParse(void)
 {
   /* store accumulator direct */

    if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
     /* The immediate data should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_ADDR)
       return ADDR_TOO_LARGE; /* the address specified was too large */
    return InsertCodeAnd16Bit(STA_START,(unsigned)X);
 }
/*-----------------------------------------------------------------------*/
 int LxiParse(void)
 {
   /* load register pair immediate */
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1 = RegNumber())!= _B  && r1!=_D && r1!=_H && r1!=_SP)
     return WRONG_REG;
   if(Advance(0)!=COMMA) return COMMA_EXPECTED;
   if((data=Advance(0))!=NUMBER) return NUMBER_EXPECT;
   if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
    return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
   else if(X > DOUBLE_INT) return LARGE_NUMBER;
   /* the number specified was too large */
   r1 = r1==_SP ? _M : r1;
   /* Some adjustment is required here because the code name is not linear.
      By normal convention the code generated should be
      LXI_START + _SP*8
      but the code generated in the 8085 kit in the case of Lxi
      replaces 'SP' by 'M', hence the actual code generated becomes
      LIX_START + _M*8
    */
   return InsertCodeAnd16Bit(LXI_START + Displacement(r1,0),(unsigned)X);
 }
/*-----------------------------------------------------------------------*/
 int SPHLParse(void)
 {
   return InsertMachineCode(SPHL_START);
 }
/*-----------------------------------------------------------------------*/
 int XtHLParse(void)
 {
   return InsertMachineCode(XTHL_START);
 }
/*-----------------------------------------------------------------------*/
 int XchgParse(void)
 {
   return InsertMachineCode(XCHG_START);
 }
/*-----------------------------------------------------------------------*/
 int OutParse(void)
 {
    if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
    if((data=StrToNum()) > MAX_INT) return LARGE_NUMBER;
    return InsertCodeAnd8Bit(OUT_START,data);
 }
/*-----------------------------------------------------------------------*/
 int InParse(void)
 {
    if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
    if((data=StrToNum()) > MAX_INT) return LARGE_NUMBER;
    return InsertCodeAnd8Bit(IN_START,data);
 }
/*-----------------------------------------------------------------------*/
 int PushParse(void)
 {
   /* the advance function can be buggy because
      a 'push bc' will also be accepted
   */
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())!=_B && r1!=_D && r1!=_H && r1!=_PSW)
     return WRONG_REG;
   if(r1==_PSW) r1=_M;
   /* Some adjustment is required here because the code name is not linear.
      By normal convention the code generated should be
      LXI_START + _SP*8
      but the code generated in the 8085 kit in the case of Lxi
      replaces 'SP' by 'M', hence the actual code generated becomes
      LIX_START + _M*8
    */
   return InsertMachineCode(PUSH_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int PopParse(void)
 {
   /* the advance function can be buggy because
      a 'pop bc' will also be accepted
   */
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())!=_B && r1!=_D && r1!=_H && r1!=_PSW)
     return WRONG_REG;
   if(r1==_PSW) r1=_M;
   /* Some adjustment is required here because the code name is not linear.
      By normal convention the code generated should be
      LXI_START + _SP*8
      but the code generated in the 8085 kit in the case of Lxi
      replaces 'SP' by 'M', hence the actual code generated becomes
      LIX_START + _M*8
    */
   return InsertMachineCode(POP_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int AddParse(void)
 /* parse an add instruction */
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN())) return REGISTER_EXPECT;
   /* it was an identifier but was not a valid register or memory location*/
   r1 = RegNumber();
   code = ADD_START+Displacement(0,r1);
   InsertMachineCode(code);
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int AdcParse(void)
 /* parse an add instruction */
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN())) return REGISTER_EXPECT;
   /* it was an identifier but was not a valid register or memory location*/
   InsertMachineCode(ADC_START+Displacement(0,RegNumber()));
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int AdiParse(void)
  /* Parse an add immediate instructions */
 {

    if(Advance(0)!=NUMBER) return NUMBER_EXPECT; /* should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_INT) return LARGE_NUMBER;
    /* the number specified was too large */
   return InsertCodeAnd8Bit(ADI_START,X);
 }
/*-----------------------------------------------------------------------*/
 int AciParse(void)
  /* Parse an add immediate with carry instructions */
 {

    if(Advance(0)!=NUMBER) return NUMBER_EXPECT; /* should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_INT) return LARGE_NUMBER;
    /* the number specified was too large */
    return InsertCodeAnd8Bit(ACI_START,X);
 }
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/

 int SubParse(void)
 /* parse an add instruction */
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN())) return REGISTER_EXPECT;
   /* it was an identifier but was not a valid register or memory location*/
   InsertMachineCode(SUB_START+Displacement(0,RegNumber()));
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int SbbParse(void)
 /* parse an add instruction */
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN())) return REGISTER_EXPECT;
   /* it was an identifier but was not a valid register or memory location*/
   InsertMachineCode(SBB_START+Displacement(0,RegNumber()));
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int SuiParse(void)
 {
  /* Parse an subtract immediate instructions */

    if(Advance(0)!=NUMBER) return NUMBER_EXPECT; /* should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_INT) return LARGE_NUMBER;
    /* the number specified was too large */
    return InsertCodeAnd8Bit(SUI_START,X);
 }
/*-----------------------------------------------------------------------*/
 int SbiParse(void)
 {
   /* Parse an subtract immediate with carry instructions */

    if(Advance(0)!=NUMBER) return NUMBER_EXPECT; /* should be a number */
    if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
     return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
    else if(X > LARGEST_INT) return LARGE_NUMBER;
    /* the number specified was too large */
    return InsertCodeAnd8Bit(SBI_START,X);
 }
/*-----------------------------------------------------------------------*/
 int DadParse(void)
 {
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())!=_B && r1!=_D && r1!=_H && r1!=_SP)
     return WRONG_REG;
   if(r1==_SP) r1=_M;
   /* Some adjustment is required here because the code name is not linear.
      By normal convention the code generated should be
      DAD_START + _SP*8
      but the code generated in the 8085 kit in the case of Lxi
      replaces 'SP' by 'M', hence the actual code generated becomes
      DAD_START + _M*8
    */
   return InsertMachineCode(DAD_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int DaaParse(void)
 {
   return InsertMachineCode(DAA_START);
 }
/*-----------------------------------------------------------------------*/
 int InrParse(void)
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(INR_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int InxParse(void)
 {
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())!=_B && r1!=_D && r1!=_H && r1!=_SP)
     return WRONG_REG;
   r1 = r1==_SP ? _M : r1;
   return InsertMachineCode(INX_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int DcrParse(void)
 {
   if(Advance(1)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(DCR_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int DcxParse(void)
 {
   if(Advance(0)!=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())!=_B && r1!=_D && r1!=_H && r1!=_SP)
     return WRONG_REG;
   r1 = r1==_SP ? _M : r1;
   return InsertMachineCode(DCX_START + Displacement(r1,0));
 }
/*-----------------------------------------------------------------------*/
 int  StCParse(void)
 {
   return InsertMachineCode(STC_START);
 }
/*-----------------------------------------------------------------------*/
 int AnaParse(void)
 {
   /* Bitwise 'AND' the contents of accumulator and another register or
      memory and store the result in the accumulator
   */
   if(Advance(1) !=IDENTIFIER) return REGISTER_EXPECT;
      if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(ANA_START+r1);
 }
/*-----------------------------------------------------------------------*/
 int AniParse(void)
 {

   /* Bitwise 'AND' the contents of accumulator and a immediate value
     memory and store the result in the accumulator
   */
   if(Advance(0) !=NUMBER) return NUMBER_EXPECT;
   if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
    return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
   else if(X > LARGEST_INT) return LARGE_NUMBER;
   /* the number specified was too large */
   return InsertCodeAnd8Bit(ANI_START,(char)X);
 }
/*-----------------------------------------------------------------------*/
 int XraParse(void)
 {
   /* Bitwise 'XOR' the contents of accumulator and another register or
      memory and store the result in the accumulator
   */
   if(Advance(1) !=IDENTIFIER) return REGISTER_EXPECT;
      if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(XRA_START+r1);
 }
/*-----------------------------------------------------------------------*/
 int XriParse(void)
 {
   /* Bitwise 'XOR' the contents of accumulator and a immediate value
     memory and store the result in the accumulator
   */

   if(Advance(0) !=NUMBER) return NUMBER_EXPECT;
   if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
    return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
   else if(X > LARGEST_INT) return LARGE_NUMBER;
   /* the number specified was too large */
   return InsertCodeAnd8Bit(XRI_START,(char)X);
 }
/*-----------------------------------------------------------------------*/
 int OraParse(void)
 {
   /* Bitwise 'OR' the contents of accumulator and another register or
      memory and store the result in the accumulator
   */
   if(Advance(1) !=IDENTIFIER) return REGISTER_EXPECT;
      if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(ORA_START+r1);
 }
/*-----------------------------------------------------------------------*/
 int OriParse(void)
 {

   /* Bitwise 'OR' the contents of accumulator and a immediate value
     memory and store the result in the accumulator
   */
   if(Advance(0) !=NUMBER) return NUMBER_EXPECT;
   if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
    return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
   else if(X > LARGEST_INT) return LARGE_NUMBER;
   /* the number specified was too large */
   return InsertCodeAnd8Bit(ORI_START,(char)X);
 }
/*-----------------------------------------------------------------------*/
 int CmpParse(void)
 {
   /* Compare the contents of accumulator and another register or
      memory and store the result of comparison in the flag regs
   */
   if(Advance(1) !=IDENTIFIER) return REGISTER_EXPECT;
   if((r1=RegNumber())==0xFFFF || r1==_PSW)  return WRONG_REG;
   /* 0xffff is equivalent to -1 */
   return InsertMachineCode(CMP_START + r1);
 }
/*-----------------------------------------------------------------------*/
 int CpiParse(void)
 {
   /* Compare the contents of accumulator and an immediate value
      memory and store the result of comparison in the flag regs
   */
   if(Advance(0) !=NUMBER) return NUMBER_EXPECT;
   if((X=StrToNum()) == __BAD_NUMBER_FORMAT)
    return BAD_NUMBER_FORMAT; /* eg:- an octal number contained a '9' */
   else if(X > LARGEST_INT) return LARGE_NUMBER;
   /* the number specified was too large */
   return InsertCodeAnd8Bit(CPI_START,(char)X);
 }
/*-----------------------------------------------------------------------*/
 int RlcParse(void)
 {
  /* rotate left without carry */
   return InsertMachineCode(RLC_START);
 }
/*-----------------------------------------------------------------------*/
 int RrcParse(void)
 {
  /* rotate right without carry */
   return InsertMachineCode(RRC_START);
 }
/*-----------------------------------------------------------------------*/
 int RalParse(void)
 {
  /* rotate left with carry */
   return InsertMachineCode(RAL_START);
 }
/*-----------------------------------------------------------------------*/
 int RarParse(void)
 {
  /* rotate right with carry */
   return InsertMachineCode(RAR_START);
 }
/*-----------------------------------------------------------------------*/
 int CmaParse(void)
 {
   /* complement accumulator */
  return InsertMachineCode(CMA_START);
 }
/*-----------------------------------------------------------------------*/
 int CmcParse(void)
 {
   /* complement carry */
  return InsertMachineCode(CMC_START);
 }
/*-----------------------------------------------------------------------*/
 int AddressFromTable(int start)
 {
   /* find the label address from symbol table and substitute from table */
   int got;
    if((got=FindInTable(TOKEN()))==NOT_FOUND) return UNDEFINED_LABEL;
    return InsertCodeAnd16Bit(start,SYM_TABLE().entry[got].addr);
 }
/*-----------------------------------------------------------------------*/
 int JmpParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JMP_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JMP_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JnzParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JNZ_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JNZ_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JzParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JZ_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JZ_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JncParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JNC_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JNC_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JcParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JC_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JC_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JpoParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JPO_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JPO_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JpeParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JPE_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JPE_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JpParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JP_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JP_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int JmParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(JM_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(JM_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int PCHLParse(void)
 {
   return InsertCodeAnd16Bit(PCHL_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int RstParse(void)
 {
   if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
   if((addr=StrToNum()) > 7) return LARGE_NUMBER;
   return InsertMachineCode(RST_START + Displacement((int )addr,0));
 }
/*-----------------------------------------------------------------------*/
 int CallParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CALL_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CALL_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CnzParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CNZ_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CNZ_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CzParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CZ_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CZ_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CncParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CNC_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CNC_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CcParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CC_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CC_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CpoParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CPO_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CPO_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CpeParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CPE_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CPE_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CpParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CP_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CP_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int CmParse(void)
 {
   if(Advance(0)!=NUMBER) return AddressFromTable(CM_START);
   if((addr=StrToNum()) > LARGEST_ADDR) return ADDR_TOO_LARGE;
   return InsertCodeAnd16Bit(CM_START,(unsigned)addr);
 }
/*-----------------------------------------------------------------------*/
 int RetParse(void)
 {
   return InsertMachineCode(RET_START);
 }
/*-----------------------------------------------------------------------*/
 int RnzParse(void)
 {
   return InsertMachineCode(RNZ_START);
 }
/*-----------------------------------------------------------------------*/
 int RzParse(void)
 {
   return InsertMachineCode(RZ_START);
 }
/*-----------------------------------------------------------------------*/
 int RncParse(void)
 {
   return InsertMachineCode(RNC_START);
 }
/*-----------------------------------------------------------------------*/
 int RcParse(void)
 {
    return InsertMachineCode(RC_START);
 }
/*-----------------------------------------------------------------------*/
 int RpoParse(void)
 {
    return InsertMachineCode(RPO_START);
 }
/*-----------------------------------------------------------------------*/
 int RpeParse(void)
 {
    return InsertMachineCode(RPE_START);
 }
/*-----------------------------------------------------------------------*/
 int RpParse(void)
 {
    return InsertMachineCode(RP_START);
 }
/*-----------------------------------------------------------------------*/
 int RmParse(void)
 {
    return InsertMachineCode(RM_START);
 }
/*-----------------------------------------------------------------------*/
 int NopParse(void)
 {
   return InsertMachineCode(NOP_START);
 }
/*-----------------------------------------------------------------------*/
 int HltParse(void)
 {
   return InsertMachineCode(HLT_START);
 }
/*-----------------------------------------------------------------------*/
 int DiParse(void)
 {
   return InsertMachineCode(DI_START);
 }
/*-----------------------------------------------------------------------*/
 int EiParse(void)
 {
   return InsertMachineCode(EI_START);
 }
/*-----------------------------------------------------------------------*/
 int RimParse(void)
 {
   return InsertMachineCode(RIM_START);
 }
/*-----------------------------------------------------------------------*/
 int SimParse(void)
 {
   return InsertMachineCode(SIM_START);
 }
/*-----------------------------------------------------------------------*/

#endif