#ifndef _CONTROL_H_
 #define _CONTROL_H_

 /* routines which emulate the 8085 control functional group instructions */

/*---------------------------------------------------------------------*/
 int _Nop(void)
 {
   return NOP_LEN;
 }
/*---------------------------------------------------------------------*/
 int _Hlt(void)
 {
   SET_STATUS(QUIT);
   return HLT_LEN;
 }
/*---------------------------------------------------------------------*/
 int _Di(void)
 {
   INTR().ei  = 0; /* disable all interrupts except trap */
   return DI_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Ei(void)
 {
   INTR().ei  = 1; /* enable all interrupts */
   return EI_LEN;
 }
/*-----------------------------------------------------------------------*/




#endif