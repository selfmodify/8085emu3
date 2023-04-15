 #include <stdio.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include <sys\stat.h>
 #include <io.h>

 /* creates a font table from a font file.  The output from this program
    can be redirected to a file.   The ouput from this program is used in
    the file 'box.h'
 */
 void main(int argc,char *argv[])
 {
   int handle;
   char buffer[4096];
   int  i,j=16;

    if(argc<2)
    {
      printf("\nCreates a table from a font file");
      printf("\nUsage %s <filename>",argv[0]);
      exit(0);
    }
    if((handle=open(argv[1],O_BINARY|O_RDONLY))==-1)
    {
      printf("\nCannot open <%s>",argv[1]);
      exit(0);
    }
    if(read(handle,buffer,4096)==-1)
    {
       printf("\nCannot read from file <%s>",argv[1]);
       exit(0);
    }
    for(i=0; i<4096 ; i++,j++)
    {
      if(j>=16)
      {
        printf("\\\n");
        j = 0;
      }
      printf("\\x%02x",(buffer[i]&0xff));
    }
 }




