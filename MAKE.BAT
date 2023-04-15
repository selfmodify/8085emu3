@REM make file for use with Turbo C. V 1.5
@REM A linker and an assembler are also necessary (generally TC has this)

@REM For compilation with borland C/C++ use 8085.prj
tcc -mm  -O1 -G  -a -I\tc\include -L\tc\lib %1 %2 8085.c remap.c
