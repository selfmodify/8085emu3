#ifndef _FORAWRD_H_
 #define _FORWARD_H_

 /* forward declarations for  functions should be included in this file */

/*-----------------------------------------------------------------------*/
 int FindInTable(char *s);
 /* find an entry in the symbol table */
/*-----------------------------------------------------------------------*/
 int InitMachine(machine_ptr m);
 /* initialize the machine */
/*-----------------------------------------------------------------------*/
 int GetStringFromCode(unsigned _addr,char *s);
 /* given a memory address this function converts the machine code at
    that memory locations into its mnemonic and also returns its length
 */
/*-----------------------------------------------------------------------*/
  int PerformSystemCall(void);
  /* performs the system calls ('CALL 0005')
     defined in 'SYSTEM.H'
  */
/*-----------------------------------------------------------------------*/
  int DumpRegisters(void);
  /* dump the contents of all the registers to the screen.  This is called
     when a system run time error occurs.
     The function is called by 'PrintRunErrors in MYERROR.H'
     The function is defined in 'LOWLEVEL.H'
  */
/*-----------------------------------------------------------------------*/
  int IsABreakPoint(word addr);
  /* is 'addr' pointing to a break point instruction.
     defined in 'run.h'
  */
/*-----------------------------------------------------------------------*/
  int GetTheChar(int x);
   /* defined in input.h , gets a character from keyboard */
/*-----------------------------------------------------------------------*/
  int ReadAtPosition(int x,int y,char *s,int width,int max,unsigned attr);
  /* reads a string from keyboard at the specified position 'x','y'.
     Defined in 'line.h'
  */
/*-----------------------------------------------------------------------*/
 void Beep(void);  /* beeps the speaker, defined in 'Extra.h' */
/*-----------------------------------------------------------------------*/
 int  StandardMessageBox(char *s);
 /* displays a standard message box, defined int 'output.h' */
/*-----------------------------------------------------------------------*/
 int DisplayHelp(int key,char *s);
 /* display help using the parameter 'key' and 's', defined in
    'help.h'
 */
#endif