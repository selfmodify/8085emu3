#ifndef _MNEMONIC_H_
 #define _MNEMONIC_H_

/*様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様*/
  /* contains the mnemonic for the different groups of instructions */

  /*
   fields of this array

   first field   :-  whenever a token is obtained for parsing
                     it is matched with this field to see if
                     the string is a mnemonic.

   second field  :-  the length of the instruction

   third         :-  the function which parses the instruction
                     eg:- MovParse will parse the mnemonic for "mov"
                     instruction, by checking to see if the operands
                     to it are valid (i.e, in this case the operands
                     should be either registers, a register and a
                     memory location but not two memory locations)
  */

  instruction_struct   mnemonic[] =
  {
       "MOV"    , MOV_LEN  ,   MovParse  ,
       "MVI"    , MVI_LEN  ,   MviParse  ,
       "LDAX"   , LDAX_LEN ,   LdaxParse ,
       "LHLD"   , LHLD_LEN ,   LHLdParse ,
       "STAX"   , STAX_LEN ,   StaxParse ,
       "LDA"    , LDA_LEN  ,   LdAParse  ,
       "LXI"    , LXI_LEN  ,   LxiParse  ,
       "SHLD"   , SHLD_LEN ,   SHLdParse ,
       "STA"    , STA_LEN  ,   StAParse  ,

       "SPHL"   , SPHL_LEN ,   SPHLParse ,
       "XTHL"   , XTHL_LEN ,   XtHLParse ,
       "XCHG"   , XCHG_LEN ,   XchgParse ,
       "OUT"    , OUT_LEN  ,   OutParse  ,
       "IN"     , IN_LEN   ,   InParse   ,
       "PUSH"   , PUSH_LEN ,   PushParse ,
       "POP"    , POP_LEN  ,   PopParse  ,

       "ADD"    , ADD_LEN  ,    AddParse ,
       "ADC"    , ADC_LEN  ,    AdcParse ,
       "ADI"    , ADI_LEN  ,    AdiParse ,
       "ACI"    , ACI_LEN  ,    AciParse ,
       "SUB"    , SUB_LEN  ,    SubParse ,
       "SBB"    , SBB_LEN  ,    SbbParse ,
       "SUI"    , SUI_LEN  ,    SuiParse ,
       "SBI"    , SBI_LEN  ,    SbiParse ,
       "DAD"    , DAD_LEN  ,    DadParse ,
       "DAA"    , DAA_LEN  ,    DaaParse ,
       "INR"    , INR_LEN  ,    InrParse ,
       "INX"    , INX_LEN  ,    InxParse ,
       "DCR"    , DCR_LEN  ,    DcrParse ,
       "DCX"    , DCX_LEN  ,    DcxParse ,

       "STC"    , STC_LEN  ,    StCParse ,
       "ANA"    , ANA_LEN  ,    AnaParse ,
       "ANI"    , ANI_LEN  ,    AniParse ,
       "XRA"    , XRA_LEN  ,    XraParse ,
       "XRI"    , XRI_LEN  ,    XriParse ,
       "ORA"    , ORA_LEN  ,    OraParse ,
       "ORI"    , ORI_LEN  ,    OriParse ,
       "CMP"    , CMP_LEN  ,    CmpParse ,
       "CPI"    , CPI_LEN  ,    CpiParse ,
       "RLC"    , RLC_LEN  ,    RlcParse ,
       "RRC"    , RRC_LEN  ,    RrcParse ,
       "RAL"    , RAL_LEN  ,    RalParse ,
       "RAR"    , RAR_LEN  ,    RarParse ,
       "CMA"    , CMA_LEN  ,    CmaParse ,
       "CMC"    , CMC_LEN  ,    CmcParse ,


       "JMP"    , JMP_LEN  ,    JmpParse ,
       "JZ"     , JZ_LEN   ,    JzParse  ,
       "JNZ"    , JNZ_LEN  ,    JnzParse ,
       "JNC"    , JNC_LEN  ,    JncParse ,
       "JC"     , JC_LEN   ,    JcParse  ,
       "JPO"    , JPO_LEN  ,    JpoParse ,
       "JPE"    , JPE_LEN  ,    JpeParse ,
       "JP"     , JP_LEN   ,    JpParse  ,
       "JM"     , JM_LEN   ,    JmParse  ,
       "PCHL"   , PCHL_LEN ,    PCHLParse,
       "RST"    , RST_LEN  ,    RstParse ,
       "CALL"   , CALL_LEN ,    CallParse,
       "CZ"     , CZ_LEN   ,    CzParse  ,
       "CNZ"    , CNZ_LEN  ,    CnzParse ,
       "CNC"    , CNC_LEN  ,    CncParse ,
       "CC"     , CC_LEN   ,    CcParse  ,
       "CPO"    , CPO_LEN  ,    CpoParse ,
       "CPE"    , CPE_LEN  ,    CpeParse ,
       "CP"     , CP_LEN   ,    CpParse  ,
       "CM"     , CM_LEN   ,    CmParse  ,
       "RET"    , RET_LEN  ,    RetParse ,
       "RZ"     , RZ_LEN   ,    RzParse  ,
       "RNZ"    , RNZ_LEN  ,    RnzParse ,
       "RNC"    , RNC_LEN  ,    RncParse ,
       "RC"     , RC_LEN   ,    RcParse  ,
       "RPO"    , RPO_LEN  ,    RpoParse ,
       "RPE"    , RPE_LEN  ,    RpeParse ,
       "RP"     , RP_LEN   ,    RpParse  ,
       "NOP"    , NOP_LEN  ,    NopParse ,
       "RM"     , RM_LEN   ,    RmParse  ,

       "HLT"    , HLT_LEN  ,    HltParse ,
       "DI"     , DI_LEN   ,    DiParse  ,
       "EI"     , EI_LEN   ,    EiParse  ,
       "RIM"    , RIM_LEN  ,    RimParse ,
       "SIM"    , SIM_LEN  ,    SimParse ,

       NULL , 0 , NULL
  };


#endif