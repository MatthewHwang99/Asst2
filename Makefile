all: searchtest

proc: searchtest.c multitest_proc.o
	gcc -std=c99 -g searchtest.c -o searchtest multitest_proc.o
	
multitest_proc: multitest_proc.c multitest.h
	gcc -std=c99 -g -c multitest_proc.c -o multitest_proc.o

thread: searchtest.c multitest_thread.o
	gcc -std=c99 -g searchtest.c -o searchtest multitest_thread.o

multitest_thread: multitest_thread.c multitest.h
	gcc -std=c99 -g -c -lpthread multitest_thread.c -o multitest_thread.o

clean:
	rm -rf searchtest
	rm -rf multitest_thread.o
	rm -rf multitest_proc.o
