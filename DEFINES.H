#ifndef _DEFINE_H_
 #define _DEFINE_H_

 /* The various global 'defines needed for the program */

 #define   _MU                   230  /* the 'æ' ASCII character */
 #define   PLUS                  1    /* used for setting      - */
 #define   MINUS                 0    /* 'auxillary carry'       */

 #define    MAX_ERRORS           25
 /* the maximum number of errors that is reported by the machine */

 #define    _B                    0
 #define    _C                    1
 #define    _D                    2
 #define    _E                    3
 #define    _H                    4
 #define    _L                    5
 #define    _M                    6
 #define    _A                    7
 #define    _SP                   8
 #define    _FLAGS                9
 #define    _TEMP                10
 #define    _PSW		 11

 #define    ORG_DIRECTIVE         1
 #define    KICKOFF_DIRECTIVE     2
 #define    SETBYTE_DIRECTIVE     3
 #define    SETWORD_DIRECTIVE     4

 #define    DEFAULT_BASE         16
 #define    DEFAULT_IP           0x100
 #define    DEFAULT_KICKOFF      0x100
 /* if no format is specified, the numbers are assumed to have a base of
    16
 */

 #define    RST_0_ADDR             0x00
 #define    RST_1_ADDR             0x08
 #define    RST_2_ADDR             0x10
 #define    RST_3_ADDR             0x18
 #define    RST_4_ADDR             0x20
 #define    RST_5_ADDR             0x28
 #define    RST_6_ADDR             0x30
 #define    RST_7_ADDR             0x38
 #define    TRAP_ADDR              0x24
 #define    RST_5_5_ADDR           0x2c
 #define    RST_6_5_ADDR           0x34
 #define    RST_7_5_ADDR           0x3c

 #define    TRAP_INTR              0x00
 #define    RST_5_5_INTR           0x01
 #define    RST_6_5_INTR           0x02
 #define    RST_7_5_INTR           0x03

 #define    CORRECT_DIRECTIVE      500
 #define    COMMENTS               501
 #define    VALID_INSTRUCTION      502
 /* this value should be larger than values op-code, else it will be
    confused as the machine code */

/*----------------------------------------------------------------------*/

 #define    SUCCESS                271
 #define    EOI                    290       /* end of input */
 #define    EOLN                   295
 #define    COMMENT                296       /* got a comment */
 #define    IDENTIFIER             310
 #define    NUMBER                 311
 #define    COMMA                  312
 #define    KEYWORD                313
 #define    REGISTER               314
 #define    SEMI                   ';'
 #define    COLON                  ':'
 #define    FOUND                  400
 /* symbol was found in symbol table */
 #define    SYMBOL_STORED          402   /* the symbol was stored */
 #define    LABEL                  403

 #define    TOKEN_SIZE              81
 #define    LINE_LENGTH             256        /* length of input line */
 #define    MAIN_MEMORY             (16*1024l)  /* 16 K of main memory   */

 #define    MAX_BREAK_POINTS        255
 /* maximum number of break points that can be specified */
 #define    LARGEST_INT             255
 #define    MAX_INT                 LARGEST_INT
 #define    DOUBLE_INT              65535l     /* 16 bit integer value */
 #define    LARGEST_ORG             MAIN_MEMORY
 #define    LARGEST_ADDR	    MAIN_MEMORY
 /* largest memory address  */

/*========================================================================*/
/*========================================================================*/
  /* the following '#defines' define the starting machine code for each
     group of instruction
     eg:- MOV instructions start from hex 40 and Add instructions from
	  hex 80
  */

  #define   MOV_START               0x40
  #define   MVI_START               0x06
  #define   LDAX_START              0x0A
  #define   LHLD_START              0x2A
  #define   LDA_START               0x3A
  #define   STAX_START              0x02
  #define   SHLD_START              0x22
  #define   STA_START               0x32
  #define   LXI_START               0x01
  #define   SPHL_START              0xF9
  #define   XTHL_START              0xE3
  #define   XCHG_START              0xEB
  #define   OUT_START               0xD3
  #define   IN_START                0xDB
  #define   PUSH_START              0xC5
  #define   POP_START               0xC1

  #define   ADD_START               0x80
  #define   ADC_START               0x88
  #define   ADI_START               0xC6
  #define   ACI_START               0xCE
  #define   SUB_START               0x90
  #define   SBB_START               0x98
  #define   SUI_START               0xD6
  #define   SBI_START               0xDE
  #define   DAD_START               0x09
  #define   DAA_START               0x27
  #define   INR_START               0x04
  #define   INX_START               0x03
  #define   DCR_START               0x05
  #define   DCX_START               0x0B

  #define   STC_START               0x37
  #define   ANA_START               0xA0
  #define   ANI_START               0xE6
  #define   XRA_START               0xA8
  #define   XRI_START               0xEE
  #define   ORA_START               0xB0
  #define   ORI_START               0xF6
  #define   CMP_START               0xB8
  #define   CPI_START               0xFE
  #define   RLC_START               0x07
  #define   RRC_START               0x0F
  #define   RAL_START               0x17
  #define   RAR_START               0x1F
  #define   CMA_START               0x2F
  #define   CMC_START               0x3F

  #define   JMP_START               0xC3
  #define   JNZ_START               0xC2
  #define   JZ_START                0xCA
  #define   JNC_START               0xD2
  #define   JC_START                0xDA
  #define   JPO_START               0xE2
  #define   JPE_START               0xEA
  #define   JP_START                0xF2
  #define   JM_START                0xFA
  #define   PCHL_START              0xE9
  #define   RST_START               0xC7
  #define   CALL_START              0xCD

  #define   CNZ_START               0xC4
  #define   CZ_START                0xCC
  #define   CNC_START               0xD4
  #define   CC_START                0xDC
  #define   CPO_START               0xE4
  #define   CPE_START               0xEC
  #define   CP_START                0xF4
  #define   CM_START                0xFC

  #define   RET_START               0xC9
  #define   RNZ_START               0xC0
  #define   RZ_START                0xC8
  #define   RNC_START               0xD0
  #define   RC_START                0xD8
  #define   RPO_START               0xE0
  #define   RPE_START               0xE8
  #define   RP_START                0xF0
  #define   RM_START                0xF8

  #define   NOP_START               0x00
  #define   HLT_START               0x76
  #define   DI_START                0xF3
  #define   EI_START                0xFB
  #define   RIM_START               0x20
  #define   SIM_START               0x30

/*========================================================================*/
/*========================================================================*/



  #define   MOV_LEN               01
  #define   MVI_LEN               02
  #define   LDAX_LEN              01
  #define   LHLD_LEN              03
  #define   LDA_LEN               03
  #define   STAX_LEN              01
  #define   SHLD_LEN              03
  #define   STA_LEN               03
  #define   LXI_LEN               03
  #define   SPHL_LEN              01
  #define   XTHL_LEN              01
  #define   XCHG_LEN              01
  #define   OUT_LEN               02
  #define   IN_LEN                02
  #define   PUSH_LEN              01
  #define   POP_LEN               01

  #define   ADD_LEN               01
  #define   ADC_LEN               01
  #define   ADI_LEN               02
  #define   ACI_LEN               02
  #define   SUB_LEN               01
  #define   SBB_LEN               01
  #define   SUI_LEN               02
  #define   SBI_LEN               02
  #define   DAD_LEN               01
  #define   DAA_LEN               01
  #define   INR_LEN               01
  #define   INX_LEN               01
  #define   DCR_LEN               01
  #define   DCX_LEN               01

  #define   STC_LEN               01
  #define   ANA_LEN               01
  #define   ANI_LEN               02
  #define   XRA_LEN               01
  #define   XRI_LEN               02
  #define   ORA_LEN               01
  #define   ORI_LEN               02
  #define   CMP_LEN               01
  #define   CPI_LEN               02
  #define   RLC_LEN               01
  #define   RRC_LEN               01
  #define   RAL_LEN               01
  #define   RAR_LEN               01
  #define   CMA_LEN               01
  #define   CMC_LEN               01

  #define   JMP_LEN               03
  #define   JNZ_LEN               03
  #define   JZ_LEN                03
  #define   JNC_LEN               03
  #define   JC_LEN                03
  #define   JPO_LEN               03
  #define   JPE_LEN               03
  #define   JP_LEN                03
  #define   JM_LEN                03
  #define   PCHL_LEN              01
  #define   RST_LEN               01
  #define   CALL_LEN              03

  #define   CNZ_LEN               03
  #define   CZ_LEN                03
  #define   CNC_LEN               03
  #define   CC_LEN                03
  #define   CPO_LEN               03
  #define   CPE_LEN               03
  #define   CP_LEN                03
  #define   CM_LEN                03

  #define   RET_LEN               01
  #define   RNZ_LEN               01
  #define   RZ_LEN                01
  #define   RNC_LEN               01
  #define   RC_LEN                01
  #define   RPO_LEN               01
  #define   RPE_LEN               01
  #define   RP_LEN                01
  #define   RM_LEN                01

  #define   NOP_LEN               01
  #define   HLT_LEN               01
  #define   DI_LEN                01
  #define   EI_LEN                01
  #define   RIM_LEN               01
  #define   SIM_LEN               01

/*========================================================================*/
  #define   DATA_TRANSFER           01
  #define   ARITHMETIC              02
  #define   LOGICAL                 03
  #define   BRANCHING               04
  #define   CONTROL                 05
  #define   FUNCTIONAL_GROUPS       05 /* number of functional groups */

/*========================================================================*/
  #define  MAX_INSTRUCTIONS    256
  /* maximum number of instructions */
  #define  INSTRUCTION_LENGTH  10
  /*length for mnemonics for instructions*/
  #define  LABEL_LEN          33
  /* maximum length of each lable */
  #define  TABLE_LENGTH       256
  /* maximum number of entries in symbol table */
/*========================================================================*/

 #define   SIGN                128
 #define   ZERO                64
 #define   AUX_CARRY           16
 #define   PARITY              4
 #define   CARRY               1

 #define   SYSTEM_CALL         0x0005
 #define   MAX_ADDR_FIELDS     4 /* no. of address fields in LED display */
 #define   MAX_DATA_FIELDS     2 /* no. of data fields in LED display */
 #define   MAX_STATUS_FIELDS   2 /* no. of status fields in LED display */
 #define   TOTAL_LEDS          (4+2+2)
 #define   PATCH               3  /* displacement between each LED set */


 /* ------------------------------------------------------------------ */
 /*  7 segment LED display values

        a
       __
     f|__| b      and the middle one is called 'g'
     e|__| c
        d
 */

 /* ********************************************************************
 *
 *    Significance of bits of  Led display
 *
 *   ÚÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄ¿
 *   ³   ³ g ³ f ³ e ³ d ³ c ³ b ³ a ³
 *   ÀÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÙ
 *
 *
 *
 * ******************************************************************* */

/*----------------------------------------------------------------------*/

 #define  LED_A         1
 #define  LED_B         2
 #define  LED_C         4
 #define  LED_D         8
 #define  LED_E        16
 #define  LED_F        32
 #define  LED_G        64
 #define  LED_DOT     256
 #define  LED_LEN      5  /* length in bytes used to display one LED */


 #define  _LED_1           6  /* 7 segment code equivalent for displaying '1' */
 #define  _LED_2           91
 #define  _LED_3           79
 #define  _LED_4           102
 #define  _LED_5           109
 #define  _LED_6           125
 #define  _LED_7           7
 #define  _LED_8           127
 #define  _LED_9           111
 #define  _LED_0           63
 #define  _LED_A           119
 #define  _LED_B           124
 #define  _LED_C           57
 #define  _LED_D           94
 #define  _LED_E           121
 #define  _LED_F           113

 #define  _LED_BLANK       128
 #define  _LED_DOT         129
 #define  _LED_HYPHEN      130
 #define  _LED_G           131
 #define  _LED_H           132
 #define  _LED_L           133
 #define  _LED_t           134
 #define  _LED_N           135
 #define  _LED_n           136
 #define  _LED_o           137
 #define  _LED_P           138
 #define  _LED_R           139
 #define  _LED_r           140
 #define  _LED_U           141
 #define  _LED_Y           142
 #define  _LED_Mu          143
 #define  _LED_u           144
 #define  _LED_l           145
 #define  _LED_x           146

 #define  CODE_BOX_TAB        0    /* When 'TAB' is pressed you move from  */
 #define  REG_BOX_TAB         1    /* one window to another.  These defines*/
 #define  MEM_DUMP_TAB        2    /* the sequence in which the change     */
 #define  FLAG_BOX_TAB        3    /* occurs                               */


 /* ********************************************************************
 *
 *    Significance of bits of  Led display
 *      7      6      5      4      3      2      1      0
 *   ÚÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄ¿
 *   ³ SOD  ³ SDE  ³ XXX  ³ R7.5 ³ MSE  ³ M7.5 ³ M6.5 ³ M5.5 ³
 *   ÀÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÙ
 *
 *     M7.5, M6.5, M5.5 are RSTxx Masks -> 0=available , 1=masked
 *     MSE         -   Mask set enable, if 0 bits 0-2 are ignored,
 *                     if 1 mask is set
 *     RST 7.5     -   if 1 'rst_7_5_ff' is reset
 *
 *     Bit 5 is ignored
 *
 *     SDE if 1 bit 7 is output to serial output data latch
 *     SOD serial output data, ignored if bit 6 =0
 *
 * ******************************************************************* */

 #define    MASK_5_5                  0x01
 /* mask value for setting the 'rst_5_5_ff' variable */
 #define    MASK_6_5                  0x02
 /* mask value for setting the 'rst_6_5_ff' variable */
 #define    MASK_7_5                  0x04
 /* mask value for setting the 'rst_7_5_ff' variable */
 #define    MASK_SET_ENABLE           0x08
 #define    RESET_RST_7_5             0x10
 #define    SERIAL_DATA_ENABLE        0x40
 #define    SERIAL_DATA               0x80

 #define    HELP_SEARCH_LEN           60
 /* a search can be made for a help link of only 60 characters.  This
    restriction is made to increase efficiency during search
 */
 #define  MAX_PREV_HELPS              20
 /* maximum number of previous helps that you can get by pressing Alt F1 */

 #define  HELP_BOX_WIDTH              74
/*----------------------------------------------------------------------*/

#endif