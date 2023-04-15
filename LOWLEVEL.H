#ifndef _LOWLEVEL_H_
 #define _LOWLEVEL_H_

 /* lowlevel routines to access and manipulate the 8085 machine */

 #define  GetFlag()                             (KIT->cpu.r.flags)
 /* return the value of the flags  */
 #define  SetFlag(f)                            (KIT->cpu.r.flags=f)
 /* set the value of the flags  */
 #define  GetIP()                               (KIT->cpu.r.ip)
 /* return the value of Instruction pointer */
 #define  GetSP()                               (KIT->cpu.r.sp)
  /* return the value of the stack pointer */
 #define  GetA()                                (KIT->cpu.r.a)
   /* return the value of register 'A' */
 #define  GetB()                                (KIT->cpu.r.b)
   /* return the value of register 'B' */
 #define  GetC()                                (KIT->cpu.r.c)
   /* return the value of register 'C' */
 #define  GetD()                                (KIT->cpu.r.d)
   /* return the value of register 'D' */
 #define  GetE()                                (KIT->cpu.r.e)
   /* return the value of register 'E' */
 #define  GetH()                                (KIT->cpu.r.h)
   /* return the value of register 'H' */
 #define  GetL()                                (KIT->cpu.r.l)
   /* return the value of register 'L' */
 #define  GetTemp()                             (KIT->cpu.r.temp)
   /* get the value of temporary varaible in the KIT */
 #define GetPsw()                               ((GetA()<<8)+GetFlag())
  /* get the Processor Status word */
 #define GetTemp32()                            (KIT->cpu.r.temp32)
   /* return the value of temporary varaible in the KIT */
 #define GetHL()                                ((word)(GetH()<<8)+GetL())
   /* get the value of 'HL' pair */
 #define GetDE()                                ((word)(GetD()<<8)+GetE())
   /* get the value of 'DE' pair */
 #define GetBC()                                ((word)(GetB()<<8)+GetC())
   /* get the value of 'BC' pair */

/*-----------------------------------------------------------------------*/

 #define  SetImmediate(x)                       (KIT->cpu.immediate = x)
  /* set the value of 'immediate' in 8085 */
 #define SetSP(x)                               (KIT->cpu.r.sp = x)
  /* set the value of the stack pointer */
/*-----------------------------------------------------------------------*/
 unsigned  SetIP(unsigned i)
 { /* return the value of Instruction pointer */
    if(i>MAIN_MEMORY)
    {
       SET_STATUS(IP_BEYOND_MEMORY);
       /* tried to set the value of ip beyond valid memory location */
       return KIT->cpu.r.ip;
    }
    return KIT->cpu.r.ip = i;
 }
/*-----------------------------------------------------------------------*/
 #define SetA(x)                                (KIT->cpu.r.a = x)
  /* set the contents of register 'A' */
 #define SetB(x)                                (KIT->cpu.r.b = x)
  /* set the contents of register 'B' */
 #define SetC(x)                                (KIT->cpu.r.c = x)
  /* set the contents of register 'C' */
 #define SetD(x)                                (KIT->cpu.r.d = x)
  /* set the contents of register 'D' */
 #define SetE(x)                                (KIT->cpu.r.e = x)
  /* set the contents of register 'E' */
 #define SetH(x)                                (KIT->cpu.r.h = x)
  /* set the contents of register 'H' */
 #define SetL(x)                                (KIT->cpu.r.l = x)
  /* set the contents of register 'L' */
/*-----------------------------------------------------------------------*/
 unsigned SetPsw(unsigned v)
 {  /* return the Processor Status word */
    return SetA(v>>8) + SetFlag(v&0x255);
 }
/*-----------------------------------------------------------------------*/
 #define SetTemp(x)                             (KIT->cpu.r.temp = x)
  /* set the value of temporary varaible in the KIT */
 #define SetTemp32(x)                           (KIT->cpu.r.temp32 = x)
   /* set the value of temporary varaible in the KIT */
/*-----------------------------------------------------------------------*/
 unsigned SetHL(unsigned x)
 {
   SetH(x>>8);        /* get upper 8 bits */
   SetL(x);           /* get lower 8 bits */
   return 1;
 }
/*-----------------------------------------------------------------------*/
 unsigned SetBC(unsigned x)
 {
   SetB(x>>8);        /* get upper 8 bits */
   SetC(x);      /* get lower 8 bits */
   return 1;
 }
/*-----------------------------------------------------------------------*/
 unsigned SetDE(unsigned x)
 {
   SetD(x>>8);        /* get upper 8 bits */
   SetE(x);      /* get lower 8 bits */
   return 1;
 }
/*-----------------------------------------------------------------------*/
 #define GetIPWord()     \
    (GetIP()>=MAIN_MEMORY-1 ? 0 : \
      (KIT->cpu.ram[GetIP()]<<8) + KIT->cpu.ram[GetIP()+1])
   /* get a word of data from memory pointed by 'IP'  */
 #define GetIPByte()   (GetIP()>=MAIN_MEMORY ? 0 :KIT->cpu.ram[GetIP()])
   /* get a byte of data from memory pointed by 'IP' */
/*-----------------------------------------------------------------------*/
 word GetMemWord(unsigned addr)
 {
   /* get a word of data from memory pointed by 'addr'  */
  /* return KIT->cpu.ram.word[addr/2]; */
  if(addr>LARGEST_ADDR-1)
  {
    SET_STATUS(READ_FAULT | SEVERE_ERROR);
    /* tried to access beyond available memory*/
    return 0;
  }
  return KIT->cpu.ram[addr] + (KIT->cpu.ram[addr+1]<<8);
 }
/*-----------------------------------------------------------------------*/
 int GetMemByte(unsigned addr)
 {
   /* get a byte of data from memory pointed by 'addr' */
  if(addr>LARGEST_ADDR)
  {
    SET_STATUS(READ_FAULT | SEVERE_ERROR);
    /* tried to access beyond available memory*/
    return 0;
  }
  return KIT->cpu.ram[addr];
 }
/*-----------------------------------------------------------------------*/
 long SetMemWord(unsigned addr,unsigned data)
 {
   /* set a word of data in memory pointed by 'addr' to 'data'  */
   /* return KIT->cpu.ram.word[addr/2]=data; */
   if(addr>LARGEST_ADDR-1)
   {
     SET_STATUS(WRITE_FAULT | SEVERE_ERROR);
     /*tried to access beyond available memory*/
     return WRITE_SEG_FAULT;
   }
   KIT->cpu.ram[addr]   = data & 0xff;
   KIT->cpu.ram[addr+1] = data >> 8;
   return data;
 }
/*-----------------------------------------------------------------------*/
 int SetMemByte(unsigned addr,unsigned data)
 {
   /* set a byte of data in memory pointed by 'addr' to 'data'  */
   if(addr>LARGEST_ADDR)
   {
     SET_STATUS(WRITE_FAULT | SEVERE_ERROR);
     /*tried to access beyond available memory*/
     return WRITE_SEG_FAULT;
   }
   return KIT->cpu.ram[addr]=data;
 }
/*-----------------------------------------------------------------------*/
 void ClearMemory(void)
 {
   word i;

    for(i=0; i<MAIN_MEMORY ; i++)
       KIT->cpu.ram[i] = 0; /* initialize  memory location to '0'*/
 }
/*------------------------------------------------------------------------*/

 unsigned PushWord(unsigned x)
 {
   /* this function is not used for simulation, but is internally used
      for instructions like 'Call'
   */
   if(x>MAIN_MEMORY-1)
   {
      SET_STATUS(STACK_OVERFLOW);
      /* tried to set the value of ip beyond valid memory location */
      return KIT->cpu.r.ip;
   }
   SetSP(GetSP()-2);           /* decrement SP first */
   SetMemWord(GetSP(),x);      /* push the data */
   return x;
 }
/*-----------------------------------------------------------------------*/
 unsigned PopWord(void)
 {
  unsigned int x;
   /* this function is not used for simulation, but is internally used
      for instructions like 'ret'
   */
   if(GetSP()>MAIN_MEMORY-1)
   {
      SET_STATUS(STACK_UNDERFLOW);
      /* tried to set the value of ip beyond valid memory location */
      return KIT->cpu.r.ip;
   }
   x = GetMemWord(GetSP()); /* get the word and save it into reg pair */
   SetSP(GetSP()+2);            /* increment sp */
   return x;
 }
/*-----------------------------------------------------------------------*/
 unsigned PushIP(void)
 {
   return PushWord(GetIP());
 }
/*-----------------------------------------------------------------------*/
 unsigned PopIP(void)
 {
   /* pop top of stack into 'IP' */
   return SetIP(PopWord());
 }
/*-----------------------------------------------------------------------*/

 int DumpRegisters(void)
 {
   printf("\n--------------------------------------");
   printf("\nA=%#x  B=%#x  C=%#x  D=%#x  ",GetA(),GetB(),GetC(),GetD());
   printf("E=%#x  H=%#x  L=%#x  ",GetE(),GetH(),GetL());
   printf("\nIP=%#x  Flags=%#x",GetIP(),GetFlag());
   printf("\nSP=%#x",GetSP());
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int GotoInterrupt(int intr_num)
 {
   /* set the value of 'IP' so that the processor serivices that
      interrupt
   */
   switch(intr_num)
   {
     case TRAP_INTR    :  PushIP(); /* push the current value of 'IP' */
                          SetIP(TRAP_ADDR);
                          break;
     case RST_5_5_INTR :  if(INTR().rst_5_5_ff) return 0;
                          PushIP(); /* push the current value of 'IP' */
                          SetIP(RST_5_5_ADDR);
                          break;
     case RST_6_5_INTR :  if(INTR().rst_6_5_ff) return 0;
                          PushIP(); /* push the current value of 'IP' */
                          SetIP(RST_6_5_ADDR);
                          break;
     case RST_7_5_INTR :  if(INTR().rst_7_5_ff) return 0;
                          PushIP(); /* push the current value of 'IP' */
                          SetIP(RST_7_5_ADDR);
                          break;
   }
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int PerformInterrupt(int intr_num)
 {
   /* the contents of other registers other than 'IP' should be
      saved by the interrupt routine
   */
   if(!INTR().ei)  /* interrupts have been disabled, except trap */
   {
     if(intr_num==TRAP_INTR)  /* a trap interrupt was generated */
     {
        PushIP(); /* push the current value of 'IP' */
        SetIP(TRAP_ADDR);
        return 1;
     }
     return 0;
   }
    /* switch(intr_num)
     {
       case RST_5_5_INTR :  INTR().pending_5_5 = 1;
                            break;
       case RST_6_5_INTR :  INTR().pending_6_5 = 1;
                            break;
       case RST_7_5_INTR :  INTR().pending_7_5 = 1;
                            break;
     }
    */
    return GotoInterrupt(intr_num);
 }
/*-----------------------------------------------------------------------*/
 void interrupt TrapIntrFunc(void)
 {
   INTERRUPTED() = 1;
   INTERRUPT_NUMBER() = TRAP_INTR;
 }
/*-----------------------------------------------------------------------*/
 void interrupt Rst_5_5_Func(void)
 {
   INTERRUPTED() = 1;
   INTERRUPT_NUMBER() =  RST_5_5_INTR;
 }
/*-----------------------------------------------------------------------*/
 void interrupt Rst_6_5_Func(void)
 {
   INTERRUPTED() = 1;
   INTERRUPT_NUMBER() =  RST_6_5_INTR;
 }
/*-----------------------------------------------------------------------*/
 void interrupt Rst_7_5_Func(void)
 {
   INTERRUPTED() = 1;
   INTERRUPT_NUMBER() =  RST_7_5_INTR;
 }
/*-----------------------------------------------------------------------*/
 void InitIsrCode(void)
 {
   /* the 'ISR' routines are simply set to 'RET' instructions  */
    SetMemByte(TRAP_ADDR,RET_START);
    SetMemByte(RST_5_5_ADDR,RET_START);
    SetMemByte(RST_6_5_ADDR,RET_START);
    SetMemByte(RST_7_5_ADDR,RET_START);

    SetMemByte(RST_0_ADDR,RET_START);
    SetMemByte(RST_1_ADDR,RET_START);
    SetMemByte(RST_2_ADDR,RET_START);
    SetMemByte(RST_3_ADDR,RET_START);
    SetMemByte(RST_4_ADDR,RET_START);
    SetMemByte(RST_5_ADDR,RET_START);
    SetMemByte(RST_6_ADDR,RET_START);
    SetMemByte(RST_7_ADDR,RET_START);
 }
/*-----------------------------------------------------------------------*/
 int SendToSerialPort(uchar x)
 {
   outportb(GCOM2,x);   /* 'GCOM2' is a variable defined in 'vars.h' */
   return x;
 }
/*-----------------------------------------------------------------------*/
 int ReadFromSerialPort(void)
 {
   return inportb(GCOM2)>>7;
   /* 'GCOM2' is a variable defined in 'vars.h' */
 }
/*-----------------------------------------------------------------------*/
 int InitInterruptMask(void)
 {
   INTR().ei = 0;
   INTR().rst_5_5_ff = 1;  /* by default disable interrupts */
   INTR().rst_6_5_ff = 1;  /* by default disable interrupts */
   INTR().rst_7_5_ff = 1;  /* by default disable interrupts */
   return 1;
 }
#endif