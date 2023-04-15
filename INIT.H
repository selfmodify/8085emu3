#ifndef __INIT_H__
 #define __INIT_H_

 /* The various initializing routines go into this file */

/*------------------------------------------------------------------------*/
 machine * SetMachine(machine *mac)
 {
  machine *m;

   m     = KIT; /* get the previous machine */
   KIT   = mac;  /* this is not a Apple macintosh */
   return  m;     /* return the previous machine */
 }
/*------------------------------------------------------------------------*/
 void SaveVectors(void)
 {
   /* get the old values for vectors for 'TRAP_VECTOR' and 'RST_5_5 etc'
      vectors from the IVT
   */
   OldTrapVector     = getvect(TRAP_INTR_VECTOR);
   OldRst_5_5_Vector = getvect(RST_5_5_INTR_VECTOR);
   OldRst_6_5_Vector = getvect(RST_6_5_INTR_VECTOR);
   OldRst_7_5_Vector = getvect(RST_7_5_INTR_VECTOR);
 }
/*-----------------------------------------------------------------------*/
 void RestoreOldVectors(void)
 {
   /* restore the old values for vectors for 'TRAP_VECTOR' and 'RST_5_5 etc'
      vectors from the IVT
   */
   setvect(TRAP_INTR_VECTOR,OldTrapVector);
   setvect(RST_5_5_INTR_VECTOR,OldRst_5_5_Vector);
   setvect(RST_6_5_INTR_VECTOR,OldRst_6_5_Vector);
   setvect(RST_7_5_INTR_VECTOR,OldRst_7_5_Vector);
 }
/*-----------------------------------------------------------------------*/
 void InitTheBoxes(void)
 {
    SetCodeBox(4,3,23,11);       /* initialize the code display box       */
    SetRegisterBox(32,3,15,11);  /* initialize the register display box   */
    SetMemDumpBox(52,3,12,11);   /* initialize the memory dump display box*/
    SetFlagBox(69,3,7,6);        /* initialize the flag display box       */
    SetStackBox(58,17,18,5);     /* initialize the stack display box      */
    SetHelpBox(3,3,HELP_BOX_WIDTH,19);/* initialize the help box          */
    SetLedDisplayBox(4,17,TOTAL_LEDS*LED_LEN+9,5);
 }
/*-----------------------------------------------------------------------*/
 void AllocateMachine(void)
 {
   /* allocate the necessary 'ram' and the structure from heap, and
      assign it to the global variable 'm'.
      If that is not possible then we simply exit.
   */
    if((m=(machine_ptr) malloc(sizeof(machine)))==NULL)
    {
      printf("\n Fatal error : Not enough memory to run machine");
      exit(0);
    }
 }
/*-----------------------------------------------------------------------*/
 void ReleaseMachine(void)
 {
   free(m);          /* free the allocated memory */
 }
/*-----------------------------------------------------------------------*/
 int InitMachine(machine *m)
 {
   int x[]={6,91,79,102,109,125,7,127};
   /* initialize the LEDs to display '1 2 3 .. ' etc */
   int i,incr;
    SetMachine(m);
    ClearMemory();           /* clear the entire by filling zeroes */
    SetIP(DEFAULT_IP);       /* by default all programs start here */
    PTR() = DEFAULT_KICKOFF; /* by default start placing programs here */
    InitTheBoxes();          /* initialize the box coordinates colors etc */
    SetImmediate(0);
    SetFlag(0);
    SetSP(MAIN_MEMORY-0x10);     /* initialize stack to a default location*/
    RESET_STATUS(0);
    EXECUTING()   = 0;
    INTERRUPTED() = 0;  /* set the variable 'interrupted' to 0 */
    InitIsrCode();      /* set the interrupt routines, currently
                           these are just 'RET' instructions */
    InitLexStruct(&LEX_STRUCT);
    for(i=0,incr=0; incr<2 ; incr++,i++)
     STATUS_FIELD(incr) = x[i];
    for(incr=0; incr<4 ; incr++,i++)
     ADDR_FIELD(incr) = x[i];
    for(incr=0; incr<2 ; incr++,i++)
     DATA_FIELD(incr) = x[i];
    InitSymbolTable();  /* set the symbol table counter to zero */
    InitInterruptMask();
    BREAK_PT_CTR() = 0;  /* no break points have been defined by default*/
    GERROR_COUNT = MAX_ERRORS;
    return 1;
 }
/*------------------------------------------------------------------------*/
 void CleanUpFunction(void)
 {
   SetBlink(1);    /* enable blinking */
   Restore8x16Font();   /* restore the default font */
   RestoreOldVectors();
 }
/*------------------------------------------------------------------------*/
 InitializePrinterPort(int prnnumber)
 {
   _AX = 0x0100;   /* initialize the specified parallel port */
   _DX = prnnumber; /* printer number (0=LPT1,1=LPT2,2=LPT3)  */
   geninterrupt(0x17);
   return _AX>>4;   /* return AH */
 }
/*-----------------------------------------------------------------------*/
 void Init(char *s)
 {
  int i;

   printf("\nอออออออออออออออออออออออออออออออออออออออออออออออออออออ");
   printf("\nAn 8085 emulator : Programmed by\n");
   printf("\nV. Kumar\n");
   InitScreen();
    /* find the starting address of video ram.  The above function also
       checks to see if you have a EGA/VGA or above card installed and if
       it dosen't find one then the program terminates
    */
   InitializePrinterPort(GPRNPORT); /* initialize the printer port */
   AllocateMachine();
   /* allocate necessary amount of memory for the virtual machine from
      heap.  If there is not enough memory, then the function terminates
      the program after printing an error message
   */
   textmode(C80); /* set to text mode colour , 80 rows */
   strcpy(GSTARTUP_PATH,s);
   for(i=strlen(GSTARTUP_PATH); i>0 ; i--)
     if(GSTARTUP_PATH[i] =='\\' || GSTARTUP_PATH[i]==':') break;
   GSTARTUP_PATH[i+1] = '\0';
   strcpy(GHELP_PATH,GSTARTUP_PATH);
   strcat(GHELP_PATH,(char *)GHELP_FILE);
   SaveVectors();
   SetNewVectors();
   SetBlink(0);  /* disable blinking */
   UnmangleName();
   #ifdef USE_REMAPPING
     SetSeparatorChar((char *)SCREEN_TEMP(),REMAPPED,TEMP_LEN);
     RemapCharacter();
   #endif
   textcolor(WHITE);
   textbackground(BLACK);
   clrscr();
   for(i=0; quotes[i] ; i++)
          ;
   num_quotes = i; /* this is the maximum number of quotes!!*/
   HELP().prev_help_ctr=0;  /* initialize the previous help counter */
   AddToHelp("F1");
 }
/*-----------------------------------------------------------------------*/


#endif