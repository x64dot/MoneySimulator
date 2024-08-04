CFLAGS := -Wall -O3 -c
BFLAGS := -Wall -o money-sim

money-sim: main.o core.o
	g++ $(BFLAGS) main.o core.o
main.o:
	g++ $(CFLAGS) main.cpp
core.o:
	g++ $(CFLAGS) core.cpp
