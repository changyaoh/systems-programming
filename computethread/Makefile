app:computethreadmain.o computethread.o randsafe.o doneflag.o globalerror.o sharedsum.o showresults.o
	gcc -g -o app computethreadmain.o computethread.o randsafe.o doneflag.o globalerror.o sharedsum.o showresults.o -lpthread -lm
computethreadmain.o:computethreadmain.c computethread.h doneflag.h globalerror.h sharedsum.h showresults.h
	gcc -g -c -o computethreadmain.o computethreadmain.c
computethread.o:computethread.c computethread.h doneflag.h globalerror.h randsafe.h sharedsum.h 
	gcc -g -c -o computethread.o computethread.c
randsafe.o:randsafe.c randsafe.h
	gcc -g -c -o randsafe.o randsafe.c
doneflag.o:doneflag.c doneflag.h
	gcc -g -c -o doneflag.o doneflag.c
globalerror.o:globalerror.c globalerror.h	
	gcc -g -c -o globalerror.o globalerror.c
sharedsum.o:sharedsum.c sharedsum.h globalerror.h
	gcc -g -c -o sharedsum.o sharedsum.c
showresults.o:showresults.c showresults.h
	gcc -g -c -o showresults.o showresults.c
