CC=g++

default: main main.cpp

main: main.cpp
	$(CC) main.cpp -o main

clean:
	-rm -f  main