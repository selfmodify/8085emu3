#ifndef __UNDEF_H__
 #define __UNDEF_H__

 /* the various functions which have been implemented only partly */

 /* pending interrupts and interrupt priorities have not been implemented.
    It will be possible to emulate the priorities by emulating
    8259!! (should be difficult)
 */

 /* the following functions have  been implemented only partly */

/*-----------------------------------------------------------------------*/
 int _Rim(void)
 {
  int temp=0;

    temp  |= INTR().rst_5_5_ff;
    temp  |= INTR().rst_6_5_ff<<1;
    temp  |= INTR().rst_7_5_ff<<2;
    temp  |= INTR().ei<<3;  /* enable interrupt ? */
    /* pending interrupts has not been implemented, only the variables
       are available
    */
    temp  |= INTR().pending_5_5<<4;
    temp  |= INTR().pending_6_5<<5;
    temp  |= INTR().pending_7_5<<6;
    temp  |= ReadFromSerialPort()<<7;
    SetA((uchar)temp);
   return 1;
 }
/*-----------------------------------------------------------------------*/
 int _Sim(void)
 {
   /* set interrupt mask according to the value in the accumulator */

    if(GetA() & MASK_SET_ENABLE)
    {
     /* interrupts are enabled only if 'mask set enable' bit is 1 */
      INTR().rst_5_5_ff =  !(GetA() & MASK_5_5);
      INTR().rst_6_5_ff =  !(GetA() & MASK_6_5);
      INTR().rst_7_5_ff =  !(GetA() & MASK_7_5);
    }
    if(GetA() & RESET_RST_7_5); /*reset the 'rst_7_5_ff' if this is 1 */
       INTR().rst_7_5_ff = 0;
    if(GetA() & SERIAL_DATA_ENABLE)
      SendToSerialPort((GetA() & SERIAL_DATA)>>7);
   return SIM_LEN;
 }
/*-----------------------------------------------------------------------*/
 int _Invalid(void)
 {
   SET_STATUS(INVALID_OP);
   return 1;
 }
/*-----------------------------------------------------------------------*/
#endif