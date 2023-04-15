#ifndef __HELP_H__
 #define __HELP_H__

 #define  TOPIC_PREPEND         '\1'    /* ^A character */
 #define  DATA_PREPEND          '\2'    /* ^B character */
 #define  STRING_DATA_PREPEND   "\2"    /* string version of data prepend */

 /* this implements the help for the 8085 emulaor */

 /*  Help file has the following format :-

     Normal text in the help file is stored in plain ASCII format.

     Hypertext links are prepended and appended with ^S ('HELP_LINK')
     character.  Hence moving the cursor will highlight the text in
     between the two ^S's.  The help topic will be searched for if the
     return key is pressed when the cursor is inside a hypertext link.
     eg:- hello ^Show^S are you
     In the above example 'how' is a hypertext

     The search text for a hypertext is also formatted, and has the
     following format :- The ^A(TOPIC_PREPEND) character is appended
     and prepended ot it.
     In our example the search for the topic 'how' will be made after
     appending and prepending the ^A(TOPIC_PREPEND) character to it

     ^Ahow^A.

     This is the format in which the links to a hypertext link is stored

     The data for the the topic chosen is also appended and prepended by
     the the character ^B(DATA_PREPEND).  This is done so that more than
     one hypertext can refer to the same data.

     In our example the data for the topic would look like
     ^B
        This English word
        has 3 characters.
     ^B

     if more than one hypertext refers to the same topic then it can
     be implemented in the following manner

     ^Ahow^A
     ^Ahay^A
     ^B
        This English word
        has 3 characters.
     ^B

     Both 'how' and 'hay' share the same data
 */
 #define  HELP_SUCCESS            1 /* help initialization was successful */
 #define  GOTO_HELP_LINK          2 /* 'return' key was pressed on a help
                                        link */
 #define  SHOW_PREVIOUS_HELP      3 /* show previous help */
 #define  NOTHING_TO_DO           4
 /* a help topic is not required for the specified topic, hence
    'NOTHING TO DO' , quite obvious isn't it
 */
 #define  HELP_MEM_ALLOC_ERROR   -1 /* could not allocate a help node */
 #define  FILE_NOT_FOUND         -2 /* help file not found            */
 #define  TOPIC_NOT_FOUND        -3 /* help topic not found */
 #define  ERROR_IN_HELP_FILE     -4 /* format error in help file */


 #define  HELP_STATUS  \
(uchar *)" Esc Quit  ³  Alt+F1 Previous Help  ³ \
  Use Arrow keys to move around"
 #define  USE_HIGHLIGHT          CTRL_H
 /* use this character to enclose something you want to highlight in the
    help window
 */

 #define  HELP_LINK              CTRL_S
 #define  HELP_HIGHLIGHT         MAKEATTR(WHITE,BLACK)
 #define  HELP_NORMAL            MAKEATTR(CYAN,WHITE)
/* use this character to enclose something which has a link help window */

 #define  BUF_SIZE         256

/*---------------------------------------------------------------------*/
 int SetHelpBox(int x,int y,int width, int height)
 {
   InitBox(&HELP_BOX().b,x,y,width,height,BOX_STYLE,WHITE,CYAN);
   SetBoxTextAttr(&HELP_BOX().b,LIGHTGREEN,CYAN);
   SetBoxNormalAttr(&HELP_BOX().b,BLACK,CYAN);
   SetBoxHighlightAttr(&HELP_BOX().b,BLACK,CYAN);
   SetBoxAnotherAttr(&HELP_BOX().b,DARKGRAY,BLACK);
   return 1;
 }
/*---------------------------------------------------------------------*/
 void HelpWrite(help_box h,int x,int y,unsigned char *s)
 {
  int num;
  int attr;
  int i,j,k,next_x;
  int toggle=0;
  char *str=(char *)s;
  box b;

   b = h.b.b;  /* box of scroll box of help box */
   if(x<0 || y<0) return ;
   if(y>=b.height || x>=b.width) return ;
   num = b.width-2;
   attr = b.text_attr;
   x = b.x+x;
   y = b.y+y;
   for (k=0,j=0,--x,--y; (*s) && (num) && (x<80); s++,j++)
   {
      if(*s==USE_HIGHLIGHT || *s==DATA_PREPEND || *s==TOPIC_PREPEND
       || *s==HELP_LINK)
           ++k;
     if(*s==HELP_LINK)
     {
       for(i=j+1; *(str+i) &&  *(str+i)!=HELP_LINK ; )
                    i++;
       if(str[i])
         next_x = i; /* got a 'HELP_LINE' before end of string */
       else next_x = 0;
       toggle = !toggle;
       if(h.x>=x-b.x && h.y==y-b.y  && h.x<next_x-k && toggle)
         attr = HELP_HIGHLIGHT;  /*are you inside a highlight*/
    /*   else attr = attr==b.highlight || attr==b.another_attr
                        ?  b.text_attr : b.highlight ;*/
       else attr = toggle ? HELP_NORMAL : b.text_attr;
       continue;
     }
     else if (*s==USE_HIGHLIGHT)
     {
       attr = attr!=b.text_attr ? b.text_attr : b.highlight;
       continue;
     }
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + (unsigned char)*s;
     ++x;
     num--;
   }
   for (  ; (num--) && (x<80); x++)
     *(VIDEO[PAGE]+(y*SCREEN_WIDTH +x)) = attr + ' ';
 }
/*---------------------------------------------------------------------*/
 help_struct * AllocateOneHelpNode(uchar *s)
 {
   help_struct *h;

     if((h = (help_struct *)malloc(sizeof(help_struct)))==NULL)
            return NULL;
     h->next = h->prev = NULL;
     if(s) /* if s!=NULL */
      if((h->buffer = (uchar *)strdup((char *)s))==NULL)
      {
        free(h);
        return NULL;
      }
   return h;
 }
/*---------------------------------------------------------------------*/
 int  SearchForHelpInFile(char *search,FILE *fp)
 {
   char       s[HELP_SEARCH_LEN+2];
   char       buffer[BUF_SIZE+1];
   char        *ptr;
   help_struct *cp,*np;

    sprintf(s,"%c%s%c",TOPIC_PREPEND,search,TOPIC_PREPEND);
    /* append a ^A, this is the format in which strings that can be searched
       are stored
    */
    if(fgets(buffer,BUF_SIZE,fp)!=NULL) /* read the buffer */
    while(1)
    {
      if((ptr=strstr(buffer,s))!=NULL)
         break;/* got the string !! */
      if(fgets(buffer,BUF_SIZE,fp)==NULL) return TOPIC_NOT_FOUND;
    }
    /* got the search string hence find from where the help data begins.
       Help data is enclosed withing special control characters
       In this case it is ^B
    */
    while(1)
    {
      if(fgets(buffer,BUF_SIZE,fp)==NULL)  return ERROR_IN_HELP_FILE;
      if((ptr=strstr(buffer,STRING_DATA_PREPEND))!=NULL) break;
    }
    /* got the starting delimiter     */
    ++ptr;                /* discard the starting delimiter */
    HELP().head = NULL;   /* initialize head, just in case  */
    *(buffer+strlen(buffer)-2) = '\0';
                          /* remove the '\n' and '\r' character */
    if((HELP().head = AllocateOneHelpNode((uchar *)ptr))==NULL)
      return HELP_MEM_ALLOC_ERROR;
    cp  = HELP().head;
    ++HELP().lines_read; /* increment the number of lines read */
    while(1)
    {
      if(fgets(buffer,BUF_SIZE,fp)==NULL) return ERROR_IN_HELP_FILE;
      if(strstr(buffer,STRING_DATA_PREPEND)) break; /* end of data */
      *(buffer+strlen(buffer)-2) = '\0';
      /* remove the '\n' and '\r' character.  The help file should
         end with an empty line otherwise the last two characters
         will be lost.
      */
      if((np = AllocateOneHelpNode((uchar *)buffer))==NULL)
        return HELP_MEM_ALLOC_ERROR;
      ++HELP().lines_read;
      /* remove the '\n' and '\r' character.  The help file should
         end with an empty line otherwise the last two characters
         will be lost.
      */
      cp->next    = np;
      np->prev    = cp;
      cp          = np;
    }
   HELP().current = HELP().head;
   HELP().end     = cp;  /* end of list */
   return HELP_SUCCESS;
 }
/*---------------------------------------------------------------------*/
 int SearchForHelp(char *s)
 {
   FILE *fp;
   int  x;

   if((fp=fopen((char *)GHELP_PATH,"rb"))==NULL) return FILE_NOT_FOUND;
   x = SearchForHelpInFile(s,fp);
   fclose(fp);
   return x;
 }
/*---------------------------------------------------------------------*/
 void PrintHelpBox(void)
 {
   int i;
   help_struct *p;

    for(i=1,p=HELP().current ;i<HELP_BOX().b.height && p!=NULL; p=p->next)
      HelpWrite(HELP(),1,i++,p->buffer);
    for(   ;i<HELP_BOX().b.height ; i++)
     StringAndBlankInBox(HELP_BOX().b,1,i,(uchar *)" ");
 }
/*---------------------------------------------------------------------*/
 int PerformHelpPageUp(void)
 {
   word i;
   help_struct *p;

    for(i=0, p= HELP().current ; i<HELP_BOX().b.height-2 && p!=HELP().head
             ; i++, p = p->prev)
          ;
    HELP().current = p;
    return i;
 }
/*---------------------------------------------------------------------*/
 int PerformHelpPageDown(void)
 {
   word i;
   help_struct *p;

    for(i=0, p= HELP().current ; i<HELP_BOX().b.height-2 && p!=HELP().end
             ; i++, p = p->next)
          ;
    if(p==HELP().end) return 0;
     /* data was less than 1 page, hence no need for page down */
    HELP().current = p;
    return i;
 }
/*---------------------------------------------------------------------*/
 void PerformHelpUpArrow(void)
 {
   if(HELP().y<=0)
   {
     if(HELP().current!=HELP().head)
     HELP().current = HELP().current->prev;
   }
   else --HELP().y;
 }
/*---------------------------------------------------------------------*/
 void PerformHelpDownArrow(void)
 {
    if(HELP().y>=HELP_BOX().b.height-2)
    {
      if(HELP().current->next)  /* i.e. !NULL */
      HELP().current = HELP().current->next;
    }
    else  ++HELP().y;
 }
/*---------------------------------------------------------------------*/
 void PerformHelpEnd(void)
 {
   int i;
   int ctrl_ctr;    /* control character counter */
   help_struct *p;
   char *s;

    for(i=0,p=HELP().current ; i<HELP().y ; i++)
             p = p->next;
    s = p->buffer;  /* 's' is just a temporary */
    for(i=0,ctrl_ctr=0; s[i] ; i++)
     if(s[i]==USE_HIGHLIGHT || s[i]==DATA_PREPEND || s[i]==TOPIC_PREPEND
       || s[i]==HELP_LINK)
       ctrl_ctr++;
    HELP().x = (i=strlen(p->buffer)-ctrl_ctr) > HELP_BOX_WIDTH
               ? HELP_BOX_WIDTH-2 : i;
 }
/*---------------------------------------------------------------------*/
 char * GetNextHelpTopic(void)
 {
   int         i,j,k,x;
   int         ctrl_ctr;
   help_struct *p;
   char *s;

     for(x=0,p=HELP().current ; x<HELP().y  ; p =p->next,x++)
                      ;
     s = (char *)p->buffer;
     for(j=0,k=0 ; j<HELP().x ; k++,s++)
      if(*s!=USE_HIGHLIGHT && *s!=DATA_PREPEND && *s!=TOPIC_PREPEND
       && *s!=HELP_LINK)
           ++j;
     ctrl_ctr = k-j;
     for(i=k; i>0 && p->buffer[i] !=HELP_LINK  ; i--)
              ;
     if(i<=0)  return NULL;  /* if was not a help link */
     for(j=HELP().x+1+ctrl_ctr ; p->buffer[j] && p->buffer[j] !=HELP_LINK
                          ; j++)
              ;
     if(!p->buffer[j])  return NULL;
     /* this is actually a error in help file but we ignore it */
     for(x=i+1,k=0; x<j && x<HELP_SEARCH_LEN+i+1 ; x++,k++)
          HELP().search[k] = p->buffer[x];
     HELP().search[k] = '\0';
     return HELP().search;
 }
/*---------------------------------------------------------------------*/
 int GotoNextHighlight(void)
 {
  int   j;
  help_struct  *p;
  int  link_ctr;
  char *s;  /* this is just a temporary */
  int x,y;
  int height=0;

    for(height=0,p=HELP().current ; height<HELP().y  ; p =p->next,height++)
                     ;
    x = HELP().x;
    y = HELP().y;
    link_ctr = 0;
    s = (char *)p->buffer;
    for(j=0 ; *s && j<=x ; s++)
      if(*s!=USE_HIGHLIGHT && *s!=DATA_PREPEND && *s!=TOPIC_PREPEND
        && *s!=HELP_LINK)
          ++j;
      else if(*s==HELP_LINK) ++link_ctr;

    /* skip the current highlight */
    if(link_ctr%2)
    {
      /*'link_ctr' is odd if the cursor is inside a help link, and hence
         the current help link should be skipped
      */
      for( ; *s ;  s++)
       if(*s!=USE_HIGHLIGHT && *s!=DATA_PREPEND && *s!=TOPIC_PREPEND
            && *s!=HELP_LINK)
            ++j;
       else if(*s==HELP_LINK) break;
       if(*s) s++; /* skip the end of help link */
    }
    if(!link_ctr)
    {
      s=(char *)p->buffer;
      j = 0;
    }
    /* if no links found then start from beginning */
    while(1)
    {
      link_ctr = 0;
      /* search for next highlight */
      for( ; *s ;  s++)
       if(*s!=USE_HIGHLIGHT && *s!=DATA_PREPEND && *s!=TOPIC_PREPEND
            && *s!=HELP_LINK)
            ++j;
       else if(*s==HELP_LINK) break;
      if(*s)
      {
        if(height>HELP_BOX().b.height-2)
        {
           for( ; height ; --height)
            HELP().current = HELP().current->next;
           HELP().y = 0;
        }
        else HELP().y = y;
        return HELP().x=j;
      }
      if(p->next==NULL) break;
      p = p->next;
      ++y;
      ++height;
      x = 0;
      j = 0;
      s = (char *)p->buffer;
      /* each time I don't want to write '*p->buffer' etc */
    }
    return 0;
 }
/*---------------------------------------------------------------------*/
 int GotoPrevHighlight(void)
 {
  /* the code is very bad, don't blame me!!, because I wrote it just
     because of popular demand for 'SHIFT+TAB' combination for getting
     previous help.  I somehow managed this through trial and error
  */
  int   i,j,k,l;
  help_struct  *p,*q;
  int  link_ctr;
  char *s;  /* this is just a temporary */
  int x,y;

    for(i=0,q=p=HELP().current ; i<HELP().y  ; p =p->next,i++)
                     ;
    l = HELP().x;
    y = HELP().y;
    link_ctr = 0;
    s = (char *)p->buffer;
    /* each time I don't want to write '*p->buffer' etc */
    /* reach the starting of current highlight */
    while(1)
    {
      s = (char *)p->buffer;
      link_ctr = 0;
      for(j=0,k=0 ; j<=l ; k++)
        if(s[k]!=USE_HIGHLIGHT && s[k]!=DATA_PREPEND && s[k]!=TOPIC_PREPEND
          && s[k]!=HELP_LINK)
            ++j;
        else if(s[k]==HELP_LINK)
        {
          i=k;
          x=j;
          ++link_ctr;
        }
      if(link_ctr<2)
      {
        if(p->prev==NULL) return 0;
        /* there is no hypertext in the current line and neither can we
           we move up
        */
        else
        {
        /* there was no hypertext in the current line, but we can move
            up, to the previous line
        */
          if(p==q)
          {
            q = p = p->prev;
            y = 0;
          }
          else
          {
            p = p->prev;
            --y;
          }
          x = 0;
          l = strlen((char *)p->buffer);
          continue;
        }
      }
      if(link_ctr%2)
      {
        /* if 'link_ctr' is odd then the cursor is inside a hypertext
           hence we will have to skip the current hypertext inorder
           to go to the previous hypertext
        */
        for( --i; i && s[i]!=HELP_LINK ; --i)
         if(s[i]!=USE_HIGHLIGHT && s[i]!=DATA_PREPEND && s[i]!=TOPIC_PREPEND
           && s[i]!=HELP_LINK)
             --x;
      }

      for(--x,--i; i && s[i]!=HELP_LINK ; --i)
       if(s[i]!=USE_HIGHLIGHT && s[i]!=DATA_PREPEND && s[i]!=TOPIC_PREPEND
         && s[i]!=HELP_LINK)
           --x;
      HELP().x = x+1;
      break;
    }
    HELP().current = q;
    HELP().y       = y;
    return 1;
 }
/*---------------------------------------------------------------------*/
 int ShowHelp(void)
 {
   int x,y;

    x = wherex();
    y = wherey();
    HELP_BOX().cp = HELP_BOX().start = 0;
    HELP().x      = HELP().y         = 0;
    PrintHelpBox();
    while(1)
    {
      gotoxy(HELP_BOX().b.x+HELP().x+1,HELP_BOX().b.y+HELP().y+1);
      switch(GetTheChar(NO_POLLING))
      {
        case  RETURN      :   /* if the current topic is highlighted then
                                 goto that topic
                              */
                              if(GetNextHelpTopic())
                               return GOTO_HELP_LINK;
                              break;
        case  TAB         :   GotoNextHighlight();
                              break;
        case  SHIFT_TAB   :   GotoPrevHighlight();
                              break;

        case  ALT_F1      :   return SHOW_PREVIOUS_HELP;
        case  CTRL_UP     :   if(HELP().current->prev!=NULL)
                                 HELP().current = HELP().current->prev;
                              break;
        case  CTRL_DOWN   :   if(HELP().current->next!=NULL)
                                 HELP().current = HELP().current->next;
                              break;
        case  UP          :   PerformHelpUpArrow();
                              break;
        case  DOWN        :   PerformHelpDownArrow();
                              break;
        case  LEFT        :   if(HELP().x>0) --HELP().x;
                              break;
        case  RIGHT       :   if(HELP().x<HELP_BOX().b.width-3)
                                 ++HELP().x;
                              break;
        case  PAGE_UP     :   if(PerformHelpPageUp()) break;
                              else continue; /* no page up was needed */
        case  PAGE_DOWN   :   if(PerformHelpPageDown()) break;
                              else continue; /* no page up was needed */
        case  HOME        :   HELP().x = 0;
                              /* goto starting of current line */
                              break;
        case  END         :   PerformHelpEnd();

                              /* goto end of current line */
                              break;
        case  CTRL_HOME   :
        case  CTRL_PAGE_UP
                          :   HELP().current = HELP().head;
                              HELP().x=HELP().y = 0;
                              break;
        case  CTRL_PAGE_DOWN :
        case  CTRL_END    :   HELP().current = HELP().end;
                              HELP().x=HELP().y = 0;
                              break;
        case  ESC         :   gotoxy(x,y);
                              return 0;
        default           :   continue;
      }
      PrintHelpBox();
    }
 }
/*---------------------------------------------------------------------*/
 void DeAllocateHelp(void)
 {
   /* deallocate the help buffer */
   help_struct *p,*q;

    for(p=HELP().head ; p!=NULL ; )
    {
        q = p;
        p = p->next;
        free(q->buffer);
        free(q);
    }
    HELP().head =NULL;
 }
/*---------------------------------------------------------------------*/
 void AddToHelp(char *s)
 {
   /* add to the list of previous help screens */
   int i,j;

     if((i=HELP().prev_help_ctr)>=MAX_PREV_HELPS)
     {
       for(j=0 ; i>1  ;i--,j++)
         strcpy(HELP().prev_help[j],HELP().prev_help[j+1]);
       i = j = HELP().prev_help_ctr-1;
     }
     else i = HELP().prev_help_ctr++;
     strcpy(HELP().prev_help[i],s);
 }
/*---------------------------------------------------------------------*/
 void GotoPreviousHelp(void)
 {
   if(HELP().prev_help_ctr>1) --HELP().prev_help_ctr;
   else AddToHelp("F1");
 }
/*---------------------------------------------------------------------*/
 char *KeywordSearch(void)
 {
   int i,j;
   GSTRING[0] = '\0'; /* initialise the search string to nothing */
   /* global string defined in 'vars.h' */
   switch(SWITCH()) /* in which windown are you */
   {
     case CODE_BOX_TAB   :  GetStringFromCode(CODE_BOX().cp,(char *)GSTRING);
                            for(i=0; isspace(GSTRING[i]) ; i++)
                                            ;
                            for(j=i+1 ; GSTRING[j] && !isspace(GSTRING[j])
                                     ; j++)
                                            ;
                            GSTRING[j] = '\0';
                            memmove(GSTRING,GSTRING+i,j-i+1);
                            break;
    case  MEM_DUMP_TAB   :  strcpy((char *)GSTRING,"changing memory data");
                            break;
    case  REG_BOX_TAB    :  strcpy((char *)GSTRING,"registers");
                            break;
    case  FLAG_BOX_TAB   :  strcpy((char *)GSTRING,"flags");
                            break;
    default              :  return NULL;
   }
   return (char *)GSTRING;  /* global string defined in 'vars.h' */
 }
/*---------------------------------------------------------------------*/
 int PleaseHelp(int key,char *topic)
 {
   int  x;
   char *s;

   if(HELP().prev_help_ctr<0)
   {
      HELP().prev_help_ctr = 0;
      AddToHelp("F1");
   }
   switch(key)
   {
      case  F1        :    AddToHelp("F1");
                           break;
      case  ALT_F1    :    if(HELP().prev_help_ctr<=0)
                              AddToHelp("F1");
                           break;
      case  CTRL_F1   :    if((s=KeywordSearch())==NULL)
                              return NOTHING_TO_DO;
                           AddToHelp(s);
                           break;
      case  0         : /* you want to search for help on something */
                           AddToHelp(topic);
                           break;
   }
   while(1)
   {
     switch(SearchForHelp(HELP().prev_help[HELP().prev_help_ctr-1]))
     {
       case HELP_SUCCESS            :   DrawBox(HELP_BOX().b);
                                        PrintStatusLine(HELP_STATUS);
                                        x=ShowHelp();
                                        DeAllocateHelp();
                                        if(x==GOTO_HELP_LINK)
                                        {
                                           AddToHelp(HELP().search);
                                           continue;
                                        }
                                        else if(x==SHOW_PREVIOUS_HELP)
                                        {
                                          GotoPreviousHelp();
                                          continue;
                                        }
                                        break;
       case HELP_MEM_ALLOC_ERROR    :   DeAllocateHelp();
                                        return HELP_MEM_ALLOC_ERROR;
       case TOPIC_NOT_FOUND         :   GotoPreviousHelp();
                                        return TOPIC_NOT_FOUND;
       case ERROR_IN_HELP_FILE      :   return ERROR_IN_HELP_FILE;
       case FILE_NOT_FOUND          :   return FILE_NOT_FOUND;
     }
     return HELP_SUCCESS;
   }
 }
/*------------------------------------------------------------------------*/
 int DisplayHelp(int key,char *s)
 {
   char str[80];
   auto char *err_no_mem    = "Not enough memory to display help";
   auto char *err_no_topic  = "Help Topic not found";
   auto char *err_file_err  = "Error in help file";
   _setcursortype(_NORMALCURSOR);
   switch(PleaseHelp(key,s))
   {
     case HELP_MEM_ALLOC_ERROR    :
     _setcursortype(_NOCURSOR);
     StandardErrorMessageBox(err_no_mem);
     break;

     case TOPIC_NOT_FOUND         :
     _setcursortype(_NOCURSOR);
     StandardErrorMessageBox(err_no_topic);
     /*--HELP().prev_help_ctr;*/
     /* HELP().prev_help_ctr=0;
      since the topic was not found we reset the previous help counter */
     break;

     case ERROR_IN_HELP_FILE      :
     _setcursortype(_NOCURSOR);
     StandardErrorMessageBox(err_file_err);
     break;

     case FILE_NOT_FOUND          :
     _setcursortype(_NOCURSOR);
     sprintf(str,"  Can\'t  find help file <%s>",GHELP_FILE);
     StandardMessageBox(str);
     break;

     case  HELP_SUCCESS            :
     break;

     case  NOTHING_TO_DO           :
     break;
   }
   _setcursortype(_NOCURSOR);
   RepaintDesktop();
   return 1;
 }
/*------------------------------------------------------------------------*/
#endif