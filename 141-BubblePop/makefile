simpleio: simpleio.h simpleio.c
	gcc -c simpleio.c
bboard: simpleio.h bboard.h bboard.c 
	gcc -c bboard.c
bpop: bboard.h simpleio.h bpop.c
	gcc bpop.c bboard.o simpleio.o -o bpop

