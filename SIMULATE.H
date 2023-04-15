#ifndef _SIMULATE_H_
 #define _SIMULATE_H_

  /*
    the fields of this array
    first field  :-   pointer to function which simulates the function at
                      run time.

    second field :-   equivalent mnemonic string

    third field  :-   pointer to function which converts the machine code
                      to equivalent string
    fourth field :-   length of the instruction
  */

  machine_op_struct mot[MAX_INSTRUCTIONS] =
 /* array of pointers to functions which simulate the 8085 */
  {
     _Nop     ,  "nop"          ,   StrNop     ,  NOP_LEN    ,
     _LxiB    ,  "lxi  b,"      ,   StrLxiB    ,  LXI_LEN    ,
     _StaxB   ,  "stax b"       ,   StrStaxB   ,  STAX_LEN   ,
     _InxB    ,  "inx  b"       ,   StrInxB    ,  INX_LEN    ,
     _InrB    ,  "inr  b"       ,   StrInrB    ,  INR_LEN    ,
     _DcrB    ,  "dcr  b"       ,   StrDcrB    ,  DCR_LEN    ,

     _MviB    ,  "mvi  b,"      ,   StrMviB    ,  MVI_LEN    ,
     _Rlc     ,  "rlc  "        ,   StrRlc     ,  RLC_LEN    ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _DadB    ,  "dad  b"       ,   StrDadB    ,  DAD_LEN    ,
     _LdaxB   ,  "ldax b"       ,   StrLdaxB   ,  LDAX_LEN   ,
     _DcxB    ,  "dcx  b"       ,   StrDcxB    ,  DCX_LEN    ,

     _InrC    ,  "inr  c"       ,   StrInrC    ,  INR_LEN    ,
     _DcrC    ,  "dcr  c"       ,   StrDcrC    ,  DCR_LEN    ,
     _MviC    ,  "mvi  c,"      ,   StrMviC    ,  MVI_LEN    ,
     _Rrc     ,  "rrc"          ,   StrRrc     ,  RRC_LEN    ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _LxiD    ,  "lxi  d,"      ,   StrLxiD    ,  LXI_LEN    ,

     _StaxD   ,  "stax d"       ,   StrStaxD   ,  STAX_LEN   ,
     _InxD    ,  "inx  d"       ,   StrInxD    ,  INX_LEN    ,
     _InrD    ,  "inr  d"       ,   StrInrD    ,  INR_LEN    ,
     _DcrD    ,  "dcr  d"       ,   StrDcrD    ,  DCR_LEN    ,
     _MviD    ,  "mvi  d,"      ,   StrMviD    ,  MVI_LEN    ,
     _Ral     ,  "ral"          ,   StrRal     ,  RAL_LEN    ,

     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _DadD    ,  "dad  d"       ,   StrDadD    ,  DAD_LEN    ,
     _LdaxD   ,  "ldax d"       ,   StrLdaxD   ,  LDAX_LEN   ,
     _DcxD    ,  "dcx  d"       ,   StrDcxD    ,  DCX_LEN    ,
     _InrE    ,  "inr  e"       ,   StrInrE    ,  INR_LEN    ,
     _DcrE    ,  "dcr  e"       ,   StrDcrE    ,  DCR_LEN    ,

     _MviE    ,  "mvi  e,"      ,   StrMviE    ,  MVI_LEN    ,
     _Rar     ,  "rar"          ,   StrRar     ,  RAR_LEN    ,
     _Rim     ,  "rim"          ,   StrRim     ,  RIM_LEN    ,
     _LxiH    ,  "lxi  h,"      ,   StrLxiH    ,  LXI_LEN    ,
     _SHLd    ,  "shld "        ,   StrSHLd    ,  SHLD_LEN   ,
     _InxH    ,  "inx  h"       ,   StrInxH    ,  INX_LEN    ,

     _InrH    ,  "inr  h"       ,   StrInrH    ,  INR_LEN    ,
     _DcrH    ,  "dcr  h"       ,   StrDcrH    ,  DCR_LEN    ,
     _MviH    ,  "mvi  h,"      ,   StrMviH    ,  MVI_LEN    ,
     _Daa     ,  "daa"          ,   StrDaa     ,  DAA_LEN    ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _DadH    ,  "dad  h"       ,   StrDadH    ,  DAD_LEN    ,

     _LHLd    ,  "lhld "        ,   StrLHLd    ,  LHLD_LEN   ,
     _DcxH    ,  "dcx  h"       ,   StrDcxH    ,  DCX_LEN    ,
     _InrL    ,  "inr  l"       ,   StrInrL    ,  INR_LEN    ,
     _DcrL    ,  "dcr  l"       ,   StrDcrL    ,  DCR_LEN    ,
     _MviL    ,  "mvi  l,"      ,   StrMviL    ,  MVI_LEN    ,
     _Cma     ,  "cma"          ,   StrCma     ,  CMA_LEN    ,

     _Sim     ,  "sim"          ,   StrSim     ,  SIM_LEN    ,
     _LxiSP   ,  "lxi  sp,"     ,   StrLxiSP   ,  LXI_LEN    ,
     _StA     ,  "sta  "        ,   StrStA     ,  STA_LEN    ,
     _InxSP   ,  "inx  sp"      ,   StrInxSP   ,  INX_LEN    ,
     _InrM    ,  "inr  m"       ,   StrInrM    ,  INR_LEN    ,
     _DcrM    ,  "dcr  m"       ,   StrDcrM    ,  DCR_LEN    ,

     _MviM    ,  "mvi  m,"      ,   StrMviM    ,  MVI_LEN    ,
     _Stc     ,  "stc"          ,   StrStc     ,  STC_LEN    ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _DadSP   ,  "dad  sp"      ,   StrDadSP   ,  DAD_LEN    ,
     _LdA     ,  "lda  "        ,   StrLdA     ,  LDA_LEN    ,
     _DcxSP   ,  "dcx  sp"      ,   StrDcxSP   ,  DCX_LEN    ,

     _InrA    ,  "inr  a"       ,   StrInrA    ,  INR_LEN    ,
     _DcrA    ,  "dcr  a"       ,   StrDcrA    ,  DCR_LEN    ,
     _MviA    ,  "mvi  a,"      ,   StrMviA    ,  MVI_LEN    ,
     _Cmc     ,  "cmc"          ,   StrCmc     ,  CMC_LEN    ,

     _MovBB   ,  "mov  b,b"     ,   StrMovBB   ,  MOV_LEN    ,
     _MovBC   ,  "mov  b,c"     ,   StrMovBC   ,  MOV_LEN    ,
     _MovBD   ,  "mov  b,d"     ,   StrMovBD   ,  MOV_LEN    ,
     _MovBE   ,  "mov  b,e"     ,   StrMovBE   ,  MOV_LEN    ,
     _MovBH   ,  "mov  b,h"     ,   StrMovBH   ,  MOV_LEN    ,
     _MovBL   ,  "mov  b,l"     ,   StrMovBL   ,  MOV_LEN    ,
     _MovBM   ,  "mov  b,m"     ,   StrMovBM   ,  MOV_LEN    ,
     _MovBA   ,  "mov  b,a"     ,   StrMovBA   ,  MOV_LEN    ,

     _MovCB   ,  "mov  c,b"     ,   StrMovCB   ,  MOV_LEN    ,
     _MovCC   ,  "mov  c,c"     ,   StrMovCC   ,  MOV_LEN    ,
     _MovCD   ,  "mov  c,d"     ,   StrMovCD   ,  MOV_LEN    ,
     _MovCE   ,  "mov  c,e"     ,   StrMovCE   ,  MOV_LEN    ,
     _MovCH   ,  "mov  c,h"     ,   StrMovCH   ,  MOV_LEN    ,
     _MovCL   ,  "mov  c,l"     ,   StrMovCL   ,  MOV_LEN    ,
     _MovCM   ,  "mov  c,m"     ,   StrMovCM   ,  MOV_LEN    ,
     _MovCA   ,  "mov  c,a"     ,   StrMovCA   ,  MOV_LEN    ,

     _MovDB   ,  "mov  d,b"     ,   StrMovDB   ,  MOV_LEN    ,
     _MovDC   ,  "mov  d,c"     ,   StrMovDC   ,  MOV_LEN    ,
     _MovDD   ,  "mov  d,d"     ,   StrMovDD   ,  MOV_LEN    ,
     _MovDE   ,  "mov  d,e"     ,   StrMovDE   ,  MOV_LEN    ,
     _MovDH   ,  "mov  d,h"     ,   StrMovDH   ,  MOV_LEN    ,
     _MovDL   ,  "mov  d,l"     ,   StrMovDL   ,  MOV_LEN    ,
     _MovDM   ,  "mov  d,m"     ,   StrMovDM   ,  MOV_LEN    ,
     _MovDA   ,  "mov  d,a"     ,   StrMovDA   ,  MOV_LEN    ,

     _MovEB   ,  "mov  e,b"     ,   StrMovEB   ,  MOV_LEN    ,
     _MovEC   ,  "mov  e,c"     ,   StrMovEC   ,  MOV_LEN    ,
     _MovED   ,  "mov  e,d"     ,   StrMovED   ,  MOV_LEN    ,
     _MovEE   ,  "mov  e,e"     ,   StrMovEE   ,  MOV_LEN    ,
     _MovEH   ,  "mov  e,h"     ,   StrMovEH   ,  MOV_LEN    ,
     _MovEL   ,  "mov  e,l"     ,   StrMovEL   ,  MOV_LEN    ,
     _MovEM   ,  "mov  e,m"     ,   StrMovEM   ,  MOV_LEN    ,
     _MovEA   ,  "mov  e,a"     ,   StrMovEA   ,  MOV_LEN    ,

     _MovHB   ,  "mov  h,b"     ,   StrMovHB   ,  MOV_LEN    ,
     _MovHC   ,  "mov  h,c"     ,   StrMovHC   ,  MOV_LEN    ,
     _MovHD   ,  "mov  h,d"     ,   StrMovHD   ,  MOV_LEN    ,
     _MovHE   ,  "mov  h,e"     ,   StrMovHE   ,  MOV_LEN    ,
     _MovHH   ,  "mov  h,h"     ,   StrMovHH   ,  MOV_LEN    ,
     _MovHL   ,  "mov  h,l"     ,   StrMovHL   ,  MOV_LEN    ,
     _MovHM   ,  "mov  h,m"     ,   StrMovHM   ,  MOV_LEN    ,
     _MovHA   ,  "mov  h,a"     ,   StrMovHA   ,  MOV_LEN    ,


     _MovLB   ,  "mov  l,b"     ,   StrMovLB   ,  MOV_LEN    ,
     _MovLC   ,  "mov  l,c"     ,   StrMovLC   ,  MOV_LEN    ,
     _MovLD   ,  "mov  l,d"     ,   StrMovLD   ,  MOV_LEN    ,
     _MovLE   ,  "mov  l,e"     ,   StrMovLE   ,  MOV_LEN    ,
     _MovLH   ,  "mov  l,h"     ,   StrMovLH   ,  MOV_LEN    ,
     _MovLL   ,  "mov  l,l"     ,   StrMovLL   ,  MOV_LEN    ,
     _MovLM   ,  "mov  l,m"     ,   StrMovLM   ,  MOV_LEN    ,
     _MovLA   ,  "mov  l,a"     ,   StrMovLA   ,  MOV_LEN    ,


     _MovMB   ,  "mov  m,b"     ,   StrMovMB   ,  MOV_LEN    ,
     _MovMC   ,  "mov  m,c"     ,   StrMovMC   ,  MOV_LEN    ,
     _MovMD   ,  "mov  m,d"     ,   StrMovMD   ,  MOV_LEN    ,
     _MovME   ,  "mov  m,e"     ,   StrMovME   ,  MOV_LEN    ,
     _MovMH   ,  "mov  m,h"     ,   StrMovMH   ,  MOV_LEN    ,
     _MovML   ,  "mov  m,l"     ,   StrMovML   ,  MOV_LEN    ,

     _Hlt     ,  "hlt"          ,   StrHlt     ,  HLT_LEN    ,
     _MovMA   ,  "mov  m,a"     ,   StrMovMA   ,  MOV_LEN    ,


     _MovAB   ,  "mov  a,b"     ,   StrMovAB   ,  MOV_LEN    ,
     _MovAC   ,  "mov  a,c"     ,   StrMovAC   ,  MOV_LEN    ,
     _MovAD   ,  "mov  a,d"     ,   StrMovAD   ,  MOV_LEN    ,
     _MovAE   ,  "mov  a,e"     ,   StrMovAE   ,  MOV_LEN    ,
     _MovAH   ,  "mov  a,h"     ,   StrMovAH   ,  MOV_LEN    ,
     _MovAL   ,  "mov  a,l"     ,   StrMovAL   ,  MOV_LEN    ,
     _MovAM   ,  "mov  a,m"     ,   StrMovAM   ,  MOV_LEN    ,
     _MovAA   ,  "mov  a,a"     ,   StrMovAA   ,  MOV_LEN    ,


     _AddB    ,  "add  b"     ,   StrAddB    ,  ADD_LEN    ,
     _AddC    ,  "add  c"     ,   StrAddC    ,  ADD_LEN    ,
     _AddD    ,  "add  d"     ,   StrAddD    ,  ADD_LEN    ,
     _AddE    ,  "add  e"     ,   StrAddE    ,  ADD_LEN    ,
     _AddH    ,  "add  h"     ,   StrAddH    ,  ADD_LEN    ,
     _AddL    ,  "add  l"     ,   StrAddL    ,  ADD_LEN    ,
     _AddM    ,  "add  m"     ,   StrAddM    ,  ADD_LEN    ,
     _AddA    ,  "add  a"     ,   StrAddA    ,  ADD_LEN    ,


     _AdcB    ,  "adc  b"     ,   StrAdcB    ,  ADD_LEN    ,
     _AdcC    ,  "adc  c"     ,   StrAdcC    ,  ADD_LEN    ,
     _AdcD    ,  "adc  d"     ,   StrAdcD    ,  ADD_LEN    ,
     _AdcE    ,  "adc  e"     ,   StrAdcE    ,  ADD_LEN    ,
     _AdcH    ,  "adc  h"     ,   StrAdcH    ,  ADD_LEN    ,
     _AdcL    ,  "adc  l"     ,   StrAdcL    ,  ADD_LEN    ,
     _AdcM    ,  "adc  m"     ,   StrAdcM    ,  ADD_LEN    ,
     _AdcA    ,  "adc  a"     ,   StrAdcA    ,  ADD_LEN    ,


     _SubB    ,  "sub  b"     ,   StrSubB    ,  SUB_LEN    ,
     _SubC    ,  "sub  c"     ,   StrSubC    ,  SUB_LEN    ,
     _SubD    ,  "sub  d"     ,   StrSubD    ,  SUB_LEN    ,
     _SubE    ,  "sub  e"     ,   StrSubE    ,  SUB_LEN    ,
     _SubH    ,  "sub  h"     ,   StrSubH    ,  SUB_LEN    ,
     _SubL    ,  "sub  l"     ,   StrSubL    ,  SUB_LEN    ,
     _SubM    ,  "sub  m"     ,   StrSubM    ,  SUB_LEN    ,
     _SubA    ,  "sub  a"     ,   StrSubA    ,  SUB_LEN    ,


     _SbbB    ,  "sbb  b"     ,   StrSbbB    ,  SUB_LEN    ,
     _SbbC    ,  "sbb  c"     ,   StrSbbC    ,  SUB_LEN    ,
     _SbbD    ,  "sbb  d"     ,   StrSbbD    ,  SUB_LEN    ,
     _SbbE    ,  "sbb  e"     ,   StrSbbE    ,  SUB_LEN    ,
     _SbbH    ,  "sbb  h"     ,   StrSbbH    ,  SUB_LEN    ,
     _SbbL    ,  "sbb  l"     ,   StrSbbL    ,  SUB_LEN    ,
     _SbbM    ,  "sbb  m"     ,   StrSbbM    ,  SUB_LEN    ,
     _SbbA    ,  "sbb  a"     ,   StrSbbA    ,  SUB_LEN    ,


     _AnaB    ,  "ana  b"     ,   StrAnaB    ,  ANA_LEN    ,
     _AnaC    ,  "ana  c"     ,   StrAnaC    ,  ANA_LEN    ,
     _AnaD    ,  "ana  d"     ,   StrAnaD    ,  ANA_LEN    ,
     _AnaE    ,  "ana  e"     ,   StrAnaE    ,  ANA_LEN    ,
     _AnaH    ,  "ana  h"     ,   StrAnaH    ,  ANA_LEN    ,
     _AnaL    ,  "ana  l"     ,   StrAnaL    ,  ANA_LEN    ,
     _AnaM    ,  "ana  m"     ,   StrAnaM    ,  ANA_LEN    ,
     _AnaA    ,  "ana  a"     ,   StrAnaA    ,  ANA_LEN    ,


     _XraB    ,  "xra  b"     ,   StrXraB    ,  XRA_LEN    ,
     _XraC    ,  "xra  c"     ,   StrXraC    ,  XRA_LEN    ,
     _XraD    ,  "xra  d"     ,   StrXraD    ,  XRA_LEN    ,
     _XraE    ,  "xra  e"     ,   StrXraE    ,  XRA_LEN    ,
     _XraH    ,  "xra  h"     ,   StrXraH    ,  XRA_LEN    ,
     _XraL    ,  "xra  l"     ,   StrXraL    ,  XRA_LEN    ,
     _XraM    ,  "xra  m"     ,   StrXraM    ,  XRA_LEN    ,
     _XraA    ,  "xra  a"     ,   StrXraA    ,  XRA_LEN    ,


     _OraB    ,  "ora  b"     ,   StrOraB    ,  ORA_LEN    ,
     _OraC    ,  "ora  c"     ,   StrOraC    ,  ORA_LEN    ,
     _OraD    ,  "ora  d"     ,   StrOraD    ,  ORA_LEN    ,
     _OraE    ,  "ora  e"     ,   StrOraE    ,  ORA_LEN    ,
     _OraH    ,  "ora  h"     ,   StrOraH    ,  ORA_LEN    ,
     _OraL    ,  "ora  l"     ,   StrOraL    ,  ORA_LEN    ,
     _OraM    ,  "ora  m"     ,   StrOraM    ,  ORA_LEN    ,
     _OraA    ,  "ora  a"     ,   StrOraA    ,  ORA_LEN    ,


     _CmpB    ,  "cmp  b"     ,   StrCmpB    ,  CMP_LEN    ,
     _CmpC    ,  "cmp  c"     ,   StrCmpC    ,  CMP_LEN    ,
     _CmpD    ,  "cmp  d"     ,   StrCmpD    ,  CMP_LEN    ,
     _CmpE    ,  "cmp  e"     ,   StrCmpE    ,  CMP_LEN    ,
     _CmpH    ,  "cmp  h"     ,   StrCmpH    ,  CMP_LEN    ,
     _CmpL    ,  "cmp  l"     ,   StrCmpL    ,  CMP_LEN    ,
     _CmpM    ,  "cmp  m"     ,   StrCmpM    ,  CMP_LEN    ,
     _CmpA    ,  "cmp  a"     ,   StrCmpA    ,  CMP_LEN    ,


     _RnZ     ,  "rnz"          ,   StrRnZ     ,  RNZ_LEN    ,
     _PopB    ,  "pop  b"       ,   StrPopB    ,  POP_LEN    ,
     _JnZ     ,  "jnz  "        ,   StrJnZ     ,  JNZ_LEN    ,
     _Jmp     ,  "jmp  "        ,   StrJmp     ,  JMP_LEN    ,
     _CnZ     ,  "cnz  "        ,   StrCnZ     ,  CNZ_LEN    ,
     _PushB   ,  "push b"       ,   StrPushB   ,  PUSH_LEN   ,

     _Adi     ,  "adi  a,"      ,   StrAdi     ,  ADI_LEN    ,
     _Rst0    ,  "rst  0"       ,   StrRst0    ,  RST_LEN    ,
     _RZ      ,  "rz"           ,   StrRZ      ,  RZ_LEN     ,
     _Ret     ,  "ret"          ,   StrRet     ,  RET_LEN    ,
     _JZ      ,  "jz "          ,   StrJZ      ,  JZ_LEN     ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,

     _CZ      ,  "cz   "        ,   StrCZ      ,  CZ_LEN     ,
     _Call    ,  "call "        ,   StrCall    ,  CALL_LEN   ,
     _Aci     ,  "aci  a,"      ,   StrAci     ,  ACI_LEN    ,
     _Rst1    ,  "rst  1"       ,   StrRst1    ,  RST_LEN    ,
     _RnC     ,  "rnc"          ,   StrRnC     ,  RNC_LEN    ,
     _PopD    ,  "pop  d"       ,   StrPopD    ,  POP_LEN    ,

     _JnC     ,  "jnc  "        ,   StrJnC     ,  JNC_LEN    ,
     _Out     ,  "out  "        ,   StrOut     ,  OUT_LEN    ,
     _CnC     ,  "cnc  "        ,   StrCnC     ,  CNC_LEN    ,
     _PushD   ,  "push d"       ,   StrPushD   ,  PUSH_LEN   ,
     _Sui     ,  "sui  a,"      ,   StrSui     ,  SUI_LEN    ,
     _Rst2    ,  "rst  2"       ,   StrRst2    ,  RST_LEN    ,

     _RC      ,  "rc"           ,   StrRC      ,  RC_LEN     ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _Jc      ,  "jc   "        ,   StrJc      ,  JC_LEN     ,
     _In      ,  "in   "        ,   StrIn      ,  IN_LEN     ,
     _CC      ,  "cc   "        ,   StrCC      ,  CC_LEN     ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,

     _Sbi     ,  "sbi  a,"      ,   StrSbi     ,  SBI_LEN    ,
     _Rst3    ,  "rst  3"       ,   StrRst3    ,  RST_LEN    ,
     _Rpo     ,  "rpo"          ,   StrRpo     ,  RPO_LEN    ,
     _PopH    ,  "pop  h"       ,   StrPopH    ,  POP_LEN    ,
     _Jpo     ,  "jpo  "        ,   StrJpo     ,  JPO_LEN    ,
     _XtHL    ,  "xthl"         ,   StrXtHL    ,  XTHL_LEN   ,

     _Cpo     ,  "cpo  "        ,   StrCpo     ,  CPO_LEN    ,
     _PushH   ,  "push h"       ,   StrPushH   ,  PUSH_LEN   ,
     _Ani     ,  "ani  a,"      ,   StrAni     ,  ANI_LEN    ,
     _Rst4    ,  "rst  4"       ,   StrRst4    ,  RST_LEN    ,
     _Rpe     ,  "rpe"          ,   StrRpe     ,  RPE_LEN    ,
     _PCHL    ,  "pchl"         ,   StrPCHL    ,  PCHL_LEN   ,

     _Jpe     ,  "jpe "         ,   StrJpe     ,  JPE_LEN    ,
     _Xchg    ,  "xchg"         ,   StrXchg    ,  XCHG_LEN   ,
     _Cpe     ,  "cpe  "        ,   StrCpe     ,  CPE_LEN    ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _Xri     ,  "xri  a,"      ,   StrXri     ,  XRI_LEN    ,
     _Rst5    ,  "rst  5"       ,   StrRst5    ,  RST_LEN    ,

     _Rp      ,  "rp "          ,   StrRp      ,  RP_LEN     ,
     _PopPSW  ,  "pop psw"      ,   StrPopPSW  ,  POP_LEN    ,
     _Jp      ,  "jp "          ,   StrJp      ,  JP_LEN     ,
     _Di      ,  "di"           ,   StrDi      ,  DI_LEN     ,
     _Cp      ,  "cp   "        ,   StrCp      ,  CP_LEN     ,
     _PushPSW ,  "push psw "    ,   StrPushPSW ,  PUSH_LEN   ,

     _Ori     ,  "ori  a,"      ,   StrOri     ,  ORI_LEN    ,
     _Rst6    ,  "rst  6"       ,   StrRst6    ,  RST_LEN    ,
     _Rm      ,  "rm "          ,   StrRm      ,  RM_LEN     ,
     _SPHL    ,  "sphl"         ,   StrSPHL    ,  SPHL_LEN   ,
     _Jm      ,  "jm "          ,   StrJm      ,  JM_LEN     ,
     _Ei      ,  "ei"           ,   StrEi      ,  EI_LEN     ,

     _Cm      ,  "cm  "         ,   StrCm      ,  CM_LEN     ,
     _Invalid ,  "invalid"      ,   StrInvalid ,  1          ,
     _Cpi     ,  "cpi  "        ,   StrCpi     ,  CPI_LEN    ,
     _Rst7    ,  "rst  7"       ,   StrRst7    ,  RST_LEN

  };



#endif