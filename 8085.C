#ifndef __MEDIUM__
/*  #error can be compiled only under medium model*/
#endif

 /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
 /*                                                                       */
 /*                                                                       */
 /*                A Program to Emulate an 8085 mu-p Kit                  */
 /*                                                                       */
 /*                        Programmed By V. Kumar                         */
 /*                                                                       */
 /*           This should be compiled only under Medium model             */
 /*                                                                       */
 /*                                                                       */
 /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

 /*  main program of the 8085 Emulator */

 #define  ERROR_IN_MACHINE      -1

 #define  POLLING               2
 #define  NO_POLLING            3
 #define  EXTENDED              300
 #define  F1                   (59 +EXTENDED)
 /* This is used by the function 'GetTheChar' */

 #define   USE_REMAPPING
 #ifndef   USE_REMAPPING
     #define BOX_STYLE          SINGLE_BOX
 #else
     #define BOX_STYLE          REMAPPED
 #endif


 #include       "include.h"   /* contains the name of files to be included */

/*-----------------------------------------------------------------------*/
 int MakeMachineFromFile(FILE *fp)
 {
  long x;

   rewind(fp);
   printf("\n€ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ€");
   printf("\n€    (Pass 1)     €");
   printf("\n€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€");
   printf("\n ");
   LINE_NUMBER()=0;
   if((x=StoreSymbolsInTable(fp))<0)
   /* store symbols in the symbol table and return the number of
      instructions assembled or return an error code
   */
   {
     /* this part may never execute !!*/
     SetAndPrintError((int )x);
     return 0;
   }

   LINES_ASSEMBLED() = x;
   SetIP(DEFAULT_IP);       /* by default all programs start here */
   PTR() = DEFAULT_KICKOFF; /* by default start placing programs here */

   rewind(fp);
   printf("\n€ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ€");
   printf("\n€    (Pass 2)     €");
   printf("\n€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€");
   printf("\n ");
   LINE_NUMBER()=0;
   for( ; !(GET_STATUS() & SEVERE_ERROR) ; )
   {
     if(CURRENT()==EOLN || CURRENT()==EOI)
     {
       /* This means buffer is empty, hence read another line */
       if(fgets(BUFFER(),LINE_LENGTH,fp)==NULL) break;
       LINE_NUMBER()++;
       STRING() = BUFFER();
     }
     if((x=ParseLex())<0)
     {
       if(!SetAndPrintError((int )x))
         break; /* 'SetAndPrintError' issued an error hence break */
       /* got an error hence skip till end of line */
       while(((x=Advance(0))!=EOLN) && x!=EOI)
              ;
     }
   }
   if(GET_STATUS() & ANY_ERROR)
   {
      SET_STATUS(SEVERE_ERROR);
      return 0;
   }
   printf("\nSuccess : No errors found ");
   InitSymbolTable();
   /*
      set the symbol table counter to zero so that symbols are no longer
      accessible from command line
   */
   return 1;
 }
/*------------------------------------------------------------------------*/
 int OpenFileAndMakeMachine(char *s)
 {
  int ret =1;
  FILE *fp;


   if((fp=fopen(s,"rt"))==NULL) return FILE_NOT_FOUND;
   InitMachine(m); /* the global machine 'm' defined in 'vars.h' */
   if(!MakeMachineFromFile(fp)) return ERROR_IN_MACHINE;
   fclose(fp);
   return ret;
 }
/*-----------------------------------------------------------------------*/
 int BrowseThrough(char *fname)
 {
  int c;
  char  newfile[257];
  char *msg=\
    "    F1 Help    F2 New    F3 Open    Alt+X Quit    F6 Reload from disk";

    PrintFlags();        /* display flags            */
    PrintRegisters();    /* display the contents of registers in a box */
    PrintStatusLine((uchar *)msg);
    SWITCH() = CODE_BOX_TAB;  /* switch to 'code box' */
    while(1)
    {
      PrintCode();         /* display the instructions */
      PrintMemoryDump();   /* display memory dump      */
      c = GetTheChar(NO_POLLING);
      switch(c)
      {
        case F2          :    newfile[0] = '\0';
                              fname[0] = '\0';
                              return F2;
        case F3          :    newfile[0] = '\0';
                              if(StandardInputBox(" Enter new file name",
                                 newfile)!=-1)
                              {
                                strcpy(fname,(char *)newfile);
                                 /* got a new file */
                                return 1;
                              }
                              break;
        case  QUIT_KEY   :    return QUIT_KEY;
        case  F6         :    return F6;
        case  F10        :    DisplayProjectGroupName();
                              break;
        case  ALT_F1     :
        case  CTRL_F1    :
        case  F1         :    DisplayHelp(c,NULL);
                              PrintStatusLine((uchar *)msg);
                              continue;
        case  F12        :    SWITCH() = CODE_BOX_TAB;
                              continue;
        case  SHIFT_TAB  :
        case  TAB        :    if(SWITCH()==CODE_BOX_TAB)
                                SWITCH()=MEM_DUMP_TAB;
                              else SWITCH()=CODE_BOX_TAB;
                               /* switch to next window */
                              continue;

        case  F5         :
        case  CTRL_G     :     GoToPosition();
                               continue;
        case  CTRL_A     :
        case  HOME       :
        case  END        :
        case  PAGE_UP    :
        case  PAGE_DOWN  :
        case  UP         :
        case  F11        :
        case  DOWN       :   if(SWITCH()==CODE_BOX_TAB)
                                 MoveCodeDumpPointer(c);
                             else if(SWITCH()==MEM_DUMP_TAB)
                                   MoveMemDumpPointer(c);
                             continue;
      }
      PrintStatusLine((uchar *)msg);
    }
 }
/*-----------------------------------------------------------------------*/
 int ErrorMessage(int num)
 {
   if(num>=0) return 0;
   SET_STATUS(SEVERE_ERROR);
   StandardErrorMessageBox(error_msg[-(num+1)]);
   return GET_STATUS();
 }
/*-----------------------------------------------------------------------*/
 int DisplayRunErrors(void)
 {

   if(GET_STATUS() & STACK_OVERFLOW)        ErrorMessage(STACK_OVER_ERROR);
   else if(GET_STATUS() & IP_BEYOND_MEMORY) ErrorMessage(EXECUTE_ERROR);
   else if(GET_STATUS() & INVALID_OP)       ErrorMessage(INVALID_OPCODE);
   else if(GET_STATUS() & READ_FAULT)       ErrorMessage(READ_SEG_FAULT);
   else if(GET_STATUS() & WRITE_FAULT)      ErrorMessage(WRITE_SEG_FAULT);
   else if(GET_STATUS() & STACK_UNDERFLOW)  ErrorMessage(STACK_UNDER_ERROR);
   else if(GET_STATUS() & BADSYSTEMCALL)    ErrorMessage(BAD_SYSTEM_CALL);
   return 1;
 }
/* --------------------------------------------------------------------- */
 int DesktopManager(char *fname)
 {
  int   ch;
  int   x;
  char  oldfile[257];
  char  f[257]; /* just a temporary, I don't want to disturb 'fname' */
  int   runnable=1;  /* can the machine be run */
  static int   starting=1;
  int    len;

   strcpy(oldfile,fname);
   strcpy(f,oldfile);
   while(1)
   {
     if(*f)
     {
        clrscr();
        if((x=OpenFileAndMakeMachine(f))==FILE_NOT_FOUND)
        {
           sprintf((char *)GSTRING,"  Could not open <%s>",f);
           /* 'GSTRING' is a global string defined in 'vars.h' */
           StandardErrorMessageBox((char *)GSTRING);
           strcpy(f,oldfile);
           RepaintDesktop();
           sprintf((char *)GMENU_BAR,\
           "               ≥   No file Loaded ≥  8085 Êp Kit Emulator");
           PrintMenuBar(GMENU_BAR);
           runnable = 0;
        }
        else if(x==ERROR_IN_MACHINE)
        {
          printf("\nCannot Run machine Severe errors");
          printf("\nMax physical Memory size %#x\n",MAIN_MEMORY-1);
          return 0;
        }
        else
        {
           len = strlen(f);
           len = len>25 ? len-25 : 0;
           /* len is used to patch up long path names, i.e., only the last
              25 characters including the filename are displayed at the most
           */
           sprintf(GMENU_BAR,"               ≥   File :- %-25s  %s",
           f+len,"≥  8085 Êp Kit Emulator");
           runnable = 1;
        }
        PrintReady();
     }
     else
     {
      InitMachine(m); /* the global machine 'm' defined in 'vars.h'*/
      sprintf((char *)GMENU_BAR,\
      "               ≥   No file Loaded ≥  8085 Êp Kit Emulator");
      PrintReady();
      runnable = 1;
     }
     if(runnable)
     {
       if(starting)
       {
         gotoxy(1,1);
         StartupDisplay();  /* display the startup message */
         starting = 0;
       }
       InitDisplay((uchar *)GMENU_BAR);
       PrintReady();
       gotoxy(1,1);
       if((ch=RunTheMachine())==0)
         DisplayRunErrors();
         /* RepaintDesktop();*/
       if(ch==QUIT_KEY) return 1;
       if(*f)
       {
         len = strlen(f);
         len = len>25 ? len-25 : 0;
         /* len is used to patch up long path names, i.e., only the last
            25 characters including the filename are displayed at the most
         */
         sprintf(GMENU_BAR,"               ≥   File :- %-25s  %s ",f+len,\
                "≥  8085 Êp Kit Emulator");
       }
       else  sprintf(GMENU_BAR,
       "               ≥   No file Loaded ≥  8085 Êp Kit Emulator    ");
        PrintMenuBar((uchar *)GMENU_BAR);
        PrintStopped();
     }
     if(BrowseThrough(f)==QUIT_KEY) break;
     /* return value is F6 then re load from disk and run the machine */
   }
   return 1;
 }
/* --------------------------------------------------------------------- */
 int main(int argc,char *argv[])
 {
  int ret;
   _setcursortype(_NOCURSOR);
   Init(argv[0]);    /* Initialize (this is defined in 'init.h') */
   InitMachine(m);   /* initialize the machine under any circumstances */
   /* 'm' is a global variable defined in 'vars.h' */
   if((ret=DesktopManager(argc<2 ? NULL : argv[1]))!=0)
    ClearScreen();  /* clear the screen otherwise you see a blinking display */
   CleanUpFunction();
   _setcursortype(_NORMALCURSOR);
   printf("\n**********************************************");
   printf("\n*   Thank You for using the 8085 Emulator    *");
   printf("\n*   Programmed by V.Kumar                    *");
   printf("\n*   Email - kumar__v@hotmail.com             *");
   printf("\n**********************************************\n");
   return ret;
 }
