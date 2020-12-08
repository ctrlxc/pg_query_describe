CC ::= gcc
CPP ::= g++
CFLAGS ::= $(CFLAGS) -I/usr/include/postgresql -Wall
LDFLAGS ::= $(LDFLAGS) -L/usr/lib/postgresql/12/lib -Wl,-rpath,/usr/lib/postgresql/12/lib
LDLIBS ::= $(LDLIBS) -lecpg

PROGRAM ::= pg_query_describe

build:
	ecpg describe.pgc
	$(CC) $(CFLAGS) -c describe.c -o describe.o
	$(CPP) $(CFLAGS) -c main.cpp -o main.o
	$(CPP) $(LDFLAGS) describe.o main.o $(LDLIBS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) describe.o main.o
