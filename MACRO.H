#ifndef _MACRO_H_
 #define _MACRO_H_

  /* The various macro's used throughout the program go into this file */

  #define CharToNum(x)      ((x>='0' && x<='9') ? x-'0' : \
                            (toupper(x)>'A') ? x -'A' + 10: x - 'a' + 10)
  #define NumToChar(x)      ((x>=0 && x<=9) ? x+'0' : x - 10 + 'A' )

  /* converts and hex character to its value */

  /* macros for accessing the various lexical parts of the 8085 machine */
  #define KIT                 _8085         /* THE 8085 mu-p Kit */
  #define INSTR()             (KIT->i)
  #define LINES_ASSEMBLED()   (INSTR().lines_assembled)
  #define BREAK_POINT(i)      (INSTR().break_points[i])
  #define LAST_BREAK_POINT()  (INSTR().last_break_point)
  #define BREAK_PT_CTR()      (INSTR().bk_ctr)
  /* break point counter, i.e., how many break points have occured */

  #define INTR()              (KIT->intr_info)
  #define EXECUTING()         (INTR().executing)
  #define INTERRUPTED()       (INTR().interrupted)
  #define INTERRUPT_NUMBER()  (INTR().interrupt_number)

  #define INCREMENT()         (KIT->m.incr)
  #define PTR_TO_SIMU()       (KIT->m.simu)
  #define RUN()               (KIT->m.run)
  #define STEP_OVER()         (KIT->m.step_over)
  #define OLD_IP()            (KIT->m.old_ip)
  #define STEP_OVER_IP()      (KIT->m.step_over_ip)
  #define CODE()              (KIT->m.code)
  #define SWITCH()            (KIT->m.tab)

  #define LEX_STRUCT          (state)
  #define TOKEN()             (LEX_STRUCT.token)
  #define STRING()            (LEX_STRUCT.str)
  #define CURRENT()           (LEX_STRUCT.current)
  #define LAST()              (LEX_STRUCT.last)
  #define BUFFER()            (LEX_STRUCT.buffer)
  #define LINE_NUMBER()       (LEX_STRUCT.line_number)
  #define PTR()               (KIT->cpu.ptr)

  #define SET_STATUS(x)       (KIT->status |= (x))
  #define RESET_STATUS(x)     (KIT->status = x)
  #define CLEAR_STATUS(x)     (KIT->status &= ~x)

  /* clear that particular status */
  #define GET_STATUS()        (KIT->status)
  #define SYM_TABLE()         (table)      /* the symbol table */
  #define _MNEMONIC()         (mnemonic)
  /* this array contains the name of the function its length and parsing
     function
  */

  #define FORMAT(x)            (x)
  /* This function can be used to format a string.
     This is used when the equivalent mnemonic is required from a given
     machine code
  */
  #define MAC_OP_TABLE          mot
  #define SIMULATE(x)           MAC_OP_TABLE[x].Simulate

  #define _LED                  (KIT->led)
  #define STATUS_FIELD(x)       (_LED.status_field[x])
  #define ADDR_FIELD(x)         (_LED.addr_field[x])
  #define DATA_FIELD(x)         (_LED.data_field[x])
  #define LED_DISPLAY           (KIT->display.led_display)


  #define MEM_DUMP_BOX()        (KIT->display.dump)
  #define CODE_BOX()            (KIT->display.code)
  #define REG_DISPLAY_BOX()     (KIT->display.regs)
  #define FLAG_BOX()            (KIT->display.flag)
  #define STACK_BOX()           (KIT->display.stack)
  #define HELP_BOX()            (help.b)
  #define HELP()                (help)

#endif