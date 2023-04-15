#ifndef _DIRECTIVE_H_
 #define _DIRECTIVE_H_

 /* Functions to parse the various directives in an 8085 assembly language
    file
 */
/*------------------------------------------------------------------------*/
 int OrgDirective(void)
 {
  long x;
   if(Advance(0)!=NUMBER) return ILLEGAL_DIRECTIVE;
   if((x=StrToNum()) > LARGEST_ORG)
    return LARGE_DIRECTIVE; /* the number specified was too large */
   else if(x==__BAD_NUMBER_FORMAT) return BAD_NUMBER_FORMAT;
   /* you specified a '8' in an octal number. etc ... */
   PTR()   = (word) x;
   /* this is where the next instruction will be placed */
   return CORRECT_DIRECTIVE;
 }
/*------------------------------------------------------------------------*/
 int KickOffDirective(void)
 {
  long x;
   if(Advance(0)!=NUMBER) return ILLEGAL_DIRECTIVE;
   if((x=StrToNum()) > LARGEST_ORG)
    return LARGE_DIRECTIVE; /* the number specified was too large */
   else if(x==__BAD_NUMBER_FORMAT) return BAD_NUMBER_FORMAT;
   /* you specified a '8' in an octal number. etc ... */
   KIT->cpu.r.ip   =  (word)x;
   /* this is where your program will start */
   return CORRECT_DIRECTIVE;
 }
/*------------------------------------------------------------------------*/
 int SetByteDirective(void)
 {
   /*  this directive moves a word or byte of data to a memory location */
  long x;
  long y;

   if(Advance(0)!=NUMBER) return ILLEGAL_DIRECTIVE;
   if((x=StrToNum()) > LARGEST_ORG)
     return LARGE_DIRECTIVE; /* the address specified was too large */
   if(Advance(0)!=COMMA) return COMMA_EXPECTED;
   if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
   if((y=StrToNum()) > MAX_INT) return LARGE_NUMBER;
   SetMemByte((word)x,(uchar)y);
   return CORRECT_DIRECTIVE;
 }
/*------------------------------------------------------------------------*/
 int SetWordDirective(void)
 {
   /*  this directive moves a word or byte of data to a memory location */
  long x;
  long y;

   if(Advance(0)!=NUMBER) return ILLEGAL_DIRECTIVE;
   if((x=StrToNum()) > LARGEST_ORG)
     return LARGE_DIRECTIVE; /* the address specified was too large */
   if(Advance(0)!=COMMA) return COMMA_EXPECTED;
   if(Advance(0)!=NUMBER) return NUMBER_EXPECT;
   if((y=StrToNum()) > DOUBLE_INT) return LARGE_NUMBER;
   SetMemWord((word)x,(word)y);
   return CORRECT_DIRECTIVE;
 }
/*------------------------------------------------------------------------*/
 int IsADirective(char *s)
 {
   if(strcmpi(s,"org")==0)
     return ORG_DIRECTIVE;
   if(strcmpi(s,"kickoff")==0)
    return KICKOFF_DIRECTIVE;
   if(strcmpi(s,"SetWord")==0)
     return SETWORD_DIRECTIVE;
   if(strcmpi(s,"SetByte")==0)
    return SETBYTE_DIRECTIVE;
   /* if it is not "org" then it is not a directive */
   return 0;
 }
/*------------------------------------------------------------------------*/
 int IsValidDirective(void)
 {
  int x;
   switch(x=IsADirective(TOKEN()))
   {
     case ORG_DIRECTIVE       : return OrgDirective();
     case KICKOFF_DIRECTIVE   :
     case SETWORD_DIRECTIVE   :
     case SETBYTE_DIRECTIVE   : return CORRECT_DIRECTIVE;
     default                  : return x;
   }
 }
/*------------------------------------------------------------------------*/
 int  IsDirective(void)
 {
   switch(IsADirective(TOKEN()))
   {
     case ORG_DIRECTIVE         :  return OrgDirective();
     case KICKOFF_DIRECTIVE     :  return KickOffDirective();
     case SETBYTE_DIRECTIVE     :  return SetByteDirective();
     case SETWORD_DIRECTIVE     :  return SetWordDirective();
     default                    :  return 0;
   }
 }

#endif
