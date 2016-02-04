

simpleio.o: simpleio.h simpleio.c
	gcc -c simpleio.c

quiz: quiz.c simpleio.o
	gcc -o quiz quiz.c simpleio.o 
      
hist: hist.c 
	gcc -o hist hist.c

util.o: util.h util.c
	gcc -c util.c

util_tst: util_tst.c util.o
	make util.o
	gcc -o util_tst util_tst.c util.o