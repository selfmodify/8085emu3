#ifndef _MYERROR_H_
 #define _MYERROR_H_

  /* the various defines for the error messages and the equivalent
     message strings.  Also contains routines to print run time errors
  */

  #define    ERROR                 -5

  #define    ILLEGAL_DIRECTIVE     -6
  /* A number did not follow org */

  #define    LARGE_DIRECTIVE       -7
  /* the number following was greater than 65535 */

  #define    LARGE_NUMBER          -8
  /* immediate number too large */

  #define    REGISTER_EXPECT       -9
  /* a register number was expected*/

  #define    REG_OR_MEM_EXPECT     -10
  /* a register or memory address was expected */

  #define    NUMBER_EXPECT         -11
  /* a number was expected */

  #define    COMMA_EXPECTED        -12
  /* a comma was expected */

  #define    WRONG_REG             -13
  /* a wrong register was specified */

  #define    UNWANTED_OP           -14
  /* a operand which was not required was specified */

  #define    ADDR_TOO_LARGE       -15
  /* The immediate address is larger than the constant LARGE_ADDR */

  #define    COLON_EXPECTED        -16
  /* a colon is expected after a label  */

  #define    SYNTAX_ERROR          -17

  #define    DUPLICATE_LABEL       -18
  /* same label was defined twice */
  #define    TABLE_FULL            -19
  /* symbol table is full */

  #define    NOT_FOUND             -20
  /* symbol was not found */

  #define    UNDEFINED_LABEL       -21
  /* an undefined label was used as an address 'label' */

  #define    READ_SEG_FAULT        -22

  #define    WRITE_SEG_FAULT       -23

  #define    STACK_OVER_ERROR      -24

  #define    EXECUTE_ERROR         -25

  #define    STACK_UNDER_ERROR     -26

  #define    MEM_TO_MEM_TRANSFER   -27
  /* found a mov m,m which is a not allowed in 8085 */

  #define    BAD_SYSTEM_CALL       -28

  #define    INVALID_OPCODE        -29

  #define    __BAD_NUMBER_FORMAT   -(DOUBLE_INT+1)

  #define    BAD_NUMBER_FORMAT     -30
  /* eg:- a number was specified as octal but had '9' in it.
     The number '-30' is actually a pointer into the array 'error_msg'.
     functions which detect this error during parsing actually return
     '__BAD_NUMBER_FORMAT' which larger than 'unsigned int' so that it
     is distinguishable from normal numbers.
     __BAD_NUMBER_FORMAT is replaced by BAD_NUMBER_FORMAT so that a
     reasonable index into the array 'error_msg' is obtained
     ('error_msg[__BAD_NUMBER_FORMAT]' is unimaginable )
  */

  #define    INSUFFICIENT_MEMORY    -31

  #define    EXTRA_INPUT            -32
  /* this error is generated only at run time, when one  keys in an
     instruction with operands that are not required
     This error has been forcefully caught, so that no one says :-
     "look it's buggy!!!!!!"
  */

  #define   TOO_MANY_ERRORS         -33
  /* the machine encountered too many errors during the parse */

 char  *error_msg[]=
  {
    "Error",
    "Error",
    "Error",
    "Error",
    "Unknown Error",
    "Org directive not followed by a number",
    "Address in Directive was larger than physical memory",
    "Immediate number too large",
    "A Register name is expected",
    "Register or memory expected as operand",
    "Number expected as operand",
    "Comma expected",
    "Wrong register specified as operand",
    "Unwanted operand",
    "Immediate Address too large",
    "Colon Expected after a label",
    "Syntax Error",
    "Duplicate definition of label",
    "Internal Error - Symbol table full",
    "Label not found",
    "Label is not defined",
    "Tried to read beyond valid memory location",
    "Tried to write beyond valid memory location",
    "Stack overflow or incorrect initialization",
    "Tried to execute beyond valid memory location",
    "Stack underflow or incorrect initialization",
    "Memory to Memory transfer not allowed",
    "Bad system Call",
    "Invalid Opcode encountered",
    "Bad Number format",
    "Insufficient memory",
    "Extra input after expression",
    "Too many errors"
  };
/* --------------------------------------------------------------------- */

  #define ANY_ERROR           0x000003fel
  #define QUIT                  1 /* quit from the machine */
  #define SEVERE_ERROR          2 /* severe error occured in the machine*/
  #define WARNING               4 /* not so severe */
  #define INVALID_OP            8 /* Invalid op code encountered */
  #define READ_FAULT           16 /* tried to read beyond valid mem loc */
  #define WRITE_FAULT          32 /* tried to write beyond valid mem loc*/
  #define STACK_OVERFLOW       64
  /* tried to push beyond zero or initialized it beyond valid memory
     location */
  #define IP_BEYOND_MEMORY    128
  /* Tried to acess instruction beyond valid memory location */
  #define STACK_UNDERFLOW     256
  #define BADSYSTEMCALL       512
  #define JUST_RETURNED      1024
  /* just returned from a subroutine, this is set by any 'ret' instruction */
  #define JUST_CALLED        2048
  /* just entered a call statement, this is et by any 'call' instruction */
/*------------------------------------------------------------------------*/
 int SetAndPrintError(int x)
 {
   if(x>=0 || GERROR_COUNT<0) return 0;
   if(GERROR_COUNT--==0)
   printf("\n%d : %s",LINE_NUMBER(),error_msg[-(TOO_MANY_ERRORS+1)]);
   else printf("\n%d : %s : %s ",LINE_NUMBER(),error_msg[-(x+1)],BUFFER());
   SET_STATUS(WARNING);
   return GET_STATUS();
 }
/* --------------------------------------------------------------------- */
 int PrintRunError(int x)
 {
   if(x>=0) return 0;
   cprintf("%s :\n\r",error_msg[-(x+1)]);
   DumpRegisters();
   SET_STATUS(SEVERE_ERROR);
   return GET_STATUS();
 }
/* --------------------------------------------------------------------- */
 int SevereErrorsDuringRun(void)
 {
    if((GET_STATUS() & ANY_ERROR))    return 1;
    return 0;
 }
/* --------------------------------------------------------------------- */
 int PrintRunErrors(void)
 {

   if(GET_STATUS() & STACK_OVERFLOW)        PrintRunError(STACK_OVER_ERROR);
   else if(GET_STATUS() & IP_BEYOND_MEMORY) PrintRunError(EXECUTE_ERROR);
   else if(GET_STATUS() & INVALID_OP)       PrintRunError(INVALID_OPCODE);
   else if(GET_STATUS() & READ_FAULT)       PrintRunError(READ_SEG_FAULT);
   else if(GET_STATUS() & WRITE_FAULT)      PrintRunError(WRITE_SEG_FAULT);
   else if(GET_STATUS() & STACK_UNDERFLOW)  PrintRunError(STACK_UNDER_ERROR);
   else if(GET_STATUS() & BADSYSTEMCALL)    PrintRunError(BAD_SYSTEM_CALL);
   return 1;
 }
/* --------------------------------------------------------------------- */
 /* Note :-
            Stack Overflow errors may never occur becuase a write
            segmentation fault will be generated
 */

 int BadSystemCall(void)
 {
   SET_STATUS(BADSYSTEMCALL);
   return BAD_SYSTEM_CALL;
 }
/* --------------------------------------------------------------------- */
 int StandardErrorMessageBox(char *s)
 {
  /* Beep(); */
   if(StandardMessageBox(s)==F1)
      DisplayHelp(0,s);
   return GET_STATUS();
 }

#endif

