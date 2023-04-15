#include <dos.h>
#pragma inline          /* for inline assembly code */

 void LowLevelRemap(char *remapped_text)
 {
   #if (__TURBOC__ <= 0x18d)

   unsigned off,segg;

   off  = FP_OFF(remapped_text);
   segg = FP_SEG(remapped_text);

     asm mov ax,4352        ;
     asm mov bx,0           ;
     asm mov bx, 4096       ;
     asm mov cx, 256        ;
     asm mov dx, 0          ;
     asm push es
     asm push bp
     asm mov es, segg       ;
     asm mov bp, off        ;
     asm int 16
     asm pop bp
     asm pop es
 #else
 struct REGPACK r;
     r.r_ax = 0x1100;
     r.r_bx = 0;
     r.r_bx = 16<<8;
     r.r_cx = 256;
     r.r_dx = 0;
     r.r_es = FP_SEG(remapped_text);
     r.r_bp = FP_OFF(remapped_text);
     intr(0x10,&r);
 #endif
 }