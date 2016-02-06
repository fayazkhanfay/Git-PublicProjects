story: story.c simpleio.o
	gcc -o story story.c simpleio.o
outline: outline.c simpleio.o
	gcc -o outline outline.c simpleio.o
scheck.o: scheck.c scheck.h
	gcc -c scheck.c
scheck_tst: scheck_tst.c scheck.h scheck.o 
	gcc -o scheck_tst scheck_tst.c scheck.c