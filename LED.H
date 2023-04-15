#ifndef _LED_H_
 #define _LED_H_

 /* Functions to print the Led's */

/*----------------------------------------------------------------------- */
 int PrintBlankLed(int xpos,int ypos,unsigned attr)
 {
   /* attr = MAKEATTR(BLUE,RED); */
    PrintToScreenN(xpos+1,ypos,' ',attr,2);
    PrintCharToScreen(xpos+3,ypos+1,' ',attr);
    PrintCharToScreen(xpos+3,ypos+2,' ',attr);
    PrintToScreenN(xpos+1,ypos+2,' ',attr,2);
    PrintCharToScreen(xpos,ypos+2,' ',attr);
    PrintCharToScreen(xpos,ypos+1,' ',attr);
    PrintToScreenN(xpos+1,ypos+1,' ',attr,2);
    PrintCharToScreen(xpos+3,ypos+3,' ',attr);
    PrintCharToScreen(xpos+4,ypos+2,' ',attr);
    return 1;
 }
/*----------------------------------------------------------------------- */
 int PrintOneLed(int xpos,int ypos,int value,unsigned attr,
                 uchar ver,uchar hor)
 {
   /* display the led's according to 'value' */
   PrintBlankLed(xpos,ypos,attr);  /* blank that particular LED */
   if(value & LED_A)
     PrintToScreenN(xpos+1,ypos,hor,attr,2);
   if(value & LED_B)
     PrintCharToScreen(xpos+3,ypos+1,ver,attr);
   if(value & LED_C)
     PrintCharToScreen(xpos+3,ypos+2,ver,attr);
   if(value & LED_D)
     PrintToScreenN(xpos+1,ypos+2,hor,attr,2);
   if(value & LED_E)
     PrintCharToScreen(xpos,ypos+2,ver,attr);
   if(value & LED_F)
     PrintCharToScreen(xpos,ypos+1,ver,attr);
   if(value & LED_G)
     PrintToScreenN(xpos+1,ypos+1,hor,attr,2);
   if(value & LED_DOT)
     PrintToScreenN(xpos+4,ypos+2,'.',attr,1);
   return 1;
 }
/*----------------------------------------------------------------------- */
 void PrintLedDot(int x,int y,unsigned attr)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+4,y+2,'.',attr);
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedHyphen(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintToScreenN(x+1,y+1,'_',attr,2);
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedG(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintToScreenN(x+1,y,hor,attr,2);    /* print uppper      '--' */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintCharToScreen(x+2,y+1,hor,attr);  /* print middle      '-' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedH(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x+3,y+1,ver,attr); /* print upper right '|'  */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedL(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedt(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedN(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+3,y+1,ver,attr); /* print upper right '|'  */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintCharToScreen(x+1,y+1,'\\',attr); /* print upper      '\\' */
   PrintCharToScreen(x+2,y+2,'\\',attr); /* print lower      '\\' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedn(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedo(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedP(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintToScreenN(x+1,y,hor,attr,2);    /* print uppper      '--' */
   PrintCharToScreen(x+3,y+1,ver,attr); /* print upper right '|'  */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedR(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintToScreenN(x+1,y,hor,attr,2);    /* print uppper      '--' */
   PrintCharToScreen(x+3,y+1,ver,attr); /* print upper right '|'  */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,2);  /* print middle      '--' */
   PrintCharToScreen(x+3,y+2,'\\',attr); /* print right '\\'  */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedr(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintToScreenN(x+1,y+1,hor,attr,1);  /* print middle      '--' */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedU(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+3,y+1,ver,attr); /* print upper right '|'  */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
   PrintCharToScreen(x,y+1,ver,attr);   /* print upper left  '|'  */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedY(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x+1,y+1,'\\',attr);  /* print uppper left  '\'  */
   PrintCharToScreen(x+3,y+1,'/',attr);  /* print upper right '/'   */
   PrintCharToScreen(x+2,y+1,hor,attr);  /* print middle      '-'   */
   PrintCharToScreen(x+2,y+2,ver,attr);  /* print lower       '|'   */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedMu(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+1,y+1,_MU,attr);
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedu(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x+3,y+2,ver,attr); /* print lower right '|'  */
   PrintToScreenN(x+1,y+2,hor,attr,2);  /* print lower       '__' */
   PrintCharToScreen(x,y+2,ver,attr);   /* print lower left  '|'  */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedl(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);    /* blank that particular LED */
   PrintCharToScreen(x+1,y+1,ver,attr); /* print upper '|'  */
   PrintCharToScreen(x+1,y+2,ver,attr); /* print lower '|'  */
   PrintCharToScreen(x+2,y+2,hor,attr); /* print lower '_'  */
 }
/*----------------------------------------------------------------------- */
 #pragma argsused
 void PrintLedx(int x,int y,unsigned attr,uchar ver,uchar hor)
 {
   PrintBlankLed(x,y,attr);     /* blank that particular LED */
   PrintCharToScreen(x+1,y+1,'\\',attr);  /* print upper '\'  */
   PrintCharToScreen(x+3,y+1,'/',attr);   /* print upper '/'  */
   PrintCharToScreen(x+1,y+2,'/',attr);   /* print lower '\'  */
   PrintCharToScreen(x+3,y+2,'\\',attr);  /* print lower '/'  */
 }
/*----------------------------------------------------------------------- */
 int  PrintOneLedSpecial(int x,int y,int value,unsigned attr)
 {
   switch(value)
   {
     case  _LED_DOT        :   PrintLedDot(x,y,attr);
                               break;
     case  _LED_HYPHEN     :   PrintLedHyphen(x,y,attr,'|','_');
                               break;
     case  _LED_G          :   PrintLedG(x,y,attr,'|','_');
                               break;
     case  _LED_H          :   PrintLedH(x,y,attr,'|','_');
                               break;
     case  _LED_L          :   PrintLedL(x,y,attr,'|','_');
                               break;
     case  _LED_t          :   PrintLedt(x,y,attr,'|','_');
                               break;
     case  _LED_N          :   PrintLedN(x,y,attr,'|','_');
                               break;
     case  _LED_n          :   PrintLedn(x,y,attr,'|','_');
                               break;
     case  _LED_o          :   PrintLedo(x,y,attr,'|','_');
                               break;
     case  _LED_P          :   PrintLedP(x,y,attr,'|','_');
                               break;
     case  _LED_R          :   PrintLedR(x,y,attr,'|','_');
                               break;
     case  _LED_r          :   PrintLedr(x,y,attr,'|','_');
                               break;
     case  _LED_U          :   PrintLedU(x,y,attr,'|','_');
                               break;
     case  _LED_Y          :   PrintLedY(x,y,attr,'|','_');
                               break;
     case  _LED_Mu         :   PrintLedMu(x,y,attr,'|','_');
                               break;
     case  _LED_u          :   PrintLedu(x,y,attr,'|','_');
                               break;
     case  _LED_l          :   PrintLedl(x,y,attr,'|','_');
                               break;
     case  _LED_x          :   PrintLedx(x,y,attr,'|','_');
                               break;
     case  LED_DOT         :   PrintLedDot(x,y,attr);
                               break;
     default               :   return BAD_SYSTEM_CALL;
   }
   return 1;
 }
/*----------------------------------------------------------------------- */
 int DisplayOneLed(int xpos,int ypos,int value,unsigned attr)
 {
   if(value==_LED_BLANK)
     return PrintBlankLed(xpos,ypos,attr);
   else if(value>=LED_DOT)
   {
     PrintOneLed(xpos,ypos,value|LED_DOT,attr,'|','_');
   }
   else if(value>_LED_BLANK)
    return PrintOneLedSpecial(xpos,ypos,value,attr);
   /* special characters like '.' 'R' etc */
   else return PrintOneLed(xpos,ypos,value,attr,'|','_');
   return 1;
 }
/*----------------------------------------------------------------------- */
 int DisplayStatusLed(void)
 {
   int i;
    for(i=0; i<MAX_STATUS_FIELDS ; i++)
      DisplayOneLed(LED_DISPLAY.x+i*LED_LEN+2,LED_DISPLAY.y+1,
               STATUS_FIELD(i),LED_DISPLAY.text_attr);
    return 1;
 }
/*----------------------------------------------------------------------- */
 int DisplayAddressLed(void)
 {
   int i;
    for(i=0; i<MAX_ADDR_FIELDS ; i++)
      DisplayOneLed(LED_DISPLAY.x+MAX_DATA_FIELDS*LED_LEN+i*LED_LEN+PATCH+1,
               LED_DISPLAY.y+1,ADDR_FIELD(i),LED_DISPLAY.text_attr);
    return 1;
 }
/*----------------------------------------------------------------------- */
 int DisplayDataLed(void)
 {
   int i;
    for(i=0; i<MAX_DATA_FIELDS ; i++)
      DisplayOneLed(LED_DISPLAY.x+(MAX_DATA_FIELDS+MAX_ADDR_FIELDS)*LED_LEN
      +i*LED_LEN+PATCH+4,LED_DISPLAY.y+1,DATA_FIELD(i),LED_DISPLAY.text_attr);
    return 1;
 }
/*----------------------------------------------------------------------- */
 int DisplayAllLeds(void)
 {
   DisplayStatusLed();
   DisplayAddressLed();
   DisplayDataLed();
   return 1;
 }
/* ---------------------------------------------------------------------- */
 int BlankStatusLed(void)
 {
   int i;
    for(i=0; i<MAX_STATUS_FIELDS; i++)
      STATUS_FIELD(i) = _LED_BLANK;  /* blank the status field */
   return DisplayStatusLed();
 }
/* ---------------------------------------------------------------------- */
 int BlankAddressLed(void)
 {
   int i;
     for(i=0; i<MAX_ADDR_FIELDS ; i++)
       ADDR_FIELD(i) = _LED_BLANK;     /* blank the address field */
       return DisplayAddressLed();
 }
/* ---------------------------------------------------------------------- */
 int BlankDataLed(void)
 {
   int i;
     for(i=0; i<MAX_DATA_FIELDS ; i++)
       DATA_FIELD(i) = _LED_BLANK;    /* blank the data field */
       return DisplayDataLed();
 }
/* ---------------------------------------------------------------------- */
 int BlankAllLeds(void)
 {
    BlankStatusLed();
    BlankAddressLed();
    BlankDataLed();
    return 1;
 }
/* ---------------------------------------------------------------------- */
 int NumTo7Seg(int num)
 {
   switch(num)
   {
      case  0     :  return _LED_0;
      case  1     :  return _LED_1;
      case  2     :  return _LED_2;
      case  3     :  return _LED_3;
      case  4     :  return _LED_4;
      case  5     :  return _LED_5;
      case  6     :  return _LED_6;
      case  7     :  return _LED_7;
      case  8     :  return _LED_8;
      case  9     :  return _LED_9;
      case  0xA   :  return _LED_A;
      case  0xB   :  return _LED_B;
      case  0xC   :  return _LED_C;
      case  0xD   :  return _LED_D;
      case  0xE   :  return _LED_E;
      case  0xF   :  return _LED_F;
      case  0x10  :  return _LED_BLANK;
      case  0x11  :  return _LED_DOT;
      case  0x12  :  return _LED_HYPHEN;
      case  0x13  :  return _LED_G;
      case  0x14  :  return _LED_H;
      case  0x15  :  return _LED_L;
      case  0x16  :  return _LED_t;
      case  0x17  :  return _LED_N;
      case  0x18  :  return _LED_n;
      case  0x19  :  return _LED_o;
      case  0x1A  :  return _LED_P;
      case  0x1B  :  return _LED_R;
      case  0x1C  :  return _LED_r;
      case  0x1D  :  return _LED_U;
      case  0x1E  :  return _LED_Y;
      case  0x1F  :  return _LED_Mu;
      case  0x20  :  return _LED_u;
      case  0x21  :  return _LED_l;
      case  0x26  :  return _LED_x;
      default     :  return BadSystemCall();
    }
 }
/* ---------------------------------------------------------------------- */
 int NumToSegment(unsigned int num)
 {
   /* this is used in the implementation of the system call
      a = 0d
      c = 00 to 03
      This function returns the equivalent code to light up one
      segment
   */
   int temp=0; /* initially everything is reset */

    num =~num;
    if(num & 16) temp |=LED_A;
    if(num & 32)  temp |=  LED_B;
    if(num & 64)  temp |=  LED_C;
    if(num & 128) temp |=  LED_D;
    if(num & 2)   temp |=  LED_E;
    if(num & 1)   temp |=  LED_F;
    if(num & 4)   temp |=  LED_G;
    if(num & 8)   temp |=  LED_DOT;
   return temp;
 }
/* ---------------------------------------------------------------------- */
#endif
