//library with a multithread implementation of your search function

#include"multitest.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>

void* search_func(void*);
struct thread{
	pthread_t* th;
	int retval; //index that the target was found, -1 if target wasn't found
	int start; //starting index
	int end; //ending index
	int target;
	int* array;
};

int search(int* arr, int size, int target){
	int numThreads;
	
	/*if(size % 250 == 0){
		numThreads = size / 250;
	}*/
	
	numThreads = size/100;
	
	int result;
	
	for(int i = 0; i<numThreads; i++){
		struct thread* th = (struct thread*)malloc(sizeof(struct thread));
		pthread_t thread_t = (pthread_t)malloc(sizeof(pthread_t));
		th->start = i*250;
		th->end = i*250+249;
		th->array = arr;
		th->target = target;
		pthread_create(&thread_t, NULL, search_func, (void*)th);
		//printf("Waiting for thread %d\n", i);
		pthread_join(thread_t, NULL);
		if(th->retval != -1){
			//printf("Target(%d) found at: index %d in thread %d\n", target, th->retval, i);
			return th->retval;
		}
	}
	
	return -1;
}

void* search_func(void* args){
	struct thread* th = (struct thread*)args;
	int start = th->start;
	int end = th->end;
	int target = th->target;
	int* array = th->array;
	
	for(int i = start; i<end; i++){
		if(array[i] == target){
			th->retval = i;
			pthread_exit(NULL);
		}
	}
	
	th->retval = -1;
	pthread_exit(NULL);
}



