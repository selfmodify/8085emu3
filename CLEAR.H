
 #define COLOURS     16       /* number of colours */
 #define RGB         3
 #define INCR        1


#if 0

 int ReadDacs(char *buf)
 {
   unsigned old_es;
   /* Read the RGB combination of colours into the buffer 'buf' */

    old_es  = _ES;
    _ES     = FP_SEG(buf);   /* segment of buffer */
    _DX     = FP_OFF(buf);   /* offset of buffer */
    _AX     = 0x1017;        /* function number */
    _BX     = 1;             /* first colour register */
    _CX     = 0x0f;          /* number of colour register */
    geninterrupt(0x10);
    _ES     = old_es;        /* restore the old Extra segment */
    return 1;
 }
/* ---------------------------------------------------------------------- */
 int UpdateBuffer(char *buf)
 {
   int i;
   int once=0;
    for(i=0; i<RGB*COLOURS ; i++)
    if(buf[i]>0)
    {
      once =1;
      buf[i] -= INCR;
    }
   return once;
 }
/* ---------------------------------------------------------------------- */
 int WriteDacs(char *buf)
 {
   unsigned old_es;
   /* Read the RGB combination of colours into the buffer 'buf' */

    old_es  = _ES;
    _ES     = FP_SEG(buf);   /* segment of buffer */
    _DX     = FP_OFF(buf);   /* offset of buffer */
    _AX     = 0x1012;        /* function number */
    _BX     = 1;             /* first colour register */
    _CX     = 0x0f;          /* number of colour register */
    geninterrupt(0x10);
    _ES     = old_es;        /* restore the old Extra segment */
    return 1;
 }
/* ---------------------------------------------------------------------- */
 int Brighten(int count)
 {
  char save[RGB*COLOURS],buf[RGB*COLOURS];
  clock_t t1;
  int  i=24,ret=1;

  ReadDacs(save);
  while(ret && (i>0))
  {
     t1 = clock();
     ReadDacs(buf);
     ret=UpdateBuffer(buf);
     while((clock()-t1)<count)
             ;
     WriteDacs(buf);
     i--;
  }
  clrscr();
  WriteDacs(save);
  return 1;
 }
/* ---------------------------------------------------------------------- */

#endif


 void ClearFromTop(int row,int col,int nrow,int ncol,int effect)
 {
   int i,j;
   clock_t t1;

   for(i=row; i<=row+nrow-1 ; i++)
   {
     t1 = clock();
     for(j=col ; j<=col+ncol-1 ; j++)
     {
        PrintToScreenN(j,i,' ',2,1);
        PrintToScreenN(j,26-i,' ',2,1);
     }
     if(effect==1)
      while(clock()-t1<2)
           ;
   }
 }
/*-----------------------------------------------------------------------*/
 void ClearFromSide(int row,int col,int nrow,int ncol,int effect)
 {
   int i,j;
   clock_t t1;

   for(i=row; i<=row+nrow-1; i++)
   {
     t1 = clock();
     for(j=col ; j<=col+ncol-1 ; j++)
     {
        PrintToScreenN(i,j,' ',2,1);
        PrintToScreenN(81-i,26-j,' ',2,1);
     }
     if(effect==1)
        while(clock()-t1<1)
           ;
   }
 }
/*-----------------------------------------------------------------------*/
#if 0
 void ClearAround(int effect)
 {
  int i;
  clock_t t1;

    for(i=1;i<=13 ;i++)
    {
      t1 = clock();
      ClearFromTop(i,1,1,80,0);
      while(clock()-t1<2)
            ;
      ClearFromSide(i,1,1,40,0);
    }
 }
/*-----------------------------------------------------------------------*/
#endif

 void ClearScreen(void)
 {
   /*PrintToScreenN(int x,int y,unsigned char c,unsigned attr,int num)*/
   /* ClearFromTop(1,1,24,80,1);*/
   /* ClearFromSide(1,1,40,25,1);*/
   switch(random(2)+1)
   {
      case 1        :    ClearFromTop(1,1,13,80,1);
                         break;

      default       :    ClearFromSide(1,1,40,25,1);
                         break;
     /* case 3        :    Brighten(2);
                         break;*/
   }
   clrscr();
 }
/*-----------------------------------------------------------------------*/