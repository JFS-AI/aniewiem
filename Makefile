main: main.cpp worki.o
	g++ @opcjeCpp main.cpp worki.o -o main

worki.o: worki.cpp worki.h
	g++ @opcjeCpp worki.cpp -c

main2: main.cpp worki2.o
	g++ @opcjeCpp main.cpp worki2.o -o main

worki2.o: worki2.cpp worki2.h
	g++ @opcjeCpp worki2.cpp -c

main3: main.cpp worki3.o
	g++ @opcjeCpp main.cpp worki3.o -o main

worki3.o: worki3.cpp worki3.h
	g++ @opcjeCpp worki3.cpp -c

main31: main.cpp worki31.o
	g++ @opcjeCpp main.cpp worki31.o -o main

worki31.o: worki31.cpp worki3.h
	g++ @opcjeCpp worki31.cpp -c

main32: main.cpp worki32.o
	g++ @opcjeCpp main.cpp worki32.o -o main

worki32.o: worki32.cpp worki3.h
	g++ @opcjeCpp worki32.cpp -c

clear:
	rm *.o
