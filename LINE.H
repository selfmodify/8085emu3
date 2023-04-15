#ifndef __LINE_H__
 #define __LINE_H__

 /* The 'line input' function is defined in this file */

 #define  ATTRIBUTE    ((LIGHTGRAY<<8)+BLACK)
 #define  MAX          257

/*-------------------------------------------------------------------------*/
 int SetInsertCursor(int x)
 {
   if(x)  _setcursortype(_SOLIDCURSOR);
   else _setcursortype(_NORMALCURSOR);
   return 1;
 }
/*-------------------------------------------------------------------------*/
  void ClearEoln(int x,int y,unsigned attr,int width)
  {
   BlankLine(x,y,attr,width);
  }
/*-------------------------------------------------------------------------*/
 void InsertChar(char *temp,char ch,int ins_on,int *pos)
 {
  int i,j,len;
  char temporary[MAX];

   len = strlen(temp);
   for(i=0; i<*pos ; i++)
    temporary[i] = temp[i];
   j=i;
   temporary[j++] = ch;
   if(!ins_on) i++;
   for( ; i<len ; i++,j++)
   temporary[j] = temp[i];
   temporary[j] = 0;
   strcpy(temp,temporary);
   ++(*pos);
  }
/*-------------------------------------------------------------------------*/
  int ReadLine(char *s,int width,int max,unsigned attr)
  {
   char  temp[MAX];
   char  temporary[MAX];
   int   ch,i,j;
   int   pos=0;
   int   y_pos,x_pos;
   int   ins_on = 1;
   int   modified=1;
   int   start=0;
   int   len;  /* length of string */

    strcpy(temp,s);
    temp[width] = 0;
    x_pos = wherex();
    y_pos = wherey();
    pos = len = strlen(temp);
    do
    {
     if(modified)
     {
        ClearEoln(x_pos,y_pos,attr,width);
        PrintToScreen(x_pos,y_pos,(uchar *)temp+start,attr,width);
        modified = 0;
     }
     gotoxy(x_pos+pos-start,y_pos);
     ch = GetTheChar(NO_POLLING);

     if(ch == RETURN ) break;
     switch(ch)
     {
       case LEFT        :   if(pos > 0)
                            {
                              --pos;
                              if(start>pos)  --start;
                              modified = 1;
                            }
                            break;
       case RIGHT       :   if(pos <len)
                            {
                              ++pos;
                              if(pos>=width+start) ++start;
                              modified = 1;
                            }
                            break;
       case DEL         :   for(i=0;i<pos; i++)
                              temporary[i] = temp[i];
                             j=i++;
                             for(; i<len ; i++,j++)
                              temporary[j] = temp[i];
                             temporary[j] = 0;
                             strcpy(temp,temporary);
                             modified = 1;
                             len=strlen(temp);
                             break;

      case INSERT        :   ins_on = !ins_on;
                             SetInsertCursor(!ins_on);
                             break;
      case HOME          :   start = pos = 0;
                             modified=1;
                             break;
      case END           :   pos = strlen(temp);
                             if(pos>=width)
                               start = pos-width+2;

                             modified = 1;
                             break;

      case BACKSPACE     :  if(pos<=0) continue;
                             memmove(temp+pos-1,temp+pos,strlen(temp)-pos);
                             temp[strlen(temp)-1]=0;
                             --len;
                             --pos;
                             if(pos<start) --start;
                             modified=1;
                             break;
     case ESC             :  return -1;
     default              :  if(ch<EXTENDED)
                             {
                               if(len<max)
                               {
                                InsertChar(temp,ch,ins_on,&pos);
                                ++len;
                                if(pos>=width)
                                   ++start;
                                modified = 1;
                               }
                             }
                             break;
     }
   }
   while(1);
   strcpy(s,temp);
   return strlen(s);
  }
/*-------------------------------------------------------------------------*/
 int ReadAtPosition(int x,int y,char *s,int width,int max,unsigned attr)
 {
   int oldx,oldy;
   int ret;

    _setcursortype(_NORMALCURSOR);
    oldx = wherex();
    oldy = wherey();
    gotoxy(x,y);
    ret = ReadLine(s,width,max,attr);
    gotoxy(oldx,oldy);
    _setcursortype(_NOCURSOR);
    return ret;
 }
/*-------------------------------------------------------------------------*/

#endif