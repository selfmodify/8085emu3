#ifndef _TYPEDEF_H_
 #define _TYPEDEF_H_

 /* the various type declarations go here */


 typedef struct
 {
   int               x,y;
   int               width,height;
   unsigned          attr;   /* attribute in which the box should be drawn */
   int               type;        /* type of box */
   int               top_hor,left_ver;
   /* characters which represent the horizontal
   and vertical side e.g.:-  'Ä ³' */

   int               bottom_hor,right_ver;
   /* characters which represent the horizontal and
      vertical side e.g.:-  'Ä ³' */
   int               rtop,ltop;   /* right and left top */
   int               rbot,lbot;   /* right and left bottom */
   unsigned          highlight;   /* attribute for highlight colour */
   unsigned          another_attr;  /* this attribute can be used for
                                     anything */
   unsigned          text_attr;
                     /* attribute in which text should be written */
   unsigned          normal;
 }box;
/*----------------------------------------------------------------------*/
 typedef struct
 {
   box b;
   unsigned   cp;     /* current position */
   unsigned   start;  /* start displaying from this position */
 }scroll_box;
/*---------------------------------------------------------------------*/
 typedef int (*ptr_to_parse)(void);
 /* pointer to function which parse a given string
    eg:- 'MOV A,B'
 */
/*---------------------------------------------------------------------*/
 typedef int (*ptr_to_simulate)(void);
 /* pointer to function which simulate the '8085'  Instuctions*/
/*---------------------------------------------------------------------*/
 typedef int (*ptr_to_convert)(unsigned _addr,int pos,char *s);
 /* pointer to function which converts a given op code into its
    equivalent string and also returns its length
 */
/*---------------------------------------------------------------------*/
  typedef unsigned int      word;
  typedef unsigned long     dword;
  typedef unsigned char     uchar;
/*---------------------------------------------------------------------*/
  typedef struct help_struct_tag
  {
    uchar                    *buffer;  /* buffer to hold the string */
    struct help_struct_tag   *next;  /* pointer to next node */
    struct help_struct_tag   *prev;  /* pointer to previous node */
  }help_struct;
/*---------------------------------------------------------------------*/
  typedef struct
  {
    help_struct   *head;    /* pointer to head node */
    help_struct   *current; /*ptr to current node, used by display routines*/
    help_struct   *end;     /* ptr to last node */
    word          lines_read; /* number of lines read into the buffer */
    char          search[HELP_SEARCH_LEN+1];
    /* when 'return' is pressed in a help link 'search' has the string which
       is to be searched for a link
    */
    char          prev_help[MAX_PREV_HELPS][HELP_SEARCH_LEN+1];
    int           prev_help_ctr;
    scroll_box    b;
    int x,y;                  /* current x and y coordinates */
  }help_box;
/*---------------------------------------------------------------------*/
 typedef struct
 {
   /* the structure 'box' & 'scroll_box' is declared in 'box.h'   */
   scroll_box   regs;   /* display the contents of registers      */
   scroll_box   code;   /* code is displayed in this box          */
   scroll_box   flag;   /* display the flags                      */
   scroll_box   stack;  /* display stack contents
                           (currently this is not scrollable)     */
   box          led_display;  /* the led's are displayed in this box  */
   scroll_box   dump;
 }output;
/*---------------------------------------------------------------------*/

  typedef struct
  {
    char  *name; /* name of the instruction eg:- 'mov'*/
    int   len;          /* length of instruction */
    ptr_to_parse parse; /* pointer to function to parse the instruction*/
  }instruction_struct;

/*---------------------------------------------------------------------*/

 typedef struct
 {
   char  token[TOKEN_SIZE+2];    /*  the current string                 */
   char  last[TOKEN_SIZE+2];     /*  last token obtained                */
   int   current;                /*  the value of the last token        */
   char  *str;                   /*  points to the last obtained token  */
   int   line_number;            /*  the current line number            */
   char  buffer[LINE_LENGTH+2];  /*  buffer to hold the entire string   */
 }lex_struct;

 typedef  lex_struct  *lex_ptr; /* pointer to lexical analysis structure */
/*---------------------------------------------------------------------*/
  typedef struct
  {
     uchar       a;
     uchar       flags;
     uchar       b;
     uchar       c;
     uchar       d;
     uchar       e;
     uchar       h;
     uchar       l;
    /* uchar       w;  the 'w' and 'z' registers are not used and
       uchar       z;  are given here only for completeness
    */
     word   ip;
     word   sp;
     word   temp;
     dword  long  temp32;   /* a 32 bit temporary variable */
  }registers;     /* the 8085 registers */
  /* don't use register its a keyword */

/*---------------------------------------------------------------------*/
 typedef struct
 {
   registers   r;
   uchar       ram[MAIN_MEMORY];
   unsigned    immediate; /* contains the last immediate value*/
   unsigned    ptr;    /* where to put the next instruction when parsing*/
 }cpu_struct;
 typedef cpu_struct *cpu_ptr;

/*-----------------------------------------------------------------------*/

 typedef struct
 {
   char name[LABEL_LEN];      /* name of the label */
   unsigned addr;             /* address of the label */
 }one_entry;

/*-----------------------------------------------------------------------*/

 typedef struct
 {
    one_entry  entry[TABLE_LENGTH];
    int       max;          /* maximum number of entries made so far */
 } symbol_table;
/*-----------------------------------------------------------------------*/

 typedef struct
 {
   int status_field[MAX_STATUS_FIELDS]; /* two status field display */
   int addr_field[MAX_ADDR_FIELDS];     /* four address field display */
   int data_field[MAX_DATA_FIELDS];  /* two data fields display  */
 }led_data_struct;
/*-----------------------------------------------------------------------*/
 typedef struct
 {
   long   lines_assembled; /* number of lines that actually form the code */
   word   last_break_point; /* where the last break point occured */
   word   break_points[MAX_BREAK_POINTS+1]; /* store break point addresses */
   word   bk_ctr;    /* how many break points have been installed so far */
 }debug;
/*-----------------------------------------------------------------------*/
 typedef struct
 {
   int               incr;  /* increment 'ip' by this value */
   uchar             code;
   ptr_to_simulate   simu;  /* pointer to simulating function */
   int run;                 /* if this is true the machine simply
                               runs without waiting for a key stroke
                            */
   int   step_over;       /* use F8 to step over a call instruction */
   int   tab;             /* used to switch between the different windows */
   word  old_ip,step_over_ip;
 }misc;
/*-----------------------------------------------------------------------*/
 typedef struct
 {
   int    executing;
   /* this is '1' if the machine is currently executing an instruction.
    This is useful in implementing interrupts
   */

   volatile int    interrupted;
   /* This is set to 1 if the processor was interrupted.
      This variable is set to '1' if any of the rst 5.5,6.5,7.5 or
      trap interrupts occur.
   */
   uchar           ei;         /* enable interrupt, if this is reset
                                  all interrupts except TRAP are disabled*/
   uchar           rst_5_5_ff; /* rst 5.5 flip flop, rst 5.5 is
                                  enabled only if this is reset */
   uchar           rst_6_5_ff; /* rst 6.5 flip flop, rst 5.5 is
                                  enabled only if this is reset */
   uchar           rst_7_5_ff; /* rst 7.5 flip flop, rst 5.5 is
                                  enabled only if this is reset */
   uchar           pending_5_5; /* pending rst 5.5 interrupt    */
   uchar           pending_6_5; /* pending rst 6.5 interrupt    */
   uchar           pending_7_5; /* pending rst 7.5 interrupt    */
   volatile int    interrupt_number;
   /* what interrupt was generated when 'interrupted' was '1'  */
 }interrupt_struct;
/*-----------------------------------------------------------------------*/
 typedef struct
 {
   cpu_struct         cpu;      /* the various registers and memory */
   unsigned           status;   /* status of the machine */
   output             display;  /* used to display the contents mem/regs */
   led_data_struct    led;      /* LED display */
   debug              i;
   misc               m;        /* various miscellaneous variables */
   interrupt_struct   intr_info;  /* interrupt information */
 }machine;
 typedef machine *machine_ptr;

/*----------------------------------------------------------------------*/


 /* ********************************************************************
  *
  *    Significance of lower 8 bits of  Status word
  *
  *   ÚÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄ¿
  *   ³ 7 ³ 6 ³ 5 ³ 4 ³ 3 ³ 2 ³ 1 ³ 0 ³
  *   ÀÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÙ
  *     ³   ³   ³   ³   ³   ³   ³   ³
  *     ³   ³   ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄ  QUIT THE MACHINE
  *     ³   ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  SEVERE ERROR
  *     ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  WARNING
  *     ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  INVALID OPCODE ENCOUNTERED
  *     ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  READ BEYOND MEMORY
  *     ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  WRITE BEYOND MEMORY
  *     ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  STACK OVERFLOW
  *     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  BRANCH ADDRESS NOT VALID
  *

  *    Significance of higher 8 bits of  Status word
  *   ÚÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄ¿
  *   ³ 15³ 14³ 13³ 12³ 11³ 10³ 9 ³ 8 ³
  *   ÀÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÙ
  *     ³   ³   ³   ³   ³   ³   ³   ³
  *     ³   ³   ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄ  IF A 'ret' INSTRUCTION HAS been
  *     ³   ³   ³   ³   ³   ³   ³                  JUST BEEN EXECUTED.
  *     ³   ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  IF A 'call' INSTRUCTION
        ³   ³   ³   ³   ³   ³                      HAS BEEN EXECUTED
  *     ³   ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *     ³   ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *     ³   ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *     ³   ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *     ³   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
  *
  *
  *
  * ******************************************************************* */

/*----------------------------------------------------------------------*/
 typedef struct
 {
   ptr_to_simulate       Simulate;  /* pointer to function which simulates the 8085 at run time */
   char                  *name;      /* for a given op code 'name' is the equivalent mnemonic */
   ptr_to_convert        Convert;    /* pointer to function which converts a given machine code
                                        to its mnemonic using the above variable 'name' */
   uchar                 length;     /* length of the instruction */
 }machine_op_struct;

 typedef machine_op_struct  machine_op_table[MAX_INSTRUCTIONS];

#endif

