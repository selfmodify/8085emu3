#ifndef _CODE_TO_MNEMONIC_H_
 #define _CODE_TO_MNEMONIC_H_

 /* functions which return equivalent mnemonic's i.e., strings
    for a opcode.
    eg 1:- for the opcode 0 the function 'StrNop' will
    store the string "nop" in the parameter string 's'
    eg 2 :- for the opcode 40 the 'MovBB' will
    store the string "mov b,b" in the parameter string 's'
 */
/* --------------------------------------------------------------------- */
 char * AsciiToString(unsigned x,char *s)
 {
  static char num[80];
  /*   ultoa(x,num,DEFAULT_BASE); */
    if(x>MAX_INT) sprintf(num,"%04x",x);
     else sprintf(num,"%02x",x);
    strcat(s,num);
    return s;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrNop(unsigned _addr ,int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return NOP_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrLxiB(unsigned _addr ,int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrStaxB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return STAX_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrInxB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INX_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrInrB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrDcrB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrMviB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrRlc(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RLC_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrInvalid(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return 1;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrDadB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DAD_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrLdaxB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return LDAX_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrDcxB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCX_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrInrC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrDcrC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrMviC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrRrc(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RRC_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrLxiD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/* --------------------------------------------------------------------- */
 #pragma argsused
 int StrStaxD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return STAX_LEN;
 }
/*-----------------------------------------------------------------------*/
 #pragma argsused
 int StrInxD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INX_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInrD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrMviD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrRal(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RAL_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDadD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DAD_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrLdaxD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return LDAX_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcxD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCX_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInrE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrMviE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrRar(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RAR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrRim(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RIM_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrLxiH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrSHLd(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return SHLD_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInxH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INX_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInrH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrMviH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDaa(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DAA_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDadH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DAD_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrLHLd(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LHLD_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcxH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCX_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInrL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrMviL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrCma(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMA_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrSim(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SIM_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrLxiSP(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrStA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/*----------------------------------------------------------------------*/
 #pragma argsused
 int StrInxSP(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INX_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrInrM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMviM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrStc(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return STC_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrDadSP(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DAD_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrLdA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return LXI_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrDcxSP(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCX_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrInrA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return INR_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrDcrA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DCR_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMviA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return MVI_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmc(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMC_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovBA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovCA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovDA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovED(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }
/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovEA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovHA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovLA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovMB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovMC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovMD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovME(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovMH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovML(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrHlt(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovMA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrMovAA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return MOV_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAddA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADD_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdcA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ADC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSubA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SUB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbbA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SBB_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ANA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAnaA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XRA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXraA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return ORA_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOraA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpE(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpM(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCmpA(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return CMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRnZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RNZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPopB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return POP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJnZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JNZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJmp(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JMP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCnZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CNZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPushB(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PUSH_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAdi(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return ADI_LEN;
 }


/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst0(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRet(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RET_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCZ(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CZ_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCall(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CALL_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAci(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return ACI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst1(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRnC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RNC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPopD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return POP_LEN;
 }


/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJnC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JNC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOut(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return OUT_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCnC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CNC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPushD(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PUSH_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSui(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return SUI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst2(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJc(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrIn(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return IN_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCC(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CC_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSbi(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return SBI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst3(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRpo(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PCHL_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPopH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return POP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJpo(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JPO_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXtHL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XTHL_LEN;
 }


/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCpo(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CPO_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPushH(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PUSH_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrAni(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return ANI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst4(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRpe(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RPE_LEN;
 }


/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPCHL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PCHL_LEN;
 }


/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJpe(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JPE_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXchg(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return XCHG_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCpe(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CPE_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrXri(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return XRI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst5(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRp(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPopPSW(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PUSH_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJp(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrDi(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return DI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCp(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CP_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrPushPSW(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return PUSH_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrOri(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return ORI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst6(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRm(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RM_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrSPHL(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return SPHL_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrJm(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return JM_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrEi(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return EI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCm(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemWord(_addr+1),s);
   return CM_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrCpi(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   AsciiToString(GetMemByte(_addr+1),s);
   return CPI_LEN;
 }

/*---------------------------------------------------------------------*/
 #pragma argsused
 int StrRst7(unsigned _addr, int pos ,char *s)
 {
   strcpy(s,FORMAT(MAC_OP_TABLE[pos].name));
   return RST_LEN;
 }

#endif