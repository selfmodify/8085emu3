#ifndef _MOV_H_
 #define _MOV_H_

 /* routines which emulate the 8085 data transfer Instructions  */

/*------------------------------------------------------------------------*/
 int _MviB(void)
 {
   SetB(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviC(void)
 {
   SetC(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviD(void)
 {
   SetD(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviE(void)
 {
   SetE(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviH(void)
 {
   SetH(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviL(void)
 {
   SetL(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviM(void)
 {
   SetMemByte(GetHL(),GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }
/*------------------------------------------------------------------------*/
 int _MviA(void)
 {
   SetA(GetMemByte(GetIP()+1));
   return  MVI_LEN; /* increment ip by 2 bytes */
 }

/*様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様*/
/*様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様*/

 int _MovBB(void)
 {
   SetB(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovBC(void)
 {
   SetB(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBD(void)
 {
   SetB(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBE(void)
 {
   SetB(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBH(void)
 {
   SetB(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBL(void)
 {
   SetB(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBM(void)
 {
   SetB(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovBA(void)
 {
   SetB(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovCB(void)
 {
   SetC(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovCC(void)
 {
   SetC(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCD(void)
 {
   SetC(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCE(void)
 {
   SetC(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCH(void)
 {
   SetC(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCL(void)
 {
   SetC(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCM(void)
 {
   SetC(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovCA(void)
 {
   SetC(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovDB(void)
 {
   SetD(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovDC(void)
 {
   SetD(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDD(void)
 {
   SetD(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDE(void)
 {
   SetD(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDH(void)
 {
   SetD(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDL(void)
 {
   SetD(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDM(void)
 {
   SetD(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovDA(void)
 {
   SetD(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovEB(void)
 {
   SetE(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovEC(void)
 {
   SetE(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovED(void)
 {
   SetE(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovEE(void)
 {
   SetE(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovEH(void)
 {
   SetE(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovEL(void)
 {
   SetE(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovEM(void)
 {
   SetE(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovEA(void)
 {
   SetE(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovHB(void)
 {
   SetH(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovHC(void)
 {
   SetH(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHD(void)
 {
   SetH(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHE(void)
 {
   SetH(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHH(void)
 {
   SetH(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHL(void)
 {
   SetH(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHM(void)
 {
   SetH(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovHA(void)
 {
   SetH(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovLB(void)
 {
   SetL(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovLC(void)
 {
   SetL(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLD(void)
 {
   SetL(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLE(void)
 {
   SetL(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLH(void)
 {
   SetL(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLL(void)
 {
   SetL(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLM(void)
 {
   SetL(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovLA(void)
 {
   SetL(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovMB(void)
 {
   SetMemByte(GetHL(),GetB());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovMC(void)
 {
   SetMemByte(GetHL(),GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovMD(void)
 {
   SetMemByte(GetHL(),GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovME(void)
 {
   SetMemByte(GetHL(),GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovMH(void)
 {
   SetMemByte(GetHL(),GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovML(void)
 {
   SetMemByte(GetHL(),GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovMA(void)
 {
   SetMemByte(GetHL(),GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

 int _MovAB(void)
 {
   SetA(GetB());
   return  MOV_LEN; /* return the no. of bytes by which IP should be incremented*/
 }
/*------------------------------------------------------------------------*/
 int _MovAC(void)
 {
   SetA(GetC());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAD(void)
 {
   SetA(GetD());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAE(void)
 {
   SetA(GetE());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAH(void)
 {
   SetA(GetH());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAL(void)
 {
   SetA(GetL());
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAM(void)
 {
   SetA(GetMemByte(GetHL()));
   return  MOV_LEN;
 }
/*------------------------------------------------------------------------*/
 int _MovAA(void)
 {
   SetA(GetA());
   return  MOV_LEN;
 }

/*------------------------------------------------------------------------*/

#endif