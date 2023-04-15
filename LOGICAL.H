#ifndef _LOGICAL_H_
 #define _LOGICAL_H_

 /* routines which emulate the 8085 logical instructions */

/*-----------------------------------------------------------------------*/
 int _Stc(void)
 {
   /* set the carry flag */
   SetCarry(1);
   return STC_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaB(void)
 {
   /* logical "and" with accumulator and store the result in accumulator */
   /* S,Z,P are modified to reflect the result of the operation.  CY is
      reset.  In 8085 AC is set and in 8080A AC is the result of
      ORing bits D3 of the operands.
   */

    SetTemp(GetA() & GetB());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaC(void)
 {
    SetTemp(GetA() & GetC());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaD(void)
 {
    SetTemp(GetA() & GetD());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaE(void)
 {
    SetTemp(GetA() & GetE());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaH(void)
 {
    SetTemp(GetA() & GetH());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaL(void)
 {
    SetTemp(GetA() & GetL());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaM(void)
 {
    SetTemp(GetA() & GetMemByte(GetHL()));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _AnaA(void)
 {
    SetTemp(GetA() & GetA());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return  ANA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Ani(void)
 {
   /* The contents of the accumulator are logiclly ANDed with the 8-bit
      data and the results are placed in the accumulator
   */
    SetTemp(GetA() & GetMemWord(GetIP()+1));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(1);
    return ANI_LEN;;
 }
/*-----------------------------------------------------------------------*/

 int _XraB(void)
 {
   /* logical "xor" with accumulator and store the result in accumulator */
   /* S,Z,P are modified to reflect the result of the operation.  CY is
      reset.  In 8085 AC is set and in 8080A AC is the result of
      ORing bits D3 of the operands.
   */

    SetTemp(GetA() ^ GetB());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraC(void)
 {
    SetTemp(GetA() ^ GetC());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraD(void)
 {
    SetTemp(GetA() ^ GetD());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraE(void)
 {
    SetTemp(GetA() ^ GetE());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraH(void)
 {
    SetTemp(GetA() ^ GetH());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraL(void)
 {
    SetTemp(GetA() ^ GetL());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraM(void)
 {
    SetTemp(GetA() ^ GetMemByte(GetHL()));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _XraA(void)
 {
    SetTemp(GetA() ^ GetA());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  XRA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Xri(void)
 {
   /* The contents of the accumulator are logiclly ANDed with the 8-bit
      data and the results are placed in the accumulator
   */
    SetTemp(GetA() ^ GetMemWord(GetIP()+1));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return XRI_LEN;;
 }
/*-----------------------------------------------------------------------*/
 int _OraB(void)
 {
   /* logical "or" with accumulator and store the result in accumulator */
   /* S,Z,P are modified to reflect the result of the operation.  CY is
      reset.  In 8085 AC is set and in 8080A AC is the result of
      ORing bits D3 of the operands.
   */

    SetTemp(GetA() | GetB());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraC(void)
 {
    SetTemp(GetA() | GetC());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraD(void)
 {
    SetTemp(GetA() | GetD());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraE(void)
 {
    SetTemp(GetA() | GetE());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraH(void)
 {
    SetTemp(GetA() | GetH());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraL(void)
 {
    SetTemp(GetA() | GetL());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraM(void)
 {
    SetTemp(GetA() | GetMemByte(GetHL()));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _OraA(void)
 {
    SetTemp(GetA() | GetA());
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return  ORA_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Ori(void)
 {
   /* The contents of the accumulator are logiclly ANDed with the 8-bit
      data and the results are placed in the accumulator
   */
    SetTemp(GetA() | GetMemWord(GetIP()+1));
    SetA(GetTemp() & MAX_INT);
    SetAllButCarry();
    SetCarry(0);
    SetAuxCarry(0);
    return ORI_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpB(void)
 {
  uchar a,b;      /* the values of the two accumulator */
   /* Compare with accumulator */
   /* if (A) < (Reg/Mem) carry flag is set.
      if (A) = (Reg/Mem) zero  flag is set.
      if (A) > (Reg/Mem) carry and zero flags are set.
   */
   a = GetA();
   b = GetB();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpC(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetA();
   b = GetC();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpD(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetA();
   b = GetD();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpE(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetA();
   b = GetE();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpH(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetA();
   b = GetH();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpL(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetL();
   b = GetB();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpM(void)
 {
  uchar a,b;      /* the values of accumulator and memory location */

   a = GetA();
   b = GetMemByte(GetHL());
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _CmpA(void)
 {
  uchar a,b;      /* the values of the two accumulator */

   a = GetA();
   b = GetA();
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return  CMP_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Cpi(void)
 {
  /* compare immediate */
   uchar a,b;

   a = GetA();
   b = GetMemByte(GetIP()+1);  /* get the byte following 'ip' */
   SetTemp(a-b);    /* this is done to set other flags */
   SetAllButCarry();
   if(a < b) SetCarry(1);
   else if(a == b) SetZero(1);
   else if (a > b)
   {
     SetZero(0);
     SetCarry(0);
   }
   return CPI_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Rlc(void)
 {
   /* Rotate accumulator left.
      Each binary bit of the accumulator is rotated by one position.
      Bit D7 is placed in the position of D0 as well as in the Carry flag
   */
   uchar x;
   SetTemp(GetA()<<1); /* rotate by 1 bit towards right */
   x = GetA()>>7; /* Get the highest bit */
   SetTemp(x | GetTemp());
   SetA(GetTemp() & 255);
   SetCarry(x);
   return RLC_LEN;
 }

/*-----------------------------------------------------------------------*/
 int _Rrc(void)
 {
   /* Rotate accumulator right.
      Each binary bit of the accumulator is rotated by one position.
      Bit D0 is placed in the position of D7 as well as in the Carry flag
   */
   uchar x;
   SetTemp(GetA()>>1); /* rotate by 1 bit towards right */
   x = (GetA() & 1)<<7;   /* Get the lower most bit and shift it by 7 */
   SetTemp(x | GetTemp());
   SetA(GetTemp() & 255);
   SetCarry(x);
   return RRC_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Ral(void)
 {
   /* Each binary bit of the accumulator is rotated left by one position
      through the Carry flag.  Bit D7 is placed in the bit in the Carry
      flag and Carry flag is placed in the least significant position D0
   */
   uchar x;
    SetTemp(GetA()<<1);
    x = GetA() >> 7;   /* got the most significant bit of accumulator */
    SetA((GetCarry() | GetTemp()) & MAX_INT);
    /* get the carry and bitwise or it with the shifted value of accumulator
       which is stored in the 'temporary' register.  Now and this with
       'MAX_INT' to get a 8 bit number and set this value in 'A'
    */
    SetCarry(x);
    return RAL_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Rar(void)
 {
   /* Each binary bit of the accumulator is rotated right by one position
      through the Carry flag.  Bit D0 is placed in the bit in the Carry
      flag and Carry flag is placed in the most significant position D7
   */
   uchar x;
    SetTemp(GetA()>>1);
    x = GetA() & 1; /* got the least significant bit of accumulator */
    SetA(((GetCarry()<<7) | GetTemp()) & MAX_INT);
    /* get the carry and shift it by 7 so that it will be placed in the
       most significant postition bitwise or it with the shifted
       value of accumulator which is stored in the 'temporary' register.
       Now and this with 'MAX_INT' to get a 8 bit number and set
       this value in 'A'
    */
    SetCarry(x);
    return RAR_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Cma(void)
 {
   /* complement accumulator */
   SetA(~GetA());
   return CMC_LEN;
 }
/*------------------------------------------------------------------------*/
 int _Cmc(void)
 {
   SetCarry(!GetCarry());
   return CMC_LEN;
 }

#endif