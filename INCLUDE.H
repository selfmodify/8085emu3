#ifndef _INCLUDE_H_
 #define _INCLUDE_H_

 /* all the include files go here */

/* #include <alloc.h>*/

 typedef unsigned clock_t;

 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <string.h>
 #include <dos.h>
 #include <conio.h>
 #include <time.h>

 #if (__TURBOC__ <= 0x18d)

 #define _NOCURSOR      0
 #define _SOLIDCURSOR   1
 #define _NORMALCURSOR  2

 void _setcursortype(int x)
 {
   union REGS r;
    r.h.ah = 0x1;
    switch(x)
    {
      case _SOLIDCURSOR  :  r.h.ch = 0;
                            r.h.cl = 4;
                            break;
      case _NORMALCURSOR :  r.h.ch = 3;
                            r.h.cl = 4;
                            break;
      case _NOCURSOR     :  r.h.ch = 0x20;
			    break;
      default            :  return;
    }
    int86(0x10,&r,&r);
 }
 #endif

/* ------------------------------------------------------------------- */

 #include "defines.h"   /* the various '#defines'  */

 #include "typedef.h"   /* the various type definitions for the structures,
			  arrays and function pointers
                        */
 #include "box.h"

 #include "vars.h"      /* the various global variables */

 #include "macro.h"     /* various macros for accessing the string's in
                           the 8085 machine struct
                        */

 #include "forward.h"   /* forward declaration for functions are placed
                            here
                        */

 #include "myerror.h"   /* The various #defines for error messages and
                           an array of strings containing the
                           appropriate messages
                        */

 #include "lowlevel.h"  /* low level routines for accessing the various
                           registers
                        */

 #include "flags.h"     /* routines to manipulate the flags */

 #include "mov.h"       /* data movement function */

 #include "transfer.h"  /* other data movement functions such as
                           LDAX, LHLD, STAX, LXI etc
                        */

 #include "add.h"

 #include "control.h"

 #include "logical.h"   /* logical functions like and "compare","and",
                           "or","xra" etc
                        */

 #include "branch.h"

 #include "undef.h"     /* functions which have not yet been implemented */

 #include "lex.h"       /* lexical analysis functions */

 #include "parse.h"     /* the various functions which parse a given string
			   and find out the equivalent machine code*/
 #include "mnemonic.h"
 /*name of the instruction and pointers to functions which can parse them*/

 #include "directve.h"
 /* the functions which identify various directives are given here */

 #include "symbol.h"   /* functions for symbol table manipulation */

 #include "code2str.h"
 /* contains functions which convert a given machine code into it's
    equivalent mnemonic using the 'mot'
 */

 #include "simulate.h"

 /* array of pointers to functions which simulate the various low level
    functions.  The array of pointer is a part of a structure which also
    has the length of instruction and its mnemonic
 */

 #include "extra.h"
 /* extra functions such as 'ParseLex','GetStringFromCode' */


 #include "output.h"     /* output routines                        */

 #include "led.h"        /* led display functions                  */

 #include "input.h"      /* functions to read from keyboard        */

 #include "system.h"     /* system calls                           */

 #include "draw.h"       /* draw the various boxes                 */


 #include "help.h"       /* various functions to activate help     */

 #include "line.h"       /* perform line input                     */

 #include "run.h"        /* various functions to run the machine   */

 #include  "init.h"      /* initializing routines                  */

 #include  "clear.h"     /* The last clearing act when the program
                            terminates                             */
#endif