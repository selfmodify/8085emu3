#ifndef _LEX_H_
 #define _LEX_H_

 /* low level parsing routines are included in this file */

 #define IsNumSuffix(x)   (x=='O' || x=='H' || x== 'I'  || x=='#')
 #define _ISALNUM(x)      (isalnum(x) || x=='_')
 #define _ISALPHA(x)      (isalpha(x) || x=='_')

 /* number suffixes which can follow a number to indicate the base of the
    number
    O - Octal Number
    H - Hexadecimal
    I - Binary number.
    # - Decimal number.
 */

/*-----------------------------------------------------------------------*/
 int NextToken(void)
 {
   int ch;
   int i;

   if(STRING()==NULL || *(STRING())=='\0') return EOI;
   while((ch=*(STRING()))==' ' || ch=='\t')
      ++(STRING());
   if(ch=='\n')
   {
     ++STRING();
     return EOLN;
   }
   TOKEN()[0] = ch;
   TOKEN()[1] = 0;
   TOKEN()[TOKEN_SIZE] ='\0';
   if(_ISALPHA(*(STRING())))
   {
     for(i=0 ; _ISALNUM(*(STRING())) && i<TOKEN_SIZE ;
             i++,STRING()++)
     TOKEN()[i] = *(STRING());
     TOKEN()[i] =0;
     return IDENTIFIER;
   }
   if(isxdigit(*(STRING())))
   {
     while(*STRING()=='0')
      ++STRING();  /* skip leading zeroes */

     for(i=0 ; isxdigit(*(STRING())) && i<TOKEN_SIZE ;
             i++,STRING()++)
       TOKEN()[i] = *(STRING());

     if(IsNumSuffix(toupper(*STRING())))
       TOKEN()[i++] = *(STRING()++);
     TOKEN()[i] =0;
     return NUMBER;
   }
   ch = *TOKEN();
   if(ch ==',')
   {
     ++STRING();
     return COMMA;
   }
   if(ch==';' || ch ==':')
   {
     ++STRING();
     return ch == ';' ? SEMI : COLON;
   }
   ++(STRING());
   return ERROR;
 }
/*------------------------------------------------------------------------*/
 int NextToken_1(void)
 {
   /* same as NextToken but advance only by one byte */
   int ch;

   if(STRING()==NULL || *(STRING())=='\0') return EOI;
   while((ch=*(STRING()))==' ' || ch=='\t')
      ++(STRING());
   ++(STRING());
   if(ch=='\n')  return EOLN;
   TOKEN()[0] = ch;
   TOKEN()[1] = 0;
   TOKEN()[TOKEN_SIZE] ='\0';
   if(isalpha(ch)) return IDENTIFIER;
   if(isxdigit(ch)) return NUMBER;
   if(ch ==',')  return COMMA;
   if(ch==';') return SEMI;
   else if(ch ==':') return COLON;
   return ERROR;
 }
/*------------------------------------------------------------------------*/
 int  InitToken(char *s)
 {
   STRING()       = s;
   TOKEN()[0]   = 0;
   return CURRENT()=NextToken();
 }
/*------------------------------------------------------------------------*/
 int Advance(int x)
 {
  /* if x==0 advance to the next token
     else advance by one byte
  */
   strcpy(LAST(),TOKEN()); /* save the last obtained token */
   return   (CURRENT()= (x==0 ?  NextToken() : NextToken_1()));
 }
/*------------------------------------------------------------------------*/
 long StringToNum(char *s)
 {
   long l=DOUBLE_INT+1;
   char *endptr;

    l = strtol(s,&endptr,2); /* first check for base '2' */
    if(*endptr=='i') return l;
    l = strtol(s,&endptr,DEFAULT_BASE);
    if(endptr==NULL) return l;
    switch(toupper(*endptr))
    {
      case 'H'      :    l=strtol(s,&endptr,16);
                         break;
      case 'I'      :    l=strtol(s,&endptr,2);
                         if(isxdigit(*endptr)) return __BAD_NUMBER_FORMAT;
                         break;
      case 'O'      :    l=strtol(s,&endptr,8);
                         if(isxdigit(*endptr)) return __BAD_NUMBER_FORMAT;
                         break;
      case '#'      :    l=strtol(s,&endptr,10);
                         if(isxdigit(*endptr)) return __BAD_NUMBER_FORMAT;
                         break;
      default       :    if(*endptr==';' || *endptr=='\0') return l;
                         else return __BAD_NUMBER_FORMAT;
                         /* a number can be followed by prefixes or a
                            semicolon, otherwise it is an error !!
                         */
    }
    return l;
 }
/*------------------------------------------------------------------------*/
 long StrToNum(void)
 {
   return StringToNum(TOKEN());
 }
/*------------------------------------------------------------------------*/
 int InsertMachineCode(uchar code)
 {
   int x;
   /*   if(code>MAX_INSTRING()UCTIONS) return ERROR;  */
   if((x=SetMemByte(PTR()++,code))<0) return x;
   return code;
 }
/*------------------------------------------------------------------------*/
 int InsertCodeAnd8Bit(uchar code,char value)
 {
  int x;
   if((x=SetMemByte(PTR()++,code))<0) return x;
   if((x=SetMemByte(PTR()++,value))<0) return x; /* immediate 8 bit value */
   return code;
 }
/*------------------------------------------------------------------------*/
 int InsertCodeAnd16Bit(uchar code,unsigned value)
 {
  int  x;

   if((x=SetMemByte(PTR()++,code))<0) return x;
   SetMemWord(PTR(),value);
   PTR()   += 2;
   return code;
 }
/*------------------------------------------------------------------------*/
 int IsAnInstruction(void)
 {
   int i;
    for(i=0; *mnemonic[i].name ; i++)
      if(strcmpi(TOKEN(),mnemonic[i].name)==0)
          return i;
   return -1;
 }
/*------------------------------------------------------------------------*/
 int IsValidInstruction(void)
 {
   /* integer version of 'IsAnInstruction(void)'
      This function returns -1 if not an instruction else returns its
      length
   */
   int i;
    for(i=0; *mnemonic[i].name ; i++)
      if(strcmpi(TOKEN(),mnemonic[i].name)==0)
         return mnemonic[i].len;
   return -1;
 }
/*------------------------------------------------------------------------*/
 int IsRegs(char *s)
 {  /* returns true if the argument is the name of a valid register */
   int ch;
   ch = toupper(*s);
   return ch=='A' || ch=='B' || ch=='C' || ch=='D' || ch=='E' ||
          ch=='H' || ch=='L' || (strcmpi(s,"SP")==0) || (strcmpi(s,"PSW")==0)
          ?  1  : 0;
 }
/*------------------------------------------------------------------------*/
 int IsMem(char *s)
 {
   return strcmpi(s,"M")==0 ? 1 : 0;
 }
/*------------------------------------------------------------------------*/
 int RegisterNumber(char *x)
 {
   switch(toupper(*x))
   {
     case 'B'   :       if(*(x+1)!='\0') return -1;
                        return _B;
     case 'C'   :       if(*(x+1)!='\0') return -1;
                        return _C;
     case 'D'   :       if(*(x+1)!='\0') return -1;
                        return _D;
     case 'E'   :       if(*(x+1)!='\0') return -1;
                        return _E;
     case 'H'   :       if(*(x+1)!='\0') return -1;
                        return _H;
     case 'L'   :       if(*(x+1)!='\0') return -1;
                        return _L;
     case 'M'   :       if(*(x+1)!='\0') return -1;
                        return _M;
     case 'A'   :       if(*(x+1)!='\0') return -1;
                        return _A;
     default    :       return strcmpi(x,"PSW")==0 ? _PSW :
                        strcmpi(x,"SP")==0 ? _SP : -1;
   }
 }
/*------------------------------------------------------------------------*/
 int RegNumber(void)
 {
   return RegisterNumber(TOKEN());
 }
/*------------------------------------------------------------------------*/
 int Common(void)
 {
   /* do the common parsing of testing if the first variable is a register
      or memory location and that following is a comma, if not return 0 */
   /* Currently this function is not used */

   if(Advance(0)!=IDENTIFIER) return REG_OR_MEM_EXPECT;
   /* should be an identifier to be the name of a register */
   if(!IsRegs(TOKEN()) && !IsMem(TOKEN())) return REG_OR_MEM_EXPECT;
   /* it was an identifier but was not a valid register or memory location*/
   if(Advance(0)!=COMMA) return COMMA_EXPECTED;  /* should be a ',' */
   return 1;
 }
/*------------------------------------------------------------------------*/
 int Displacement(int r1,int r2)
 {
  /* the machine codes for the instructions are in the increasing order
     according to the registers they use.
     The highest priority being given to 'B' and lowest to 'A'.
     eg:- MOV inSTRING()uctions start at 0x40
          hence MOV B,B has a value 0x40
          but   MOV B,C has a value 0x41
          and   MOV B,D has a value 0x42
 */
   return r1*8 + r2;
 }
/*------------------------------------------------------------------------*/
 int IsComment(void)
 {
  int got;
   if(CURRENT()!=SEMI) return 0;
   while((got=Advance(0))!=EOLN && (got!=EOI))
                 ;
   return COMMENT;
 }
/*------------------------------------------------------------------------*/
 int SetLex(lex_struct *l)
 {  /* make 'state' point to l, so that the all operations will now be
       performed on l
    */
   LEX_STRUCT = *l;
   return 1;
 }
/*------------------------------------------------------------------------*/
 int InitLexStruct(lex_struct *l)
 {
   l->line_number = 0;
   l->str         = NULL;
   l->token[0]    = 0;
   l->last[0]     = 0;
   l->current     = EOI;
   SetLex(l);
   return 1;
 }
/*------------------------------------------------------------------------*/
#endif