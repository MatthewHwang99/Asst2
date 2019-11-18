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
	
	numThreads = size/250;
	
	struct thread** arrThreads = (struct thread**)malloc(sizeof(struct thread*)*numThreads);
	
	int result = -1;
	
	for(int i = 0; i<numThreads; i++){
		struct thread* th = (struct thread*)malloc(sizeof(struct thread));
		pthread_t* thread_t = (pthread_t*)malloc(sizeof(pthread_t));
		th->th = thread_t;
		th->start = i*250;
		th->end = i*250+249;
		th->array = arr;
		th->target = target;
		pthread_create(thread_t, NULL, search_func, (void*)th);
		arrThreads[i] = th;
		//printf("Waiting for thread %d\n", i);
	}
	
	for(int i = 0; i<numThreads; i++){
		struct thread* temp = arrThreads[i];
		pthread_t th = *(temp->th);
		if(temp->retval != -1){
			//printf("Target(%d) found at: index %d in thread %d\n", target, th->retval, i);
			result = temp->retval;
		}
		pthread_join(th, NULL);
	}
	
	return result;
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



