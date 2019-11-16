all:
	echo "Error: must make with 'proc' or 'thread'"

proc: searchtest.c multitest_proc.c multitest.h
	gcc -std=c99 -g -c multitest_proc.c -o multitest.o
	gcc -std=c99 -g searchtest.c -o searchtest multitest.o

thread: searchtest.c multitest_thread.c multitest.h
	gcc -std=c99 -g -c -lpthread multitest_thread.c -o multitest.o
	gcc -std=c99 -g searchtest.c -o searchtest multitest.o


clean:
	rm -rf searchtest
	rm -rf multitest_thread.o
	rm -rf multitest_proc.o
