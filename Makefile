all:
	echo "Error: must make with 'proc' or 'thread'"

proc: searchtest.c multitest_proc.c multitest.h
	gcc -std=c99 -g -c multitest_proc.c -o multitest.o
	gcc -std=c99 -g searchtest.c -o searchtest multitest.o -lm

thread: searchtest.c multitest_thread.c multitest.h
	gcc -std=c99 -g -lpthread -c multitest_thread.c -o multitest.o
	gcc -std=c99 -g -lpthread searchtest.c -o searchtest multitest.o -lm


clean:
	rm -rf searchtest
	rm -rf multitest.o
	rm -rf resulttest.txt
