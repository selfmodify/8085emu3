#ifndef _VARS_H_
 #define _VARS_H_

 /* the various global variables go here */

 machine_ptr                _8085  = NULL;
 /* this is the pointer to the currently running machine */
 machine_ptr                m;    /* a global machine */
 unsigned  long             data; /* general purpose variables */
 unsigned  long	            addr;
 long                       X;
 uchar                      code;  /* for code */
 unsigned		    r1;  /* as numericals equivalents for registers*/
 unsigned                   r2;
 char * BEYOND_MEMORY       = " W0Nyrgy";  /* what's this */
 extern instruction_struct   mnemonic[];
 extern machine_op_struct    mot[MAX_INSTRUCTIONS];

 lex_struct                 state;   /* lexical state */

 uchar status_string[] =
 "  F1-Help  Alt+S-Stop  Alt+X-Quit  F2-BkPt  F4"\
"  F7-Trace  F8-Step  F9-Run  F10";
 unsigned                    TRAP_INTR_VECTOR     = 200;
 /* use 80x86 interrupt 200 to invoke the 'TRAP' interrupt routine */
 unsigned                    RST_5_5_INTR_VECTOR  = 201;
 /* use 80x86 interrupt 201 to invoke the 'RST 5.5' interrupt routine */
 unsigned                    RST_6_5_INTR_VECTOR  = 202;
 /* use 80x86 interrupt 202 to invoke the 'RST 6.5' interrupt routine */
 unsigned                    RST_7_5_INTR_VECTOR  = 203;
 /* use 80x86 interrupt 203 to invoke the 'RST 7.5' interrupt routine */

 int    REAL_OUT=0;
 /* if 'REAL_OUT' is '0' then the 'out' instruction does not send the byte
    to the actual port but instead sets the value of an internal data
    structure.
    When its value is '1' the 'out' instruction sends the byte to the
    actual output port.
    When assigned 3 data is sent to the port as well as the data
    structure.

    This has not been implemented
 */
 int    REAL_IN=0;   /* same as above, but used for 'in' instruction */

 unsigned  GCOM1      =      0x3f8;    /* address of serial port 1  */
 unsigned  GCOM2      =      0x2f8;    /* address of serial port 2  */
 unsigned  GPRNPORT   =      0;        /* 0=LPT1, 1=LPT2, 2=LPT3 */

 void interrupt (far * OldTrapVector)(void);
 void interrupt (far * OldRst_5_5_Vector)(void);
 void interrupt (far * OldRst_6_5_Vector)(void);
 void interrupt (far * OldRst_7_5_Vector)(void);

 word page_up[256];  /* used for moving one page up through the code */
 /* this is used by the function 'PerformPageUp' in 'Extra.h' */
 uchar GMENU_BAR[257];  /* global variable */
 /* first print you string  into this variable and then call the 'MenuBar'
    function
 */
 uchar GSTATUS_LINE[257];  /* global variable */
 /* first print you string  into this variable and then call the 'StatusLine'
    function
 */

 uchar  *GHELP_FILE  = (uchar *)"8085HLP.HLP";
  /* default name for help file */

 uchar GSTRING[257];
 /* this is a global string and can be used by any function, I don't
    wan't to 'malloc' and 'free' for small things
 */

 char  GSTARTUP_PATH[257]; /* full path from where the program was started*/
 char  GHELP_PATH[257]; /* full path for help file */
 int   GERROR_COUNT = MAX_ERRORS;
 /* The number of errors that have occured.  The machine quits if you
    encounters 'MAX_ERRORS'
 */

 symbol_table table;    /* the symbol table */

 help_box  help;

 int  num_quotes;  /* number of quotes!! */
 char *quotes[] = {
 /* A project wouldn't be complete without what we call 'kuntrac' in
    Malayalam
 */
 {"Programmed by V. Kumar\
 of S8 Computer Science, College of Engineering Trivandrum, Kerala\
 ®India¯. zip code - 695 016"},
 {"Committee - A group of men who individually can do nothing but as a\
 group decide that nothing can be done  - Fred Allen"},
 {"Egoist, n. A person of low taste more interested in himself than in me\
  - Ambrose Bierce"},
 {"The one serious conviction that man should have is that nothing is to be\
 taken too seriously - Nicholas Murray Butler"},
 {"People only think a thing's worth believing in if it's hard to believe -\
 Armiger Barclay"},
 {"The noblest of all dogs is the hot dog; it feeds the hand that bites it -\
 Robert W. Chambers"},
 {"Excercise is bunk.  If you are healthy, you don't need it: if you are\
 sick,you shouldn't take it. - Henry Ford"},
 {"Computers can figure out all kinds of problems, except the things in the\
 world that just don't add up - James Magary"},
 {"The chains of habit are too weak to be felt until they are too strong to\
 be broken - Samuel Johnson"},
 {"Life can only be understood backward; but it must be live forwards\
 - Soren Kierkegaard"},
 {"A chain is as strong as its weakest link"},
 {"Genius is one percent inspiration and ninety-nine percent perspiration\
 - Thomas Edison"},
 {"To be alive at any instant is an indication and opportunity to be\
 happy"},
 {"The difference between reality and fiction? Fiction has to make\
 sense - Tom clancy"},
 {"Solitude is a good place to visit, but a poor place to stay - Josh\
 Billings"},
 {"The smoothest thing about a used car is the salesman."},
 {"\"That\'s the guy I\'m laying for,\" said the little hen as the farmer\
 crossed the yard."},
 {"Garden : A thing of beauty and a job forever"},
 {"Money used to talk, but now it goes without saying."},
 {"When you have removed the impossible, whatever remains, however\
 improbable it might be, will be the truth"},
 {"One life - a little gleam of Time between two Eternities - Thomas\
  Carlyle"},
 {"I always wanted to be someone - now I think that I should have been\
 more specific"},
 {"Tact is the ability to describe others as they see themselves -\
 Abraham Lincoln"},
 {"Infant prodigy - A small child with highly imaginative parents-\
 R.H. Creaeese."},
 {"A cake of soap never gets dirty - V. Kumar"},
 {"If you have trouble forecasting the future correctly, do it frequently\
 at very short intervals"},
 {"Familiarity breeds attempt"},
 {"To iterate is humane, to recurse is divine"},
 {"All my life I wanted to be someone; I guess I should have been more\
 specific"},
 {"\"What's another word for Thesaurus?\" -- Steven Wright"},
 {"Laughter is the closest distance between two people.  -  Victor Borge"},
 {"If you're not part of the solution, you're part of the precipitate."},
 {"A radioactive cat has eighteen half-lives."},
 {"Admiration, n.:  Our polite recognition of another\'s resemblance to\
 ourselves.  -- Ambrose Bierce, The Devil\'s Dictionary"},
 {"It's the thought, if any, that counts!"},
 {"Test-tube babies shouldn't throw stones."},
 {"See - the thing is - I'm an absolutist.  I mean, kind of ... in a\
 way ..."},
 {"Got Mole problems?   -   Call Avogadro at 6.02 x 10^23"},
 {"\'In Conclusion: \' The phrase that wakes up the audience."},
 {"The most welcome guest is the one who knows when to go home."},
 {"An onion a day keeps everyone away."},
 {"It's difficult to look spick if you  have too much span."},

 {NULL}
 };
/*------------------------------------------------------------------------*/
#endif