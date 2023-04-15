#ifndef __INPUT_H__
 #define __INPUT_H__

  /* various functions to read from keyboard */

  #include <bios.h>

  #ifndef _KEYBRD_READY
    #define _KEYBRD_READY        1
  #endif

  #ifndef _KEYBRD_SHIFTSTATUS
   #define _KEYBRD_SHIFTSTATUS   2
  #endif

/*
  #define  POLLING               2  these have been defined in '8085.c'
  #define  NO_POLLING            3  for global access
*/

  #define  BACKSPACE             8
  #define  TAB                   9
  #define  CTRL_A                1
  #define  CTRL_H                8
  #define  NEWLINE              10
  #define  ESC                  27
  #define  RETURN               13
  #define  CTRL_G                7
  #define  CTRL_R               18
  #define  CTRL_T               20
  #define  CTRL_Y               25
  #define  CTRL_S               19

  #define  PLUS_KEY            43
  #define  MINUS_KEY           45

  #define  SHIFT_TAB           ( 15+EXTENDED)
  #define  UP                  ( 72+EXTENDED)
  #define  CTRL_UP             (141+EXTENDED)
  #define  DOWN                ( 80+EXTENDED)
  #define  CTRL_DOWN           (145+EXTENDED)
  #define  LEFT                ( 75+EXTENDED)
  #define  RIGHT               ( 77+EXTENDED)
  #define  HOME                ( 71+EXTENDED)
  #define  END                 ( 79+EXTENDED)
  #define  DEL                 ( 83+EXTENDED)
  #define  INSERT              ( 82+EXTENDED)
  #define  CTRL_LEFT           (115+EXTENDED)
  #define  CTRL_RIGHT          (116+EXTENDED)
  #define  PAGE_UP             ( 73+EXTENDED)
  #define  PAGE_DOWN           ( 81+EXTENDED)
  #define  CTRL_HOME           (119+EXTENDED)
  #define  CTRL_END            (117+EXTENDED)
  #define  CTRL_PAGE_UP        (132+EXTENDED)
  #define  CTRL_PAGE_DOWN      (118+EXTENDED)
  #define  CTRL_F9             (102+EXTENDED)
  #define  ALT_BACKSPACE       ( 14+EXTENDED)

  /* #define  F1                  (59 +EXTENDED)*/
  /* #define for 'F1' is required in 'myerror.h' hence it is being moved
     forward
  */
  #define  F2                  (60 +EXTENDED)
  #define  F3                  (61 +EXTENDED)
  #define  F4                  (62 +EXTENDED)
  #define  F5                  (63 +EXTENDED)
  #define  F6                  (64 +EXTENDED)
  #define  F7                  (65 +EXTENDED)
  #define  F8                  (66 +EXTENDED)
  #define  F9                  (67 +EXTENDED)
  #define  F10                 (68 +EXTENDED)
  #define  F11                 (133+EXTENDED)
  #define  F12                 (134+EXTENDED)
  #define  ALT_X               (45 +EXTENDED)
  #define  ALT_S               (31 +EXTENDED)
  #define  ALT_F3              (106+EXTENDED)
  #define  ALT_F1              (104+EXTENDED)
  #define  CTRL_F1             (94 +EXTENDED)

  #define  CTRL_Q              17
  #define  QUIT_KEY            ALT_X  /* use this to quit the machine */
  #define  STOP_KEY            ALT_S  /* use this to stop the machine */

/*-----------------------------------------------------------------------*/
 int GetTheChar(int x)
 {
  int ch=0;
    if(x==NO_POLLING)
      ch = (ch=getch())==0 ? getch()+EXTENDED : ch;
    else if(kbhit())
     ch = (ch=getch())==0 ? getch()+EXTENDED : ch;
    return ch;
 }
/*-----------------------------------------------------------------------*/
 int InputBox(int x,int y,int width,int max,char *prompt,char *s)
 {
  box b;

   InitBox(&b,x,y,width,4,BOX_STYLE,WHITE,LIGHTGRAY);
   SetBoxTextAttr(&b,BLACK,LIGHTGRAY);
   SetBoxNormalAttr(&b,BLACK,WHITE);
   gettext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   DrawBox(b);
   StringAndBlankInBox(b,1,1,(unsigned char *)prompt);
   x =ReadAtPosition(x+2,y+2,s,width-4,max,b.normal);
   puttext(b.x,b.y,b.x+b.width+2,b.y+b.height+2,screen.one_screen);
   return x;
 }
/*-----------------------------------------------------------------------*/
 int StandardInputBox(char *prompt,char *s)
 {

   return InputBox(5,11,70,129,prompt,s);
 }
#endif __INPUT_H__