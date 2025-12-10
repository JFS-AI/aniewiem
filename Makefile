main.e: main.cpp worki.o
	g++ @opcjeCpp main.cpp worki.o -o main.e

worki.o: worki.cpp worki.h
	g++ @opcjeCpp worki.cpp -c

clear:
	rm *.o
	rm *.e
