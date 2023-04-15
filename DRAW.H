#ifndef __DRAW_H__
 #define __DRAW_H__
 #include <time.h>


 /* functions to draw the initial screen and various boxes */

 void SetBlink(int x)
 {
   union REGS r;
    r.h.ah = 0x10;
    r.h.al = 0x3;
    r.h.bl = !!x;     /* enable or disable intensity */
    int86(0x10,&r,&r);
 }
/*-----------------------------------------------------------------------*/
 void DisplayProjectGroupName(void)
 {
   box b;

   auto char *msg[] = {
       {"A program to emulate a æp Kit based on the Intel 8085 æp."},
       {"Version 3.00,  [8085 Inside]  (Unregistered)"},
       {" "},
                   {"Éßß°²²²²²²²°ßßÉ"},
                   {"Éßß°±±±5±±±°ßßÉ     "},
                   {"Éßß°²²²8²²²°ßßÉ         "},
                   {"Éßß°±±±0±±±°ßßÉ             "},
                   {"Éßß°²²²8²²²°ßßÉ                 "},
                   {"Éßß°±±±±±±±°ßßÉ                     "},
       {" "},
       {"Programmed by     --     V. Kumar"},
       {"Email id  -  kumar__v@hotmail.com"},
       {"If you find this program useful and wish to support it,"},
       {"the author requests that you send a $10(or less or more ;-) )"},
       {"donation to:"},

       {""},

       {"TC 21/2O50,  Single Street,  Karamana,"},
       {"Trivandrum - 695 002,  Kerala, India."},
       {""},

       {NULL}
     };
   int i=1;
   int height;
   int width;
   char s[257];
   int x;
   char *str;
   int len;
   int k;

   strcpy(s,GetPreviousMenuBar());
   PrintMenuBar((uchar *)\
   "             ® Challenge   Has   Always   Offered   Satisfaction ¯");
   for(i=0,width=0 ; msg[i] ; i++)
      if(strlen(msg[i])>width) width=strlen(msg[i]);
   height = i;
   InitBox(&b,3,3,74,19,BOX_STYLE,YELLOW,LIGHTBLUE);
   SetBoxTextAttr(&b,WHITE,LIGHTBLUE);
   SetBoxHighlightAttr(&b,BLACK,LIGHTBLUE);
   gettext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   DrawBox(b);
   for(i=0; i<3 ; i++)
     StringAndBlankInBox(b,(b.width-strlen(msg[i]))/2,i+1,(uchar *)msg[i]);
   for(   ; i<10 ; i++)
     HighlightAndBlankInBox(b,(b.width-strlen(msg[i]))/2+6,i+1,
           (uchar *)msg[i],b.highlight);

   for(   ; i<12 ; i++)
     StringAndBlankInBox(b,(b.width-strlen(msg[i]))/2,i+1,(uchar *)msg[i]);

   for(   ; i<16 ; i++)
     HighlightAndBlankInBox(b,(b.width-strlen(msg[i]))/2,i+1,
           (uchar *)msg[i],b.highlight);

   for( ; i<height ; i++)
     StringAndBlankInBox(b,(b.width-strlen(msg[i]))/2,i+1,(uchar *)msg[i]);

   strcpy((char *)GSTRING,GetPreviousStatusLine());
   while(!kbhit())
   {
    clock_t t1;

     i = 80;
     BlankStatusLine();
     randomize();
     if((x = random(num_quotes))>num_quotes/2)
       x=random(num_quotes);
     str =quotes[x];
     len = strlen(str);

     for( ; i>0 && !kbhit(); i--)
     {
       t1 = clock();      /* get the clock tick */
       StatusLineAt(i,25,str);
       while((clock()-t1)<3)
           ;              /* make delay independent of machine speed */
     }
     for( k=1 ; i>-len && ! kbhit(); i--,k++)
     {
       t1 = clock();      /* get the clock tick */
       StatusLineAt(1,25,str+k);
       while((clock()-t1)<3)
           ;              /* make delay independent of machine speed */
     }
   }

   if(getch()==0) getch(); /*read a character */
   puttext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   PrintMenuBar((uchar *)s);  /* restore the old menu bar */
   PrintStatusLine(GSTRING);
 }
/*------------------------------------------------------------------------*/
 void RefreshAllBoxes(void)
 {
   DrawBox(CODE_BOX().b);        /* draw the memory display box */
   DrawBox(REG_DISPLAY_BOX().b);   /* draw the register display box */
   DrawBox(LED_DISPLAY);
   DrawBox(MEM_DUMP_BOX().b);
   DrawBox(FLAG_BOX().b);
   DrawBox(STACK_BOX().b);
   DisplayAllLeds();
 }
/*------------------------------------------------------------------------*/
 void InitDisplay(uchar *s)
 {
   FillScreen(177,MAKEATTR(LIGHTGRAY,BLUE));
   DefaultStatusLine();
   PrintMenuBar(s);
 }
/*------------------------------------------------------------------------*/
 void StartupDisplay(void)
 {
   FillScreen(177,MAKEATTR(LIGHTGRAY,BLUE));
   DefaultStatusLine();
   DisplayProjectGroupName();
 }
/*------------------------------------------------------------------------*/
 void RepaintAllBoxes(void)
 {
   RefreshAllBoxes();
   PrintRegisters();    /* display the contents of registers in a box */
   PrintCode();         /* display the instructions */
   PrintMemoryDump();   /* display memory dump      */
   PrintFlags();        /* display the flags        */
   PrintStackDump();    /* display stack dump       */
 }
/*------------------------------------------------------------------------*/
 void RepaintDesktop(void)
 {
   InitDisplay(GMENU_BAR);
   RepaintAllBoxes();
   DisplayPreviousStatusLine();
   gotoxy(1,1);
 }
/*-----------------------------------------------------------------------*/

#endif