link.o:	Queue.h Queue.cpp Parent.h Parent.cpp main.h main.cpp main_functions.cpp Ordered.h Ordered.cpp Stack.h Stack.cpp Unordered.h Unordered.cpp
	g++ -c Parent.cpp Queue.cpp Ordered.cpp Stack.cpp Unordered.cpp main_functions.cpp main.cpp

link:	Parent.o Queue.o Ordered.o Stack.o Unordered.o main_functions.o main.o
	g++ Parent.o Queue.o Ordered.o Stack.o Unordered.o main_functions.o main.o -o link

clean:	
	rm Parent.o Queue.o Ordered.o Stack.o Unordered.o main_functions.o main.o link