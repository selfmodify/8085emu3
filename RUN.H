#ifndef __RUN_H__
 #define __RUN_H__

 /* These functions run the machine and allow online editing of data
    and instructions
 */

/*------------------------------------------------------------------------*/
 int RunTimeParse(void)
 {
   int ret;
   int x;

    if((ret = IsInstruction())<0) return ret;
    if((x=Advance(0))==EOI || x==EOLN) return ret;
    return EXTRA_INPUT;
 }
/*------------------------------------------------------------------------*/
 int  ProcessInterrupts(void)
 {
  int val;
   if(INTERRUPTED())   /* 5.5, 6.5, 7.5 or TRAP interrupt occured */
   {
     val = PerformInterrupt(INTERRUPT_NUMBER());
     INTERRUPTED() = 0;
   }
   return val; /* return 1 if you were able to process the 'isr' */
 }
/*------------------------------------------------------------------------*/
 int IsABreakPoint(word addr)
 {
   int i;

    for(i=0; i<BREAK_PT_CTR() ; i++)
      if(BREAK_POINT(i)==addr) return i;
    return -1;
 }
/*------------------------------------------------------------------------*/
 void DeInstallBreakPoint(int index)
 {
   int i;
    for(i=index; i<BREAK_PT_CTR()-1 ; i++)
        BREAK_POINT(i) = BREAK_POINT(i+1);
    --BREAK_PT_CTR();
 }
/*------------------------------------------------------------------------*/
 int InstallBreakPoint(word addr)
 {
  int x;
  char s[257];
   if(BREAK_PT_CTR() >= MAX_BREAK_POINTS)
   {
     /* too many break points */
     sprintf(s,"   Too many Break points (Max break points %d)"
                   ,MAX_BREAK_POINTS);
     DisplayError(s);
     return 0;
   }
   if((x=IsABreakPoint(addr))!=-1)
   {
     DeInstallBreakPoint(x);  /* toggle break point */
     return 2;
   }
   BREAK_POINT(BREAK_PT_CTR()++)  =  addr;
   if(addr == GetIP()) LAST_BREAK_POINT() = addr;
   return 1;
 }
/*------------------------------------------------------------------------*/
 int ExecuteCurrentInstruction(void)
 {
   int x;
   static int last_was_interrupt=0;
   /* an interrupt routine was serviced during the last call to this
      function
   */

    /* geninterrupt(201); */
    if(!last_was_interrupt)  /*first process interrupts */
      if((last_was_interrupt = ProcessInterrupts())==1) return 0;
    /* 'last_was_interrupt' is set if processor entered a interrupt routine
       if the above check is not done then it will not be possible to
       trace the first instruction of any 'isr'
    */
    OLD_IP() = GetIP();
    last_was_interrupt = 0;
    if(((x=IsABreakPoint(GetIP()))!=-1) && (RUN() || STEP_OVER()))
     if(!(LAST_BREAK_POINT()==BREAK_POINT(x)))
     {
       LAST_BREAK_POINT() = BREAK_POINT(x);
       return RUN()=STEP_OVER()=0; /* reset the 'run' and 'step over' flag */
     }
     x = (*PTR_TO_SIMU())();
     LAST_BREAK_POINT() = 0; /* reset last break point */
     return x;
 }
/*------------------------------------------------------------------------*/
 int MoveMemDumpPointer(int c)
 {
   /* change the value of 'cp' (current pointer) of memory dump */
   switch(c)
   {
     case UP         :   if(MEM_DUMP_BOX().cp==MEM_DUMP_BOX().start)
                         { /* if you have reached top of box */
                           if(MEM_DUMP_BOX().start==0) break;
                           else  MEM_DUMP_BOX().cp = --MEM_DUMP_BOX().start;
                         }
                         else --MEM_DUMP_BOX().cp;
/*                         if(MEM_DUMP_BOX().start>MAIN_MEMORY-1)
                         MEM_DUMP_BOX().start = MEM_DUMP_BOX().cp=MAIN_MEMORY-1;
*/
                         break;
     case DOWN       :   PerformMemDumpDown();
                         break;
     case PAGE_UP    :   if((long)MEM_DUMP_BOX().start - MEM_DUMP_BOX().b.height <0)
                          MEM_DUMP_BOX().start = 0;
                         else MEM_DUMP_BOX().start -= MEM_DUMP_BOX().b.height-1;
                         MEM_DUMP_BOX().cp =  MEM_DUMP_BOX().start;
                         break;
     case PAGE_DOWN  :   if((long)MEM_DUMP_BOX().start + 2l*MEM_DUMP_BOX().b.height >=
                               MAIN_MEMORY)
                         MEM_DUMP_BOX().start = MAIN_MEMORY - MEM_DUMP_BOX().b.height+1;
                         else MEM_DUMP_BOX().start += (MEM_DUMP_BOX().b.height-1);
                         MEM_DUMP_BOX().cp =  MEM_DUMP_BOX().start;
                         break;
     case HOME       :   MEM_DUMP_BOX().cp = MEM_DUMP_BOX().start = 0;
                         break;
     case END        :   MEM_DUMP_BOX().start = MAIN_MEMORY - MEM_DUMP_BOX().b.height+1;
                         MEM_DUMP_BOX().cp = MAIN_MEMORY-1;
                         break;
     case F10        :   DisplayProjectGroupName();
                         break;
     case F11        :
     case CTRL_A     :   MEM_DUMP_BOX().cp = MEM_DUMP_BOX().start=GetIP();
      /* goto 'IP' */    break;
     default         :   return 0;
   }
  return 1;
 }
/*------------------------------------------------------------------------*/
 int MoveCodeDumpPointer(int c)
 {
   /* change the value of 'cp' (current pointer) of code dump */
   /* CODE_BOX().start = GetIP(); */
   word i;

   switch(c)
   {
     case UP         :  PerformCodeUp();
                        break;
     case DOWN       :  PerformCodeDown();
                        break;
     case PAGE_UP    :  PerformCodePageUp();
                        CODE_BOX().cp =  CODE_BOX().start;
                        break;
     case PAGE_DOWN  :  for(i=0; i < CODE_BOX().b.height-1; i++ )
                         if((long)CODE_BOX().start+CODE_BOX().b.height
                             > MAIN_MEMORY)  break;
                         else
                          CODE_BOX().start = GetNearestNextAddr(CODE_BOX().start);
                        CODE_BOX().cp =  CODE_BOX().start;
                        break;
     case HOME       :  CODE_BOX().cp = CODE_BOX().start = 0;
                        break;
     case END        :  PerformCodeEnd();
                       /* CODE_BOX().cp =  GetNearestPrevAddr(MAIN_MEMORY-1);
                        CODE_BOX().cp =  GetNearestNextAddr(CODE_BOX().cp);
                        */
                        break;
     case F11        :
     case CTRL_A     :  i = GetNearestPrevAddr(GetIP());
     /* goto 'IP' */    if(GetNearestNextAddr(i)==GetIP())
                           CODE_BOX().cp =  CODE_BOX().start = GetIP();
                        else CODE_BOX().cp =  CODE_BOX().start = i;
                        break;
     default         :  return 0;
   }
  return 1;
 }
/*------------------------------------------------------------------------*/
 int MoveRegisterDumpPointer(int ch)
 {
   /* change the value of 'cp' (current pointer) of 'register' dump */
   switch(ch)
   {
     case UP         :  if(REG_DISPLAY_BOX().cp==0)
                        REG_DISPLAY_BOX().cp = REG_DISPLAY_BOX().b.height-2;
                        else  REG_DISPLAY_BOX().cp--;
                        break;
    case DOWN        :  if(REG_DISPLAY_BOX().cp>=REG_DISPLAY_BOX().b.height-2)
                        {
                          REG_DISPLAY_BOX().cp = 0;
                          break;
                        }
                        REG_DISPLAY_BOX().cp++;
                        break;
    case PAGE_UP     :
    case HOME        :   REG_DISPLAY_BOX().cp = 0;
                         break;

    case PAGE_DOWN   :
    case END         :   REG_DISPLAY_BOX().cp = REG_DISPLAY_BOX().b.height-2;
                         break;
   }
   return 1;
 }
/*------------------------------------------------------------------------*/
 int MoveFlagDumpPointer(int ch)
 {
   /* change the value of 'cp' (current pointer) of 'register' dump */
   switch(ch)
   {
     case UP         :  if(FLAG_BOX().cp==0)
                        FLAG_BOX().cp=FLAG_BOX().b.height-2;
                        else FLAG_BOX().cp--;
                        break;
    case DOWN        :  if(FLAG_BOX().cp>=FLAG_BOX().b.height-2)
                          FLAG_BOX().cp=0;
                        else FLAG_BOX().cp++;
                        break;
    case PAGE_UP     :
    case HOME        :   FLAG_BOX().cp = 0;
                         break;

    case PAGE_DOWN   :
    case END         :   FLAG_BOX().cp = FLAG_BOX().b.height-2;
                         break;
   }
   return 1;
 }
/*------------------------------------------------------------------------*/
 void Adjust(void)
 {
   /* if 'IP' is not within the 'code' box then this function sets the
      value of the 'start' pointer of the 'code' box to 'IP' hence making
      the code that is being traced visible
   */
  word i,j;

   if(CODE_BOX().start > GetIP())
   {
      CODE_BOX().start = GetIP();
      return;
   }
   for(i=0,j=CODE_BOX().start; j<MAIN_MEMORY && i<CODE_BOX().b.height-1; i++)
      if((j += GetInstructionLen(j)) > GetIP()) return;
   CODE_BOX().start = GetIP();
 }
/*------------------------------------------------------------------------*/
 void AdjustCodeStart(void)
 {
   word i;

   Adjust();
   /* the following lines are added to correct effects of self modifying
      code
   */
   i = GetNearestPrevAddr(CODE_BOX().start);
   if(CODE_BOX().start!=GetNearestNextAddr(i)) /* no change in code */
   CODE_BOX().start = i;
 }
/*------------------------------------------------------------------------*/
 void SetNewVectors(void)
 {
   /* set new values for vectors for 'TRAP_VECTOR' and 'RST_5_5 etc'
      vectors in the IVT
   */
   setvect(TRAP_INTR_VECTOR,TrapIntrFunc);
   setvect(RST_5_5_INTR_VECTOR,Rst_5_5_Func);
   setvect(RST_6_5_INTR_VECTOR,Rst_6_5_Func);
   setvect(RST_7_5_INTR_VECTOR,Rst_7_5_Func);
 }
/*-----------------------------------------------------------------------*/
 int Trace(void)
 {
    PrintRunning();      /* print the running message in the menu bar*/
    INCREMENT()    = ExecuteCurrentInstruction();
    SetIP(GetIP()+INCREMENT());
    return 1;
 }
/*------------------------------------------------------------------------*/
 int StepOver(void)
 {
   int ch=0;

    PrintStatusLine((uchar *)\
          "   F7 - Single step mode        Alt+S - Halt      Alt+X  Quit");
    STEP_OVER() = 0;
    /* fool the 'ExecuteCurrentInstruction'  into thinking that you are
       just tracing and not stepping over
    */
    PrintRunning();      /* print the running message in the menu bar*/
    INCREMENT()    = ExecuteCurrentInstruction();
    STEP_OVER() = 1;  /* again set that you are stepping over */
    if(GET_STATUS() & JUST_CALLED)
    {
     /* do remaining only if the instruction was a  'CALL' */
      STEP_OVER_IP() = OLD_IP() + CALL_LEN;
      CLEAR_STATUS(JUST_CALLED); /* reset the 'JUST CALLED' flag */
      while(STEP_OVER() && !SevereErrorsDuringRun()
        && !(GET_STATUS() & QUIT))
      {
        if((ch=GetTheChar(POLLING))==QUIT_KEY || ch==F7 || ch==STOP_KEY)
           break;
        else fflush(stdin);
        SetIP(GetIP()+INCREMENT());
        PrintRegisters();
        PrintFlags();
        if((GET_STATUS() & JUST_RETURNED) && (STEP_OVER_IP()==GetIP()))
           break; /* encounter a corresponding 'ret' instruction */
        CODE()        = GetIPByte();
        PTR_TO_SIMU() = mot[CODE()].Simulate;
        INCREMENT()   = ExecuteCurrentInstruction();
        if(!STEP_OVER())
        {
          DefaultStatusLine();
          return 0;
        }
      }
    }
    DefaultStatusLine();
    if(ch!=QUIT_KEY && ch!=STOP_KEY) SetIP(GetIP()+INCREMENT());
    return ch;
 }
/*------------------------------------------------------------------------*/
 int Control_F9(void)
 {
   int ch=0;

  /* run the machine continuously until the user hits 'CTRL_F9' or the
     machine encounters a 'hlt' instruction. The difference between this
     function and 'RunContinuously' is that 'RunContinuously' recalculates
     code data and displays it which makes it very slow for large
     values of 'IP'
  */
     PrintStatusLine((uchar *)\
      "   F7 - Single step mode        Alt+S - Halt      Alt+X  Quit");
     PrintRunning();      /* print the running message in the menu bar*/
     while(!SevereErrorsDuringRun()  && !(GET_STATUS() & QUIT))
     {
       INCREMENT()   = ExecuteCurrentInstruction();
       if(!RUN()) break;
       SetIP(GetIP()+INCREMENT());
       CODE()        = GetIPByte();
       PTR_TO_SIMU() = mot[CODE()].Simulate;
       if((ch=GetTheChar(POLLING))==QUIT_KEY || ch==F7
            || ch==STOP_KEY) break;
       else fflush(stdin);  /* remove the key from the queue */
       PrintRegisters();
       PrintFlags();
     }
   DefaultStatusLine();
   return ch;
 }
/*------------------------------------------------------------------------*/
 int RunContinuously(void)
 {
   int ch=0;
  /* run the machine continuously until the user hits 'F9' or the
     machine encounters a 'hlt' instruction. The difference between this
     function and 'RunContinuously' is that 'RunContinuously' also
     displays code, which makes it very slow for large values of 'IP'
  */
     PrintStatusLine((uchar *)\
      "   F7 - Single step mode        Alt+S - Halt      Alt+X  Quit");
     PrintRunning();      /* print the running message in the menu bar*/
     while(!SevereErrorsDuringRun()  && !(GET_STATUS() & QUIT))
     {
       INCREMENT()   = ExecuteCurrentInstruction();
       if(!RUN()) break;
       SetIP(GetIP()+INCREMENT());
       CODE()        = GetIPByte();
       PTR_TO_SIMU() = mot[CODE()].Simulate;
       AdjustCodeStart();    /* adjust 'start' of code box */
       if((ch=GetTheChar(POLLING))==QUIT_KEY || ch==F7 || ch==STOP_KEY)
            break;
       else fflush(stdin);  /* remove the key from the queue */
       PrintRegisters();
       PrintCode();       /* display the instructions */
       PrintMemoryDump();   /* display memory dump */
       PrintFlags();
       PrintStackDump();
     }
   DefaultStatusLine();
   return ch;
 }
/*------------------------------------------------------------------------*/
 int GoToCursor(word addr)
 {
   int ch=0;

    PrintStatusLine((uchar *)\
          "   F7 - Single step mode        Alt+S - Stop      Alt+X  Quit");
    STEP_OVER()      = 1;
    /* do remaining only if the instruction was a  'CALL' */
    STEP_OVER_IP() = addr;
    PrintRunning();      /* print the running message in the menu bar*/
    INCREMENT()    = ExecuteCurrentInstruction();
    SetIP(GetIP()+INCREMENT());
    while(STEP_OVER() && !SevereErrorsDuringRun()  && !(GET_STATUS()&QUIT))
    {
      if((ch=GetTheChar(POLLING))==QUIT_KEY || ch==F7 || ch==STOP_KEY)
             break;
      else fflush(stdin);
      PrintRegisters();
      PrintFlags();
      if(STEP_OVER_IP()==GetIP())
         break;
      CODE()        = GetIPByte();
      PTR_TO_SIMU() = mot[CODE()].Simulate;
      INCREMENT()   = ExecuteCurrentInstruction();
      SetIP(GetIP()+INCREMENT());
      if(!STEP_OVER()) return 0;
    }
    DefaultStatusLine();
    return ch;
 }
/*------------------------------------------------------------------------*/
 int ReadInstruction(int ch)
 {
   /* read an instruction from command line and insert it at point
      'CODE_BOX().cp'
   */
   char s[257];
   char save[3];  /* maximum length of an instruction is 3 bytes */
   int   i;
   int   ret;

    s[0] = ch;
    s[1] = '\0';
    for(i=0 ; i<3 ; i++)
      save[i]  = GetMemByte(CODE_BOX().cp+i);
    /* save the 3 bytes following 'cp' which will be destroyed while
       parsing.  This would happen even if the instruction entered
       was incorrect
    */
    PTR()=CODE_BOX().cp;
    if(StandardInputBox(" Enter new instruction to assemble ",s)==-1)
      return 0;
    InitToken(s);
    if((ret=RunTimeParse())<0)
    {
      if(ret==-1) strcpy(s," Invalid Instruction ");
      else sprintf(s,"  %s ",error_msg[-(ret+1)]);
      /* this wastes time, but looks good */
      /* error_msg is decalred in 'myerror.h' */
      /* DisplayError(s);*/
      StandardErrorMessageBox(s);
      for(i=0 ; i<3 ; i++)
        SetMemByte(CODE_BOX().cp+i,save[i]);
      return -1;
    }
    PerformCodeDown();
    return 1;
 }
/*------------------------------------------------------------------------*/
 int ReadMemDumpNumber(int ch)
 {
   char  s[257];
   long  ret;
   word   i,j;
   int    k;

    s[0] = ch;
    s[1] = '\0';
    if(StandardInputBox(" Enter new value ",s)==-1)
      return 0;
    if((ret=StringToNum(s))<0)
    {
      ret = ret==__BAD_NUMBER_FORMAT ? BAD_NUMBER_FORMAT : ret;
      StandardErrorMessageBox(error_msg[(int)(-(ret+1))]);
      return -1;
    }
    else if(ret>DOUBLE_INT)
    {
      StandardErrorMessageBox("Number too large");
      return -1;
    }
    else
    {
      if(ret<=MAX_INT) SetMemByte(MEM_DUMP_BOX().cp,(uchar)ret);
      else
      {
        SetMemWord(MEM_DUMP_BOX().cp,(word)(ret & 0xffff));
        PerformMemDumpDown();
        /* since a 'word' data has been entered the 'cp' should move down
           twice
        */
      }
    }
    /* AdjustCodeStart(); */
    /* inserting a number into the  'ram' changes the instruction, this
       forces recalculation of 'start' value of code box.
       This is what is done below
    */
    i = GetNearestPrevAddr(CODE_BOX().start);
    if(CODE_BOX().start!=GetNearestNextAddr(i)) /* no change in code */
    CODE_BOX().start = i;
    for(j=i=CODE_BOX().start,k=0 ;i<MAIN_MEMORY-1
         && k<CODE_BOX().b.height-1; i+=GetInstructionLen(i), k++)
                     j=i; /* save the previous address */

    if(CODE_BOX().cp>=i) /* the 'cp' is outside the display window */
         CODE_BOX().cp = j; /* bring the 'cp' within the display window */
    PerformMemDumpDown();
    return 1;
 }
/*------------------------------------------------------------------------*/
 int SetNewValueForRegister(dword ret)
 {
   char *msg=" Number too large ";
     switch(REG_DISPLAY_BOX().cp)
     {
       case   0   :   if(ret>MAX_INT)  StandardErrorMessageBox(msg);
                      else SetA((uchar)ret);
                      break;
       case   1   :   if(ret>MAX_INT)
                      {
                        SetB((uchar)(ret>>8));
                        SetC((uchar)ret);
                      }
                      else SetB((uchar)ret);
                      break;
       case   2   :   if(ret>MAX_INT)  StandardErrorMessageBox(msg);
                      else SetC((uchar)ret);
                      break;
       case   3   :   if(ret>MAX_INT)
                      {
                        SetD((uchar)(ret>>8));
                        SetE((uchar)ret);
                      }
                      else SetD((uchar)ret);
                      break;
       case   4   :   if(ret>MAX_INT)  StandardErrorMessageBox(msg);
                      else SetE((uchar)ret);
                      break;
       case   5   :   if(ret>MAX_INT)
                      {
                        SetH((uchar)(ret>>8));
                        SetL((uchar)ret);
                      }
                      else SetH((uchar)ret);
                      break;
       case   6   :   if(ret>MAX_INT)  StandardErrorMessageBox(msg);
                      else SetL((uchar)ret);
                      break;
       case   7   :   if(ret<MAX_INT)
                      {
                        if(GetHL()>=MAIN_MEMORY)
                        DisplayError("  [HL] beyond valid memory ");
                        else SetMemByte(GetHL(),(uchar)ret);
                      }
                      else
                      {
                        if(GetHL()>=MAIN_MEMORY-1)
                        DisplayError("[HL] beyond valid memory");
                        else SetMemWord(GetHL(),(word)ret);
                      }
                      break;
       case   8   :   if(ret >= MAIN_MEMORY)
                        StandardErrorMessageBox("Invalid value for IP");
                      else  SetIP((word)ret);
                      break;
       case   9   :   SetSP((word)ret);
                      break;
    }
    return 1;
 }
/*------------------------------------------------------------------------*/
 int ReadRegisterNumber(int ch)
 {
   char  s[257];
   long   ret;

    s[0] = ch;
    s[1] = '\0';
    if(StandardInputBox(" Enter new value for register ",s)==-1)
      return 0;
    if((ret=StringToNum(s))<0)
    {
      ret = ret==__BAD_NUMBER_FORMAT ? BAD_NUMBER_FORMAT : ret;
      StandardErrorMessageBox(error_msg[(int)(-(ret+1))]);
      return -1;
    }
    else if(ret>DOUBLE_INT)  StandardErrorMessageBox("Number too large");
    else SetNewValueForRegister(ret);
    return 1;
 }
/*------------------------------------------------------------------------*/
 int ReadCommandLine(int ch)
 {
   void ToggleFlags(void);

   if(ch==RETURN) ch=0;
   if(SWITCH()==CODE_BOX_TAB) ReadInstruction(ch);
   else if(SWITCH()==MEM_DUMP_TAB) ReadMemDumpNumber(ch);
   else if(SWITCH()==REG_BOX_TAB) ReadRegisterNumber(ch);
   else if(SWITCH()==FLAG_BOX_TAB) ToggleFlags();
   return 1;
 }
/*------------------------------------------------------------------------*/
 int GoToSpecifiedPosition(word ret)
 {
  word j,k;

  /* goto the specified position as indicated by 'ret'  */
   if(ret>MAIN_MEMORY-1) return -1; /* beyond valid memory location */
   switch(SWITCH())
   {
     case  CODE_BOX_TAB  :  /* code dump box */
                            if(ret==0)
                              return  CODE_BOX().cp = CODE_BOX().start = 0;
                            j = GetNearestPrevAddr(ret);
                            if((k=GetNearestNextAddr(j))==ret)
                            j = k;
                            return  CODE_BOX().cp = CODE_BOX().start = j;
     case  MEM_DUMP_TAB  :  return MEM_DUMP_BOX().cp=MEM_DUMP_BOX().start=ret;
   }
   return 1;
   /* you will never reach here; this is added t2o avoid the warning
      'function should return a value '
   */
 }
/*------------------------------------------------------------------------*/
 int GoToPosition(void)
 {
   char  s[257]="";
   long   ret;

    if(!(SWITCH()==CODE_BOX_TAB || SWITCH()==MEM_DUMP_TAB)) return 0;
    /* it should be the code box or memory dump box */

    if(StandardInputBox(" Goto Position ",s)==-1)
      return 0;
    if((ret=StringToNum(s))<0)
    {
      ret = BAD_NUMBER_FORMAT;
      /* we don't encourage negative positions */
      StandardErrorMessageBox(error_msg[(int)(-(ret+1))]);
    }
    else if(ret>=MAIN_MEMORY)
      StandardErrorMessageBox("Value not within legal range");
    else return GoToSpecifiedPosition((word)ret);
    return -1;
 }
/*------------------------------------------------------------------------*/
 void MinusIP(void)
 {
   /* move 'IP' to the previous instruction.
      This is not equivalent to 'undo' because register/memory values are
      not restored
   */
   if(GetIP()==0) return;  /* nothing to do */
   SetIP(GetNearestPrevAddr(GetIP()));
 }
/*------------------------------------------------------------------------*/
 void PlusIP(void)
 {
   word i;

    if((i=GetNearestNextAddr(GetIP()))<MAIN_MEMORY) SetIP(i);
 }
/*------------------------------------------------------------------------*/
 void MinusOrPlusMemDump(int x)
 {
   /* decrement the contents of memory location currently highlighted */
   SetMemByte(MEM_DUMP_BOX().cp,GetMemByte(MEM_DUMP_BOX().cp)+x);
 }
/*------------------------------------------------------------------------*/
 void MinusOrPlusRegister(int x)
 {
  word i;
     switch(REG_DISPLAY_BOX().cp)
     {
       case   0   :   SetA(GetA()+x);
                      break;
       case   1   :   SetB(GetB()+x);
                      break;
       case   2   :   SetC(GetC()+x);
                      break;
       case   3   :   SetD(GetD()+x);
                      break;
       case   4   :   SetE(GetE()+x);
                      break;
       case   5   :   SetH(GetH()+x);
                      break;
       case   6   :   SetL(GetL()+x);
                      break;
       case   7   :   if((long)GetHL()<MAIN_MEMORY)
                      {
                          i = GetMemWord(GetHL())+x;
                          SetMemWord(GetHL(),(word)i);
                      }
                      break;
       case   8   :   if(x==-1)
                      {
                        if(GetIP()>0) SetIP(GetIP()+x);
                      }
                      else if(GetIP()<MAIN_MEMORY-1) SetIP(GetIP()+x);
                      break;
       case   9   :   SetSP(GetSP()+x);
                      break;
    }
 }
/*------------------------------------------------------------------------*/
 void ToggleFlags(void)
 {
    switch(FLAG_BOX().cp)
    {
      case   0   :   SetCarry(!GetCarry());
                     break;
      case   1   :   SetSign(!GetSign());
                     break;
      case   2   :   SetZero(!GetZero());
                     break;
      case   3   :   SetParity(!GetParity());
                     break;
      case   4   :   SetAuxCarry(!GetAuxCarry());
                     break;
    }
 }
/*------------------------------------------------------------------------*/
 int RunTheMachine(void)
 {
   int c;
   int did=1;

    RefreshAllBoxes();
    CODE_BOX().cp = CODE_BOX().start  = GetIP();
    REG_DISPLAY_BOX().cp   = FLAG_BOX().cp = 0;
    RUN() = STEP_OVER()    = 0;
    BREAK_PT_CTR()         = 0;  /* no break points defined */
    LAST_BREAK_POINT()     = 0;  /* where last break point occured */
    SWITCH()  = 0;  /* used for switching between windows */
    while(!(GET_STATUS() & QUIT))
    {
      CODE()         = GetIPByte();
      PTR_TO_SIMU()  = mot[CODE()].Simulate;
      PrintReady();
      if(did) /* refresh everything only if something is done */
      {
        PrintRegisters();    /* display the contents of registers in a box */
        PrintCode();         /* display the instructions */
        PrintMemoryDump();   /* display memory dump      */
        PrintFlags();        /* display the flags        */
        PrintStackDump();    /* display stack dump       */

      }
      c=GetTheChar(NO_POLLING);
      did = 1;   /* something is done, current unused */
      switch(c)
      {
        case  F7       :    Trace();
                            break;
        case  F8       :    STEP_OVER() =1;
                            if((c=StepOver())==QUIT_KEY || c==STOP_KEY)
                                  return c;
                            break;
        case  CTRL_F9  :    RUN() = 1;
                            if((c=Control_F9())==QUIT_KEY || c==STOP_KEY)
                                return c;
                            AdjustCodeStart();
                            break;
        case  F9       :    RUN() = 1;
                            if((c=RunContinuously())==QUIT_KEY
                                  || c==STOP_KEY)
                              return c;
                            break;
        case  ALT_F1     :
        case  CTRL_F1    :
        case  F1         :    DisplayHelp(c,NULL);
                              continue;
        case  STOP_KEY   :
        case  QUIT_KEY   :    return c;

        case  TAB        :    SWITCH() = (SWITCH()+1)%4;
                              /* switch to next window */
                              continue;
        case  SHIFT_TAB  :   if(--SWITCH()<0) SWITCH()=3;
                             continue;
        case  F2         :   InstallBreakPoint(CODE_BOX().cp);
                             continue;
        case  F4         :   if(GoToCursor(CODE_BOX().cp)==QUIT_KEY)
                               return QUIT_KEY;
                            break;
        case  F5        :
        case  CTRL_G    :   GoToPosition();
                            continue;
        case  F12       :   SWITCH() = CODE_BOX_TAB;
                            /* switch to 'code box ' */
                            continue;
        case  MINUS_KEY :  if(SWITCH()==CODE_BOX_TAB)
                               MinusIP();
                            else if(SWITCH()==MEM_DUMP_TAB)
                               MinusOrPlusMemDump(-1);
                            else if(SWITCH()==REG_BOX_TAB)
                               MinusOrPlusRegister(-1);
                            else if(SWITCH()==FLAG_BOX_TAB)
                               ToggleFlags();
                           break;
        case  PLUS_KEY  :  if(SWITCH()==CODE_BOX_TAB)
                               PlusIP();
                            else if(SWITCH()==MEM_DUMP_TAB)
                               MinusOrPlusMemDump(1);
                            else if(SWITCH()==REG_BOX_TAB)
                               MinusOrPlusRegister(1);
                            else if(SWITCH()==FLAG_BOX_TAB)
                               ToggleFlags();
                            break;

        case BACKSPACE        :  MinusIP();
                                 break;
        case ALT_BACKSPACE    :  PlusIP();
                                 break;
        case  CTRL_R          :  RepaintDesktop();
                                 continue;
        case F10              :   DisplayProjectGroupName();
                                  break;
        case  CTRL_A    :
        case  F11       :
        case  HOME      :
        case  END       :
        case  PAGE_UP   :
        case  PAGE_DOWN :
        case  UP        :
        case  DOWN      :   if(SWITCH()==CODE_BOX_TAB)
                               MoveCodeDumpPointer(c);
                            else if(SWITCH()==MEM_DUMP_TAB)
                               MoveMemDumpPointer(c);
                            else if(SWITCH()==REG_BOX_TAB)
                               MoveRegisterDumpPointer(c);
                            else if(SWITCH()==FLAG_BOX_TAB)
                               MoveFlagDumpPointer(c);
                            /* PrintMemoryDump();*/ /* display memory dump */
                            continue;
        default         :   if((c<EXTENDED && c>32) || c==RETURN)
                              ReadCommandLine(c);
                            continue;
      }
      CLEAR_STATUS(JUST_CALLED);   /* reset the 'JUST CALLED' flag */
      CLEAR_STATUS(JUST_RETURNED); /* reset the 'JUST RETURNED' flag */
      AdjustCodeStart();
      if(did) CODE_BOX().cp = GetIP();
      if(SevereErrorsDuringRun()) return 0;
    }
    return 1;
 }
#endif