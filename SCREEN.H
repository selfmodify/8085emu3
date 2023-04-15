#ifndef __SCREEN_H__
 #define __SCREEN_H__

 /* lowlevel routines to print directly to the video ram */

 #define  SCREEN_WIDTH                 80
 #define  SCREEN_HEIGHT                25
 #define  DEFAULT_COLOUR               ((LIGHTGRAY<<8)+BLACK)
 #define  VIDEO                        (screen.video)
 #define  PAGE                         (screen.page)

 #define  MAKEATTR(back,fore)          (((back<<4)+fore)<<8)

 extern   unsigned char GSTATUS_LINE[257]; /* defined in 'vars.h' */
 extern   unsigned char GMENU_BAR[257];   /* defined in 'vars.h' */

 typedef unsigned int (far * s_arrayptr); /* far pointer to video memory*/

 typedef struct
 {
    s_arrayptr video[8];
    int        page;
    unsigned   one_screen[80*25];
 }screen_struct;

 static screen_struct screen;

 #define TEMP_LEN               255
 #define SCREEN_TEMP()          screen_temp

 static unsigned char screen_temp[TEMP_LEN+1];
 /* this variable can be used for temporary purpose */

/*----------------------------------------------------------------------*/
 s_arrayptr FindMode(void)
 {
   /* int gd,gm; */
  /* detectgraph(&gd, &gm);
   if (gd == HERCMONO) return (s_arrayptr) MK_FP(0xB000, 0);
   else return (s_arrayptr) MK_FP(0xB800, 0);
  */
   if(peek(0x40,0x63)!=0x3d4)
   {
     printf("\nYou require a EGA/VGA or higher adapter");
     exit(0);
   }
   if(((peek(0x40,0x10)&0x30)>>4)!=2)
   {
     printf("\nYou require a Colour 80x25 console to run this programme");
     exit(0);
   }
  /* look into the Bios Data area */
  if(*(unsigned char *)(0x400049l)==7)  return (s_arrayptr) MK_FP(0xB000, 0);
   else return (s_arrayptr) MK_FP(0xB800, 0);
 }
/*----------------------------------------------------------------------*/
 screen_struct InitScreen(void)
 {
  int i;

   screen.video[0] = FindMode(); /* find the starting address */
   for(i=1;i<8;i++)
     screen.video[i] = screen.video[0]+2048*i;
     /* starting address of the ith  page */
   textmode(C80);  /* set the text mode to colour 80 */
   memset(screen_temp,'-',255); /* fill the string with '-' */
   return screen;
 }
/*----------------------------------------------------------------------*/
 void WriteToScreen(int x,int y,unsigned char *s,unsigned attr)
 {
   /* num - Number of characters to print */
   for (--x,--y; (*s) && (x<80); s++,x++)
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + (unsigned char)*s;
 }
/*----------------------------------------------------------------------*/
 void PrintToScreen(int x,int y,unsigned char *s,unsigned attr,int num)
 {
   /* num - Number of characters to print
      print till the 'num' >0 or *s!='\0'
   */
   for (--x,--y; (*s) && (num--) && (x<80); s++,x++)
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + (unsigned char)*s;
 }
/*----------------------------------------------------------------------*/
 void PrintToScreenN(int x,int y,unsigned char c,unsigned attr,int num)
 {
   /* num - Number of times to print the characters 'c' */
   for (--x,--y; (num--) && (x<80); x++)
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + c;
 }
/*----------------------------------------------------------------------*/
 void PrintCharToScreen(int x,int y,unsigned char c,unsigned attr)
 {
   *(VIDEO[PAGE]+((--y)*SCREEN_WIDTH +(--x))) = attr + (unsigned char)c;
 }
/*----------------------------------------------------------------------*/
 void BlankLine(int x,int y,unsigned attr,int num)
 {
   /* num - Number of characters to print */
   for (--x,--y; (num--) && (x<80); x++)
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + (unsigned char)' ';
 }
/*----------------------------------------------------------------------*/
 void FillScreen(unsigned char x,unsigned attr)
 {/* fill the screen with the given character using the attribute 'attr'*/
   int i;
   unsigned char s[81];

    for(i=0; i<80 ; i++)
       s[i] = x;
    s[i] = 0;  /* append the NULL character */
    for(i=1; i<26 ; i++)
     WriteToScreen(1,i,s,attr);
 }
/*----------------------------------------------------------------------*/
 void StatusLine(unsigned char *s)
 {
   static unsigned int attr = MAKEATTR(WHITE,BLACK);
   BlankLine(1,25,attr,SCREEN_WIDTH);
   WriteToScreen(1,25,s,attr);
 }
/*----------------------------------------------------------------------*/
 void BlankStatusLine(void)
 {
   static unsigned int attr = MAKEATTR(WHITE,BLACK);
   BlankLine(1,25,attr,SCREEN_WIDTH);
 }
/*----------------------------------------------------------------------*/
 void PrintStatusLine(unsigned char *s)
 {
   strcpy((char *)GSTATUS_LINE,(char *)s);
   /* copy to the global variable so that screen refresh functions can
    use this */
   StatusLine(GSTATUS_LINE);
 }
/*----------------------------------------------------------------------*/
 void StatusLineAt(int x,int y,char *s)
 {
   /* print status line at given position 'x','y' */
   static unsigned int attr = MAKEATTR(WHITE,BLACK);
   BlankLine(x,y,attr,SCREEN_WIDTH);
   WriteToScreen(x,y,(unsigned char *)s,attr);
 }
/*----------------------------------------------------------------------*/
 char *GetPreviousStatusLine(void)
 {
   return (char *)GSTATUS_LINE;
   /* return a pointer to the previous status line*/
 }
/*----------------------------------------------------------------------*/
 char *GetPreviousMenuBar(void)
 {
   return (char *)GMENU_BAR;
   /* return a pointer to the previous status line*/
 }
/*----------------------------------------------------------------------*/
 void DisplayPreviousStatusLine(void)
 {
   StatusLine(GSTATUS_LINE);
   /* the previous status line is stored in the global variable
      'GSTATUS_LINE'
   */
 }
/*----------------------------------------------------------------------*/
 void MenuBar(unsigned char *s)
 {
   static unsigned int attr = MAKEATTR(WHITE,BLACK);
   BlankLine(1,1,attr,SCREEN_WIDTH);
   WriteToScreen(1,1,s,attr);
 }
/*----------------------------------------------------------------------*/
 void PrintMenuBar(unsigned char *s)
 {
   strcpy((char *)GMENU_BAR,(char *)s);
   /* copy to the global variable so that screen refresh functions can
    use this */
   MenuBar(GMENU_BAR);
 }
/*----------------------------------------------------------------------*/


#endif