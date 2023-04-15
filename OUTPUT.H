#ifndef _OUTPUT_H_
 #define _OUTPUT_H_

 /* various functions which print the registers, mnemonic,flags and
    memory dump
 */

 #define BEYOND_MEM         "invalid"
 #define IP_ATTRIBUTE       MAKEATTR(CYAN,BLACK)
 /* highlight the current instruction using this colour */
 #define BREAKPT_ATTRIBUTE  MAKEATTR(LIGHTBLUE,WHITE)
 /* show break points in this colour */
/*------------------------------------------------------------------------*/
 void  PrintRegisters(void)
 {
  static   unsigned char s[81];
  int      i=1;
  unsigned attr;
  unsigned text_attr = REG_DISPLAY_BOX().b.text_attr;

   attr = SWITCH()==REG_BOX_TAB ? REG_DISPLAY_BOX().b.highlight :
                        REG_DISPLAY_BOX().b.normal;

   sprintf((char *)s," a   =   %02x",GetA());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," b   =   %02x",GetB());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," c   =   %02x",GetC());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," d   =   %02x",GetD());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," e   =   %02x",GetE());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," h   =   %02x",GetH());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," l   =   %02x",GetL());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   if((unsigned long)GetHL()<MAIN_MEMORY)
     sprintf((char *)s," [HL]= %04x",GetMemWord(GetHL()));
   else sprintf((char *)s, " [HL]=%s",BEYOND_MEM);
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   /* draw a '-------------'
      StringAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,(uchar *)screen_temp);
   */

   sprintf((char *)s," IP  = %04x",GetIP());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);

   sprintf((char *)s," SP  = %04x",GetSP());
   if(REG_DISPLAY_BOX().cp != i-1)
      HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(REG_DISPLAY_BOX().b,1,i++,s,attr);
 }
/*------------------------------------------------------------------------*/
 void PrintFlags(void)
 {
  static unsigned char s[81];
  int                  i=1;
  unsigned             attr;
  unsigned             text_attr = FLAG_BOX().b.text_attr;;

   attr = SWITCH()==FLAG_BOX_TAB ? FLAG_BOX().b.highlight
                                 : FLAG_BOX().b.normal;

   sprintf((char *)s," c=%#d",GetCarry());
   if(FLAG_BOX().cp != i-1)
      HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,attr);

   sprintf((char *)s," s=%#d",GetSign());
   if(FLAG_BOX().cp != i-1)
      HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,attr);

   sprintf((char *)s," z=%#d",GetZero());
   if(FLAG_BOX().cp != i-1)
      HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,attr);

   sprintf((char *)s," p=%#d",GetParity());
   if(FLAG_BOX().cp != i-1)
      HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,attr);

   sprintf((char *)s," a=%#d",GetAuxCarry());
   if(FLAG_BOX().cp != i-1)
      HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,text_attr);
   else HighlightAndBlankInBox(FLAG_BOX().b,1,i++,s,attr);
 }
/*------------------------------------------------------------------------*/
 void PrintCode(void)
 {
   static unsigned char s[81];
   static unsigned char s2[81];
   int incr=0;
   word i; /* this should be long or unsigned, to access memory upto 64K */
   word ip; /* this should be long or unsigned, to access memory upto 64K */
   unsigned attr;
   int ch;

    attr = SWITCH()== CODE_BOX_TAB ? CODE_BOX().b.highlight
                                   : CODE_BOX().b.normal;
    for(i=0,ip=CODE_BOX().start;
             (ip<MAIN_MEMORY) && (i<CODE_BOX().b.height-1) ; i++,ip+=incr)
    {
       incr = GetStringFromCode(ip,(char *)s);
       ch = ip==GetIP() ? '' : '*';
       /* default pattern for indicating break points */

       if(IsABreakPoint(ip)!=-1)
       {
          if(ip==CODE_BOX().cp)
             ch = ']';
          sprintf((char *)s2,"*%04x:%c%s",ip,ch,s);
          HighlightAndBlankInBox(CODE_BOX().b,1,i+1,s2,BREAKPT_ATTRIBUTE);
       }
       else if(ip==CODE_BOX().cp)
       {
          sprintf((char *)s2,"[%04x:]%s",ip,s);
          HighlightAndBlankInBox(CODE_BOX().b,1,i+1,s2,attr);
       }
       else if(ip==GetIP())
       {
          sprintf((char *)s2,"%04x:%s",ip,s);
          HighlightAndBlankInBox(CODE_BOX().b,1,i+1,s2,IP_ATTRIBUTE);
       }
       else
       {
        sprintf((char *)s2," %04x: %s",ip,s);
        StringAndBlankInBox(CODE_BOX().b,1,i+1,s2);
       }
    }
    for(  ; i<CODE_BOX().b.height-1  ; i++)
        StringAndBlankInBox(CODE_BOX().b,1,i+1,(uchar *)" ");
 }
/*----------------------------------------------------------------------- */
 void PrintMemoryDump(void)
 {
   static unsigned char s[81];
   word i,j;
   unsigned attr;

    attr = SWITCH()==MEM_DUMP_TAB ? MEM_DUMP_BOX().b.highlight
                                  : MEM_DUMP_BOX().b.normal;
    for(i=0,j=MEM_DUMP_BOX().start;
            (i<MEM_DUMP_BOX().b.height-1) && (j<MAIN_MEMORY) ; i++,j++)
    {
      if(j==MEM_DUMP_BOX().cp)
      {
        sprintf((char *)s," %04x: %02x",j,GetMemByte(j));
        HighlightAndBlankInBox(MEM_DUMP_BOX().b,1,i+1,s,attr);
      }
      else
      {
        sprintf((char *)s," %04x: %02x",j,GetMemByte(j));
        StringAndBlankInBox(MEM_DUMP_BOX().b,1,i+1,s);
      }
    }
    for(  ; i<MEM_DUMP_BOX().b.height-1  ; i++)
        StringAndBlankInBox(MEM_DUMP_BOX().b,1,i+1,(uchar *)" ");
 }
/*------------------------------------------------------------------------*/
 void DefaultStatusLine(void)
 {
   PrintStatusLine(status_string);
   /* status_string is defined in 'vars.h' */
 }
/*------------------------------------------------------------------------*/
 void HelpLine(char *s)
 {
   StatusLine((uchar *)s);
   /* status_string is defined in 'vars.h' */
 }
/*------------------------------------------------------------------------*/
 void PrintStackDump(void)
 {
   static unsigned char s[81];
   int i=1;

   if(GetSP()<MAIN_MEMORY-1)
     sprintf((char *)s," [SP]  = %04x",GetMemWord(GetSP()));
   else
   {
    if(random(100)==25)
      sprintf((char *)s," [SP]  =%s",BEYOND_MEMORY);
    else sprintf((char *)s," [SP]  =%s",BEYOND_MEM);
   }
   StringAndBlankInBox(STACK_BOX().b,1,i++,s);

   if(GetSP()+2<MAIN_MEMORY-1)
     sprintf((char *)s," [SP+2]= %04x",GetMemWord(GetSP()+2));
   else sprintf((char *)s," [SP+2]=%s",BEYOND_MEM);
   StringAndBlankInBox(STACK_BOX().b,1,i++,s);

   if(GetSP()+4<MAIN_MEMORY-1)
     sprintf((char *)s," [SP+4]= %04x",GetMemWord(GetSP()+4));
   else sprintf((char *)s," [SP+4]=%s",BEYOND_MEM);
   StringAndBlankInBox(STACK_BOX().b,1,i++,s);

   if(GetSP()+6<MAIN_MEMORY-1)
     sprintf((char *)s," [SP+6]= %04x",GetMemWord(GetSP()+6));
   else sprintf((char *)s," [SP+6]=%s",BEYOND_MEM);
   StringAndBlankInBox(STACK_BOX().b,1,i++,s);

  /* if(GetSP()+8<MAIN_MEMORY-1)
     sprintf((char *)s," [SP+8]= %04x",GetMemWord(GetSP()+8));
   else sprintf((char *)s," [SP+8]=%s",BEYOND_MEM);
   StringAndBlankInBox(STACK_BOX().b,1,i++,s);
  */
 }
/*------------------------------------------------------------------------*/
 int  MessageBox(int x,int y,int width,int height,char *s)
 {
   int len;
   int ch;
   int msg_pos;
   box b;

   if((len = strlen(s))>79) len=79;
   if((msg_pos=(width-len)/2) <0) msg_pos =1;
   /* position of message in the box */
   InitBox(&b,x,y,width,height,BOX_STYLE,WHITE,LIGHTGRAY);
   SetBoxTextAttr(&b,BLACK,LIGHTGRAY);
   SetBoxNormalAttr(&b,BLACK,CYAN);
   SetBoxHighlightAttr(&b,BLACK,WHITE);
   gettext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   DrawBox(b);
   StringAndBlankInBox(b,msg_pos,height/2,(unsigned char *)s);
   ch = GetTheChar(NO_POLLING);
   puttext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   return ch;
 }
/*------------------------------------------------------------------------*/
 int  StandardMessageBox(char *s)
 {
   return MessageBox(4,11,72,4,s);
 }
/*------------------------------------------------------------------------*/
 void DisplayError(char *s)
 {
    Beep();
    StandardMessageBox(s);
 }
/*------------------------------------------------------------------------*/
 void PrintStopped(void)
 {
  char *msg="  Stopped  ";
  unsigned int attr = MAKEATTR(WHITE,BLACK);
  PrintToScreen(1,1,(uchar *)msg, attr,strlen(msg));
 }
/*------------------------------------------------------------------------*/
 void PrintReady(void)
 {
  char *msg="  Ready    ";
  unsigned int attr = MAKEATTR(WHITE,BLACK);
  PrintToScreen(1,1,(uchar *)msg,attr,strlen(msg));
 }
/*------------------------------------------------------------------------*/
 void PrintRunning(void)
 {
  char *msg="  Running  ";
  unsigned int attr = MAKEATTR(WHITE,BLACK);
  PrintToScreen(1,1,(uchar *)msg,attr,strlen(msg));
 }


#endif