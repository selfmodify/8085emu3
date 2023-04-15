#ifndef _SYMBOLTABLE_H_
 #define _SYMBOLTABLE_H_

 /* functions which manipulate the symbol table */

/*------------------------------------------------------------------------*/
 void InitSymbolTable(void)
 {
   SYM_TABLE().max = 0;
 }
/*------------------------------------------------------------------------*/
 int FindInTable(char *s)
 {
  static int i;
   for(i=0; i<SYM_TABLE().max ; i++)
    if(strcmpi(SYM_TABLE().entry[i].name,s)==0) return i;
   return NOT_FOUND;
 }
/*------------------------------------------------------------------------*/
 int StoreSymbol(char *s)
 {
   if(FindInTable(s)!=NOT_FOUND) return DUPLICATE_LABEL;
   /* found an existing label, hence an error */
   if(SYM_TABLE().max>=TABLE_LENGTH)
    return TABLE_FULL;
   strncpy(SYM_TABLE().entry[SYM_TABLE().max].name,s,LABEL_LEN);
   SYM_TABLE().entry[SYM_TABLE().max++].addr  = PTR();
   return SYMBOL_STORED;
 }
/*------------------------------------------------------------------------*/
 int FindSymbols(char *s)
 {
   /* find the symbols and store them in the symbol table */
  int got;  /* token number obtained */
  int incr;  /* used to increment 'PTR()' */
  int x;

    got=InitToken(s);
    if(IsComment()==COMMENT)   return COMMENTS;
     /* got the starting of a one line comment */
    /* if it is not a comment it should be a directive or an instruction
       or a label */
    if((x=IsValidDirective())<0 || x==CORRECT_DIRECTIVE)   return x;
    if((incr=IsValidInstruction())>0)
    {
       PTR() += incr;
       return VALID_INSTRUCTION;
    }
    /* if it was an instruction, then return */
    if(got==EOI || got==EOLN) return got;
    if(got!=IDENTIFIER) return SYNTAX_ERROR;
    if(Advance(0)!=COLON)  return COLON_EXPECTED;
    got = StoreSymbol(LAST());
    return got;
 }
/*------------------------------------------------------------------------*/
 long StoreSymbolsInTable( FILE *fp)
 {
  int got;
  unsigned lines_assembled=0; /* number of lines assembled */

   for(/* InitMachine(m)*/ SYM_TABLE().max = 0  ;        ;   )
   {
     if(CURRENT()==EOLN || CURRENT()==EOI)
     {
       /* This means buffer is empty, hence read another line */
       if(fgets(BUFFER(),LINE_LENGTH,fp)==NULL) break;
       STRING() = BUFFER();
       LINE_NUMBER()++;  /* increment the line number */
     }
     if((got=FindSymbols(STRING()))<0)
           return got;
   /*
      there was a syntax error but ignore it, because this same error
      will be caught in the next pass which will result in two error
      messages for the same error.
      The function  'SetAndPrintError(got)' can be used to print the
      error
   */
     else  if(got!=SYMBOL_STORED)
     {
       if(got==VALID_INSTRUCTION) ++lines_assembled;
       while(!((got=Advance(0))==EOLN || got==EOI))
                    ;
     }
   /* Since it is a valid directive or instruction skip till end of line */
   }
   /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   if(GET_STATUS() & WARNING)
   {
      SET_STATUS(SEVERE_ERROR);
      return 0;
   } I don't think the error status will ever be set in this pass
      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   */
   return lines_assembled;
 }

#endif