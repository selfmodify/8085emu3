#ifndef _SYSTEM_H_
 #define _SYSTEM_H_

/* functions which implement the system calls of the 8085 mu-p Kit */

/* #define SYSTEM_CALL 0x0005 :- defined in 'define.h' */

 #define READ_FROM_KEYBOARD  " Read from keyboard and return code into A"
 #define DATA_FROM_KEYBOARD  \
   " Read from keyboard, c=0 read 4 keys into HL, c=1 read 2 keys into L"

 int IsHexDigit(int c)
 {
   /* isxdigit() didn't work properly, I had to make my own 'IsHexDigit' */
   return (c>='0' && c<='9') || (c>='A' && c<='F') ||
          (c>='a' && c<='f') ? 1 : 0;
 }
/* ---------------------------------------------------------------------- */
 int ReadHexKey(void)
 {
   /* read a key which corresponds to a hex character */
  int ch;
   fflush(stdin);
   while(!IsHexDigit((ch=GetTheChar(NO_POLLING))))
    if(ch==STOP_KEY || ch==QUIT_KEY)  break;
   if(ch==STOP_KEY || ch==QUIT_KEY)
     SET_STATUS(QUIT);  /* you pressed 'stop key' hence stop the machine*/
   ch = toupper(ch);    /* small letter is converted into capitals */
   ch = ch>='A' ? ch-'A'+ 10 : ch-'0' ;
   return ch;
 }
/* ---------------------------------------------------------------------- */
 int WriteToPrinter(int x)
 {
  int ret;
   /* write character to printer */
   _AX = x&0xff;  /* 'AH' should be zero */
   _DX = GPRNPORT;  /* printer number (0=LPT1, 1=LPT2, 2=LPT3) */
   /* 'GPRNPORT  is defined in 'vars.h' */
   geninterrupt(0x17);
   ret=_AX>>8;  /* if function fails the AH has the error value */
   if(ret&1)        DisplayError("Printer timed out");
   else if(ret&8)   DisplayError("Printer I/O error");
   else if(ret&32)  DisplayError("Out of paper");
   else if(ret&128) DisplayError("printer not ready");
   return ret>>4;
 }
/*-----------------------------------------------------------------------*/
 int _SystemReset(void)
 {
    /* this will not be implemented for obvious reasons */
    return 1;
 }
/* ---------------------------------------------------------------------- */
 int _SystemBlankDisplay(void)
 {
   switch(GetC())
   {
     case   0    :   BlankAddressLed();
                     break;
     case   1    :   BlankDataLed();
                     break;
     case   2    :   BlankStatusLed();
                     break;
     case   3    :   BlankAllLeds();
                     break;
     dafault     :   return BadSystemCall();
   }
   return 1;
 }
/* ---------------------------------------------------------------------- */
 int _SystemDisplay(void)
 {
  /* blank the display's */
   switch(GetC())
   {
     case 0    :  return BlankAddressLed();
     case 1    :  return BlankDataLed();
     case 2    :  return BlankStatusLed();
     case 3    :  return BlankAllLeds();
     default   :  return BadSystemCall();
   }
 }
/* ---------------------------------------------------------------------- */
 int _SystemDisplayDot(void)
 {
   switch(GetC())
   {
     case  0   :   DATA_FIELD(1)   = DATA_FIELD(1)   |  LED_DOT;
                   break;
     case  1   :   ADDR_FIELD(3)   = ADDR_FIELD(3)   |  LED_DOT;
                   break;
     case  2   :   ADDR_FIELD(2)   = ADDR_FIELD(2)   |  LED_DOT;
                   ADDR_FIELD(3)   = ADDR_FIELD(3)   |  LED_DOT;
                   break;
     case  3   :   STATUS_FIELD(1) = STATUS_FIELD(1) |  LED_DOT;
                   break;
     default   :   return BadSystemCall();
   }
   return DisplayAllLeds();
 }
/* ---------------------------------------------------------------------- */
 int _SystemDisplayData(void)
 {
   switch(GetC())
   {
     case  0   :   STATUS_FIELD(0) = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  1   :   STATUS_FIELD(1) = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  2   :   ADDR_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  3   :   ADDR_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  4   :   ADDR_FIELD(2)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  5   :   ADDR_FIELD(3)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  6   :   DATA_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  7   :   DATA_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()));
                   break;
     case  8   :   DATA_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()));
                   DATA_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()+1));
                   break;
     case  9   :   ADDR_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()));
                   ADDR_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()+1));
                   ADDR_FIELD(2)   = NumTo7Seg(GetMemByte(GetHL()+2));
                   ADDR_FIELD(3)   = NumTo7Seg(GetMemByte(GetHL()+3));
                   break;
     case  0xA :   STATUS_FIELD(0) = NumTo7Seg(GetMemByte(GetHL()));
                   STATUS_FIELD(1) = NumTo7Seg(GetMemByte(GetHL()+1));
                   break;
     case  0xB :
		   STATUS_FIELD(0) = NumTo7Seg(GetMemByte(GetHL()));
		   STATUS_FIELD(1) = NumTo7Seg(GetMemByte(GetHL()+1));
		   ADDR_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()+2));
		   ADDR_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()+3));
		   ADDR_FIELD(2)   = NumTo7Seg(GetMemByte(GetHL()+4));
		   ADDR_FIELD(3)   = NumTo7Seg(GetMemByte(GetHL()+5));
		   DATA_FIELD(0)   = NumTo7Seg(GetMemByte(GetHL()+6));
		   DATA_FIELD(1)   = NumTo7Seg(GetMemByte(GetHL()+7));
		   break;
     default   :   return BadSystemCall();
   }
   DisplayAllLeds();
   return 1;
 }
/* ---------------------------------------------------------------------- */
 int _SystemDisplayErr(void)
 {
   /* display the 'Err' message */
    BlankAllLeds();
    ADDR_FIELD(0) = NumTo7Seg(0xE);
    ADDR_FIELD(1) = NumTo7Seg(0x1c);
    ADDR_FIELD(2) = NumTo7Seg(0x1c);
    DisplayAllLeds();
    return 1;
 }
/* ---------------------------------------------------------------------- */
 int _SystemReadFromKeyboard(void)
 {
   /* read a key from keyboard and return the key code in the A register */
   HelpLine(READ_FROM_KEYBOARD);
   SetA((uchar)ReadHexKey());
   DefaultStatusLine();
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemCodeConversion(void)
 {
  /* the idea behind this system is not clear has it is not properly
     implemented
  */
  /*  converts HEX to ASCII & ASCII to HEX values
    When C=0 this function converts a hex value to its equivalent
    ASCII value.  This 8 bit hex data will be converted to 2 ASCII value
  */
   switch(GetC())
   {
     case   0   :   /* DE register pair will have the ASCII values
                       D - Higher bytes, E Lower bytes
                    */
                    SetD(NumToChar((GetL()>>4))); /* get upper 4 bits */
                    SetE(NumToChar((GetL()&0x0f))); /* get lower 4 bits */
                    return 1;

     case   1   :   /* H contains higher bytes ASCII valueI values
                       L contains lower byte ASCII value
                       A contains the hex value
                    */
                    SetA( (CharToNum(GetH())<<4) +
                          (CharToNum(GetL())&0x0f)); /* get lower 4 bits */
                    return 1;
     default    :   return BadSystemCall();
   }
 }
/* ----------------------------------------------------------------------*/
 int _SystemLengthOfBlock(void)
 {
   /* this function calculates the length of a block of memory
      i.e. find BC - HL
      if HL > BC, then a calculation error is displayed
   */
   long x;

    if((x=GetBC()-GetHL())<0) _SystemDisplayErr();  /* HL > BC */
    SetDE((word)x);
    return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemGenerateTone(void)
 {
   /* generate tone for driving a speaker
      but in our case we generate a tone for a short duration and quit
   */
   switch(GetC())
   {
     case   0   :  /* generate 1 KHZ */
                   sound(1000);
                   delay(75);
                   nosound();
                   break;
     case   1   :  /* generate 2 KHZ */
                   sound(2000);
                   delay(75);
                   nosound();
                   break;
     default    :  return BadSystemCall();
   }
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemDelay(void)
 {
    /* HL = delay value
       delay time is equal to  HL*7 clock ticks of the PC clock.
       This makes the delay of whether the processor is in turbo mode
       or not.
    */
    clock_t t1;
    t1 = clock();
    while((clock()-t1)<7*GetHL())
           ;
    return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemDisplayHLData(void)
 {
   /* When 'c' = 0, contents of 'L' are displayed in the status field
      When 'c' = 1, contents of 'H' and 'L' are displayed in the
      address field.
      When 'c' = 2, contents of 'L' are displayed in the Data field
   */
   switch(GetC())
   {
     case 0x0     :  STATUS_FIELD(1) = NumTo7Seg(GetL()&0x0f);
                     STATUS_FIELD(0) = NumTo7Seg((GetL()&0xf0)>>4);
                     break;
     case 0x1     :  ADDR_FIELD(3) = NumTo7Seg(GetL()&0x0f);
                     ADDR_FIELD(2) = NumTo7Seg((GetL()&0xf0)>>4);
                     ADDR_FIELD(1) = NumTo7Seg(GetH()&0x0f);
                     ADDR_FIELD(0) = NumTo7Seg((GetH()&0xf0)>>4);
                     break;
     case 0x2     :  DATA_FIELD(1) = NumTo7Seg(GetL()&0x0f);
                     DATA_FIELD(0) = NumTo7Seg((GetL()&0xf0)>>4);
                     break;
     default      :  return BadSystemCall();
   }
   DisplayAllLeds();
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemGetDataFromKeyboard(void)
 {
   uchar key;
   /* When 'c'=0, input 4 keys, store as 16 bit data in 'HL' and
      display the data in address field.
      When 'c'=1, input 2 keys, store as 8 bit data in 'L' and
      display data in data field.
   */
   HelpLine(DATA_FROM_KEYBOARD);
   switch(GetC())
   {
     case 0x0     :  SetH(((key = ReadHexKey()<<4)));
                     ADDR_FIELD(0) = NumTo7Seg(key>>4);
                     DisplayAllLeds();

                     SetH((key = ReadHexKey()) | GetH());
                     ADDR_FIELD(1) = NumTo7Seg(key);
                     DisplayAllLeds();

                     SetL((key = ReadHexKey()<<4));
                     ADDR_FIELD(2) =  NumTo7Seg(key>>4);
                     DisplayAllLeds();

                     SetL((key = ReadHexKey()) | GetL());
                     ADDR_FIELD(3) = NumTo7Seg(key);
                     DisplayAllLeds();
                     break;

     case 0x1     :  SetL((key = ReadHexKey()<<4));
                     DATA_FIELD(0) = NumTo7Seg(key>>4);
                     DisplayAllLeds();

                     SetL((key = ReadHexKey()) | GetL());
                     DATA_FIELD(1) = NumTo7Seg(key);
                     DisplayAllLeds();
                     break;
     default      :  return BadSystemCall();
   }
   DefaultStatusLine();
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemDisplayDataUsingMemoryPointer(void)
 {
   /* display data using memory pointer
      when c = 00, displays data in status field.
           c = 01  displays data in address field.
           c = 02  displays data in data field.
           c = 03  displays data in all 8 digits.

      A zero in the corresponding segment will make that segment
      glow
   */
    switch(GetC())
    {
      case  0   :  STATUS_FIELD(0) = NumToSegment(GetMemByte(GetHL()));
                   STATUS_FIELD(1) = NumToSegment(GetMemByte(GetHL()+1));
                   break;
      case  1   :  ADDR_FIELD(0) = NumToSegment(GetMemByte(GetHL()));
                   ADDR_FIELD(1) = NumToSegment(GetMemByte(GetHL()+1));
                   ADDR_FIELD(2) = NumToSegment(GetMemByte(GetHL()+2));
                   ADDR_FIELD(3) = NumToSegment(GetMemByte(GetHL()+3));
                   break;
     case   2   :  DATA_FIELD(0) = NumToSegment(GetMemByte(GetHL()));
                   DATA_FIELD(1) = NumToSegment(GetMemByte(GetHL()+1));
                   break;
     case   3   :  STATUS_FIELD(0) = NumToSegment(GetMemByte(GetHL()));
                   STATUS_FIELD(1) = NumToSegment(GetMemByte(GetHL()+1));
                   ADDR_FIELD(0) = NumToSegment(GetMemByte(GetHL()+2));
                   ADDR_FIELD(1) = NumToSegment(GetMemByte(GetHL()+3));
                   ADDR_FIELD(2) = NumToSegment(GetMemByte(GetHL()+4));
                   ADDR_FIELD(3) = NumToSegment(GetMemByte(GetHL()+5));
                   DATA_FIELD(0) = NumToSegment(GetMemByte(GetHL()+6));
                   DATA_FIELD(1) = NumToSegment(GetMemByte(GetHL()+7));
                   break;
     default    :  return BadSystemCall();
    }
    return DisplayAllLeds();
 }
/* ----------------------------------------------------------------------*/
 int _SystemSerialInput(void)
 {
   /* serial input data from COM1/COM2
      when c =0 serial input from com1 is stored in register 'B'
      when c =1 serial input from com2 is stored in register 'B'
   */
   switch(GetC())
   {
     case  0     :   SetB(inportb(GCOM1));
                     /* 'GCOM1' is a variable defined in 'vars.h' */
                     break;
     case  1     :   SetB(inportb(GCOM2));
                     /* 'GCOM2' is a variable defined in 'vars.h' */
                     break;
     default     :   return BadSystemCall();
   }
   return 1;
 }

/* ----------------------------------------------------------------------*/
 int _SystemSerialOutput(void)
 {
   /* serial output data from COM1/COM2
      when c =0 data from register 'B' is sent to com1
      when c =1 data from register 'B' is sent to com2
   */
   switch(GetC())
   {
     case  0     :   outportb(GCOM1,GetB());
                     /* 'GCOM1' is a variable defined in 'vars.h' */
                     break;
     case  1     :   outportb(GCOM2,GetB());
                     /* 'GCOM2' is a variable defined in 'vars.h' */
                     break;
     default     :   return BadSystemCall();
   }
   return 1;
 }
/* --------------------------------------------------------------------- */
 int _SystemPrintData(void)
 {
   switch(GetC())
   {
     case   0    :  WriteToPrinter(GetB());
                    break;
                    /* print the ASCII format of B */
     case   1    :  if(GetB()>=100)/*you need to print the hundred's digit*/
                      WriteToPrinter(GetB()/100+'0');
                    if(GetB()>=10)/*you need to print the ten's digit*/
                      WriteToPrinter(((GetB()/10)%10)+'0');
                    WriteToPrinter((GetB()%10)+'0');
                    break;
     default     :  return BadSystemCall();
   }
   return 1;
 }
/* --------------------------------------------------------------------- */
 int _SystemPrintCRLF(void)
 {
  /* printf a carriage return and linefeed */
  WriteToPrinter(13);
  WriteToPrinter(10);
  return 1;
 }
/* --------------------------------------------------------------------- */
 int _SystemSerialInputExtra(void)
 {
   /* serial input data through any port
      This system call is an extra functionality and is not available in
      the vi microsystem kit

      Data is received from the port as specified by the port number
      in 'HL' pair and stored in register 'B' or register 'BC'.
      If 'D' = 0 then 1 byte data is received and stored in register 'B'
      If 'D' = 1 then 1 word data is received and stored in register
      pair 'BC'
      eg:- to receive data from port 33h, load 'HL' with 33h and call
      this function
   */
   switch(GetD())
   {
      case 0        :  SetB(inportb(GetHL()));
                       break;
      case 1        :  SetBC(inport(GetHL()));
                       break;
      default       :  return BadSystemCall();
   }
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemSerialOutputExtra(void)
 {
   /* serial output data through any port
      This system call is an extra functionality and is not available in
      the vi microsystem kit

      Data is sent to the port as specified by the port number in 'HL' pair.
      if 'D' = 0 then 1 byte of data from register 'B' is sent to the
      specified port.
      if 'D' = 1 then 1 word of data from register pair 'BC' is sent to the
      specified port.

      eg:- to receive data from port 33h, load 'HL' with 33h and call
      this function
   */
   switch(GetD())
   {
      case 0        :  outportb(GetHL(),GetB());
                       break;
      case 1        :  outport(GetHL(),GetBC());
                       break;
      default       :  return BadSystemCall();
   }
   return 1;
 }
/* ----------------------------------------------------------------------*/
 int _SystemOriginalDelay(void)
 {
    /* HL = delay value
       delay time is equal to  HL*6.9 microseconds
       We can make a delay only in milliseconds
    */
    delay(6.9*GetHL());
    return 1;
 }
/* ----------------------------------------------------------------------*/
 int PerformSystemCall(void)
 {
  /* perform various system calls depending on the value of register 'A' */
   switch(GetA())
   {
     case  0    :  return _SystemReset();
     case  1    :  return _SystemBlankDisplay();
     case  2    :  return _SystemDisplayDot();
     case  3    :  return _SystemDisplayData();
     case  4    :  return _SystemDisplayErr();
     case  5    :  return _SystemReadFromKeyboard();
     case  6    :  return _SystemCodeConversion();
     case  7    :  return _SystemLengthOfBlock();
     case  8    :  return _SystemGenerateTone();
     case  9    :  return _SystemDelay();
     case  0xa  :  return 1;    /* this has not been implemented */
     case  0xb  :  return _SystemDisplayHLData();
     case  0xc  :  return _SystemGetDataFromKeyboard();
     case  0xd  :  return _SystemDisplayDataUsingMemoryPointer();
     case  0xe  :  return _SystemSerialInput();
     case  0xf  :  return _SystemSerialOutput();
     case  0x10 :  return _SystemPrintData();
     case  0x11 :  return _SystemPrintCRLF();
     case  0x12 :  return _SystemSerialInputExtra();
     case  0x13 :  return _SystemSerialOutputExtra();
     case  0x14 :  return _SystemOriginalDelay();
     default    :  return BadSystemCall();
  }
 }
#endif