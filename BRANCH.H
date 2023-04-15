#ifndef _BRANCH_H_
 #define _BRANCH_H_

  /* routines which emulate the 8085 Branch Instructions  */

 int SetJmpIP(void)
 {
   /* set the IP for jump instructions by accessing the bytes in memory
      following the 'IP'
   */
   return SetIP((GetMemByte(GetIP()+2)<<8)+(GetMemByte(GetIP()+1)));
 }
/*-----------------------------------------------------------------------*/
 unsigned GetJmpIP(void)
 {
   /* Get the IP for jump instructions by accessing the bytes in memory
      following the 'IP'
   */
   return (GetMemByte(GetIP()+2)<<8)+GetMemByte(GetIP()+1);
 }
/*-----------------------------------------------------------------------*/
 int _Jmp(void)
 {
   /* Jump unconditionally transferring control to the memory location
      specified by the 16 bit address.
      This is a 16 bit instruction
      Lower order byte first and then higher order byte
   */

   SetJmpIP();
   /* subtract the length of the jump instruction, because it will be
      added again when this function returns 3
   */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _JnZ(void)
 {
   /* jump if not zero */
   if(GetZero()) return JMP_LEN;
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _JZ(void)
 {
   /* Jump if zero */

   if(!GetZero()) return JMP_LEN;
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _JnC(void)
 {
   /* jump if not carry */
   if(GetCarry()) return JMP_LEN;
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _Jc(void)
 {
   /* jump if carry flag is set */
   if(!GetCarry()) return JMP_LEN;
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _Jpe(void)
 {
   /* jump on parity even*/
   if(!GetParity()) return JMP_LEN;
   /* if parity flag is set then  jump*/
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _Jpo(void)
 {
   /* jump on parity odd*/
   if(GetParity()) return JMP_LEN;
   /* if parity flag is set then don't jump*/
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/

 int _Jp(void)
 {
   /* jump if plus */
   if(GetSign()) return JMP_LEN;
   /* if sign flag is 0 then it means number is positive and hence jump*/
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _Jm(void)
 {
   /* jump if minus */
   if(!GetSign()) return JMP_LEN;
   /* if sign flag is 1 then it means number is negative and hence jump*/
   return _Jmp();
 }
/*-----------------------------------------------------------------------*/
 int _PCHL(void)
 {
   /* Load program counter with HL contents */
   SetIP(GetHL());
   return 0;
    /* don't return PCHL_LEN, otherwise you will miss one instruction */
 }
/*-----------------------------------------------------------------------*/
 int _Rst0(void)
 {
   /* this is like a 1 byte call instruction, with jump addresses
      predetermined */
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_0_ADDR);          /* jump to predetermined address */
   return 0;
   /* return the length of instruction as 0, since the new value of 'ip'
      has been set by 'SetIP'
   */
 }
/*-----------------------------------------------------------------------*/
 int _Rst1(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_1_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Rst2(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_2_ADDR);          /* jump to predetermined address */
   return 0;
}
/*-----------------------------------------------------------------------*/
 int _Rst3(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_3_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Rst4(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_4_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Rst5(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_5_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Rst6(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_6_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Rst7(void)
 {
   PushWord(GetIP()+ RST_LEN); /* Save the Contents of IP */
   SetIP(RST_7_ADDR);          /* jump to predetermined address */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _Call(void)
 {
   if(GetJmpIP()==SYSTEM_CALL)
   {
     PerformSystemCall();
     return CALL_LEN;
   }
   PushWord(GetIP()+ CALL_LEN); /* Save the Contents of IP */
   SET_STATUS(JUST_CALLED);
   _Jmp();    /* Jump to the specified location */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _CnZ(void)
 {
   /* call if not Zero */
   return GetZero() ?  CALL_LEN : _Call();
 }
/*-----------------------------------------------------------------------*/
 int _CZ(void)
 {
   /* call if Zero */
   return GetZero() ? _Call() :  CALL_LEN ;
 }
/*-----------------------------------------------------------------------*/
 int _CnC(void)
 {
   /* call if not Carry */
   return GetCarry() ?  CALL_LEN : _Call();
 }
/*-----------------------------------------------------------------------*/
 int _CC(void)
 {
   /* call if carry */
   return GetCarry() ? _Call() :  CALL_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Cpo(void)
 {
   /* call if parity is odd i.e., if parity bit is not set */
   return GetParity() ?  CALL_LEN : _Call();
 }
/*-----------------------------------------------------------------------*/
 int _Cpe(void)
 {
   /* call if parity even */
   return GetParity() ? _Call() :  CALL_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Cp(void)
 {
   /* call if plus */
   return GetSign() ?  CALL_LEN : _Call();
 }
/*-----------------------------------------------------------------------*/
 int _Cm(void)
 {
   /* call if minus */
   return GetSign() ? _Call() :  CALL_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Ret(void)
 {
   /* return by poping top of stack into IP */
   PopIP();
   SET_STATUS(JUST_RETURNED);
   /* set the status word indicating that the subroutine has been completed
      This is useful in implementing step over
   */
   return 0;
 }
/*-----------------------------------------------------------------------*/
 int _RnZ(void)
 {
   /* call if not Zero */
   return GetZero() ?  RET_LEN : _Ret();
 }
/*-----------------------------------------------------------------------*/
 int _RZ(void)
 {
   /* return if Zero */
   return GetZero() ? _Ret() :  RET_LEN ;
 }
/*-----------------------------------------------------------------------*/
 int _RnC(void)
 {
   /* return if not Carry */
   return GetCarry() ?  RET_LEN : _Ret();
 }
/*-----------------------------------------------------------------------*/
 int _RC(void)
 {
   /* return if carry */
   return GetCarry() ? _Ret() :  RET_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Rpo(void)
 {
   /* return if not parity is odd i.e., if parity bit is not set */
   return GetParity() ?  RET_LEN : _Ret();
 }
/*-----------------------------------------------------------------------*/
 int _Rpe(void)
 {
   /* return if not parity even */
   return GetParity() ? _Ret() :  RET_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Rp(void)
 {
   /* return if plus */
   return GetSign() ?  RET_LEN : _Ret();
 }
/*-----------------------------------------------------------------------*/
 int _Rm(void)
 {
   /* return if minus */
   return GetSign() ? _Ret() :  RET_LEN;
 }

#endif _BRANCH_H_