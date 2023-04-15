#ifndef __EXTRA_H__
 #define __EXTRA_H__

 /* Extra functions which initialize the various boxes and also functions
    which call the lowlevel parsing routines (defined in 'parse.h')
 */

/*-----------------------------------------------------------------------*/
 void Beep(void)
 {
   sound(180);
   delay(225);
   nosound();
 }
/*------------------------------------------------------------------------*/
 int SetRegisterBox(int x,int y,int width, int height)
 {
   InitBox(&REG_DISPLAY_BOX().b,x,y,width,height,BOX_STYLE,WHITE,LIGHTGRAY);
   SetBoxTextAttr(&REG_DISPLAY_BOX().b,BLACK,LIGHTGRAY);
   SetBoxNormalAttr(&REG_DISPLAY_BOX().b,BLACK,CYAN);
   SetBoxHighlightAttr(&REG_DISPLAY_BOX().b,BLACK,WHITE);
   return 1;
 }
/*------------------------------------------------------------------------*/
 int SetFlagBox(int x,int y,int width, int height)
 {
   InitBox(&FLAG_BOX().b,x,y,width,height,BOX_STYLE,WHITE,CYAN);
   SetBoxTextAttr(&FLAG_BOX().b,BLACK,CYAN);
   SetBoxHighlightAttr(&FLAG_BOX().b,BLACK,WHITE);
   SetBoxNormalAttr(&FLAG_BOX().b,RED,LIGHTGRAY);
   return 1;
 }
/*------------------------------------------------------------------------*/
 int SetStackBox(int x,int y,int width, int height)
 {
   InitBox(&STACK_BOX().b,x,y,width,height,BOX_STYLE,WHITE,BLUE);
   SetBoxTextAttr(&STACK_BOX().b,LIGHTGRAY,BLUE);
   SetBoxHighlightAttr(&STACK_BOX().b,WHITE,RED);
   SetBoxNormalAttr(&STACK_BOX().b,BLACK,CYAN);
   STACK_BOX().cp = STACK_BOX().b.height;
   return 1;
 }
/*------------------------------------------------------------------------*/
 int SetCodeBox(int x,int y,int width, int height)
 {
   InitBox(&CODE_BOX().b,x,y,width,height,BOX_STYLE,WHITE,DARKGRAY);
   SetBoxTextAttr(&CODE_BOX().b,LIGHTGRAY,DARKGRAY);
   SetBoxNormalAttr(&FLAG_BOX().b,BLACK,CYAN);
   CODE_BOX().cp = CODE_BOX().start = 0;
   return 1;
 }
/*------------------------------------------------------------------------*/
 int SetMemDumpBox(int x,int y,int width, int height)
 {
   InitBox(&(MEM_DUMP_BOX().b),x,y,width,height,BOX_STYLE,WHITE,LIGHTBLUE);
   SetBoxTextAttr(&(MEM_DUMP_BOX().b),WHITE,LIGHTBLUE);
   MEM_DUMP_BOX().start  =  MEM_DUMP_BOX().cp = 0; /* reset pointers */
   return 1;
 }
/*------------------------------------------------------------------------*/
 int SetLedDisplayBox(int x,int y,int width, int height)
 {
   InitBox(&KIT->display.led_display,x,y,width,
		  height,BOX_STYLE,WHITE,BLUE);
   SetBoxTextAttr(&KIT->display.led_display,WHITE,BLUE);
   return 1;
 }
/*------------------------------------------------------------------------*/
 int IsInstruction(void)
 {
  int x;
   if((x=IsAnInstruction())==-1) return -1;/* it was not an instruction */
  /* if it was an instruction then x has the index to the array of
     structures 'mnemonic' whose 'parse' has the pointer to function
     which can parse the instruction */
   return  _MNEMONIC()[x].parse();
 }
/*------------------------------------------------------------------------*/
 int Parse(char *s)
 {
  int got;  /* token number obtained */
  int x=0;

    got=InitToken(s);
    if((x=IsComment())!=0)  /* got the starting of a one line comment */
     return x;
    /* if it is not a comment it should be a directive or an instruction */
    if((x=IsDirective())>0 || x<0)   return x;
   /* if((x=IsInstruction())>0 || x<0) return x;
      if zero is used as a value to return an error then
      'nop' cannot be implemented
   */
    if((x=IsInstruction())!=-1) return x;
    if(got==EOI || got==EOLN) return got;
    if(got==IDENTIFIER)
    {
      if(Advance(0)!=COLON) return COLON_EXPECTED;
      return LABEL;
    }
    return ERROR;
 }
/*------------------------------------------------------------------------*/
 int ParseLex(void)
 {
   int x;
    if((x=Parse(STRING()))<=0 || x==CORRECT_DIRECTIVE)
      return x;
    return 1;
 }
/*------------------------------------------------------------------------*/
 int GetInstructionLen(word _addr)
 {
   /* give the length of the instruction at the given address */

    if(_addr>LARGEST_ADDR) return 0;
    return mot[GetMemByte(_addr)].length;
 }
/*------------------------------------------------------------------------*/
 int GetStringFromCode(word _addr,char *s)
 {
  ptr_to_convert       conv;
  int pos;
   /* pointer to function which converts machine codes into equivalent
      mnemonics
   */
   if(_addr>LARGEST_ADDR) return 0;
   pos  = GetMemByte(_addr);
   conv = mot[pos].Convert;
   return (*conv)(_addr,pos,s);
 }
/*------------------------------------------------------------------------*/
 word GetNearestNextAddr(word _addr)
 {
   /* get the address of the instruction next to  the current
      instruction.
   */
   if(_addr>=MAIN_MEMORY-1) return MAIN_MEMORY-1;
   return _addr + GetInstructionLen(_addr);
 }
/*------------------------------------------------------------------------*/
 word GetNearestPrevAddr(word _addr)
 {
   /* get the address of the instruction just before the current
      instruction.  The address of the previous instruction need not
      be 1 byte behind
   */
   word i,j;
   if(_addr==0 || _addr>=MAIN_MEMORY) return 0;
   for( j=0,i=0 ; i < _addr ; i += GetInstructionLen(i) )
            j = i;
   return j;
 }
/*------------------------------------------------------------------------*/
 word PerformCodePageUp(void)
 {
   word i,j;

    i  = CODE_BOX().cp - (CODE_BOX().b.height-1)*3;
    /* what if this is '-ive' */

    i  = GetNearestPrevAddr(i);
    for( j=0 ; i < CODE_BOX().cp ; i += GetInstructionLen(i),j++ )
             page_up[j] = i;
    /* global variable 'page_up' is declared in 'vars.h' */
   return CODE_BOX().start=CODE_BOX().cp=page_up[j-CODE_BOX().b.height+1];
 }
/*------------------------------------------------------------------------*/
 word PerformCodeEnd(void)
 {
   word i,j;

    if(CODE_BOX().cp>=MAIN_MEMORY) return CODE_BOX().cp=MAIN_MEMORY-1;
    /* already at end */

    i  = MAIN_MEMORY -1 - (CODE_BOX().b.height-1)*3;
    i  = GetNearestPrevAddr(i);
    for( j=0 ; i < MAIN_MEMORY  ; i += GetInstructionLen(i),j++ )
             page_up[j] = i;
    /* global variable 'page_up' is declared in 'vars.h' */
   CODE_BOX().start=page_up[j-CODE_BOX().b.height+1];
   return CODE_BOX().cp= i>=MAIN_MEMORY ? page_up[j-1] : page_up[j];
 }
/*------------------------------------------------------------------------*/
 void PerformCodeDown(void)
 {
  int i;
  word j;

    if(CODE_BOX().cp>=MAIN_MEMORY-1) return; /* already at end */
    for(i=0,j=CODE_BOX().start; j<MAIN_MEMORY-1 && i<CODE_BOX().b.height-2;
                  i++ )
          j += GetInstructionLen(j);
    /* now 'i' has the number of instructions in the window */
    if(CODE_BOX().cp<j)
    {
      if((j=GetNearestNextAddr(CODE_BOX().cp))<=MAIN_MEMORY-1)
            CODE_BOX().cp = j;
    }/* don't remove these paranthesis */
    else
    {
      /* 'cp' is at the last instruction in the window and you want to
         move down further
      */
      if((long)CODE_BOX().start+CODE_BOX().b.height > MAIN_MEMORY)
         return;  /* reached end of memory so return */
      if(CODE_BOX().start<=MAIN_MEMORY-CODE_BOX().b.height-1)
      CODE_BOX().start = GetNearestNextAddr(CODE_BOX().start);
      if((j=GetNearestNextAddr(CODE_BOX().cp))<=MAIN_MEMORY-1)
            CODE_BOX().cp = j; /* don't go beyond 'MAIN_MEMORY-1' */
    }
 }
/*------------------------------------------------------------------------*/
 void PerformCodeUp(void)
 {
   if(CODE_BOX().cp==CODE_BOX().start)
   {  /* if you have reached top of box */
     if(CODE_BOX().start<=0) return;
     CODE_BOX().start = CODE_BOX().cp = GetNearestPrevAddr(CODE_BOX().start);
   }
   else  CODE_BOX().cp = GetNearestPrevAddr(CODE_BOX().cp);
   if(CODE_BOX().cp < CODE_BOX().start) CODE_BOX().start = CODE_BOX().cp;
 }
/*------------------------------------------------------------------------*/
 void PerformMemDumpDown(void)
 {
   if(MEM_DUMP_BOX().cp-MEM_DUMP_BOX().start>=MEM_DUMP_BOX().b.height-2)
   {
     if(MEM_DUMP_BOX().start<=MAIN_MEMORY-MEM_DUMP_BOX().b.height)
     {
       ++MEM_DUMP_BOX().start;
       ++MEM_DUMP_BOX().cp;
     }
   }
   else ++MEM_DUMP_BOX().cp;
   if(MEM_DUMP_BOX().cp>=MAIN_MEMORY) MEM_DUMP_BOX().cp = MAIN_MEMORY-1;
 }
/*------------------------------------------------------------------------*/
 void UnmangleName(void)
 {
   int i;

     for(i=0;  BEYOND_MEMORY[i]  ; i++)
         BEYOND_MEMORY[i] -= i;
 }
/*------------------------------------------------------------------------*/
#endif