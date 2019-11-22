//library with a multithread implementation of your search function

#include"multitest.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>

int info = 0;

void* search_func(void*);

struct thread{
	pthread_t* th;
	int start; //starting index
	int end; //ending index
	int target;
	int* array;
};

int search(int* arr, int size, int target, int numThreads){
	int partitionSize = size/numThreads;
	
	if(partitionSize > 250){
		printf("Error: Partition size is greater than 250. Need more threads.\n");
		exit(0);
	}
	
	int leftover = 0;
	
	if(size%numThreads!=0){
		leftover = size%numThreads;
	}
	
	if(info == 0){
		printf("Breaking the array into partitions of %d, using %d threads.\n", partitionSize, numThreads);
		info = 1;
	}
	
	struct thread** arrThreads = (struct thread**)malloc(sizeof(struct thread*)*numThreads);
	
	int result = -1;
	
	for(int i = 0; i<numThreads; i++){
		struct thread* th = (struct thread*)malloc(sizeof(struct thread));
		pthread_t* thread_t = (pthread_t*)malloc(sizeof(pthread_t));
		th->th = thread_t;
		th->array = arr;
		th->target = target;
		
		if(leftover!=0 && i == numThreads-1){
			th->start = i*partitionSize;
			th->end = size-1;
		}else{
			th->start = i*partitionSize;
			th->end = i*partitionSize+(partitionSize-1);
		}
		pthread_create(thread_t, NULL, search_func, (void*)th);
		arrThreads[i] = th;
		//printf("Waiting for thread %d\n", i);
	}
	
	for(int i = 0; i<numThreads; i++){
		struct thread* temp = arrThreads[i];
		pthread_t th = *(temp->th);
		void* retval=NULL;
		pthread_join(th, &retval);
		int* num = (int*)retval;
		if(*num != -1){
			result = *num;
		}
		
		free(num);
		free(temp);
	}
	
	return result;
}

void* search_func(void* args){
	struct thread* th = (struct thread*)args;
	int start = th->start;
	int end = th->end;
	int target = th->target;
	int* array = th->array;
	int* res = (int*)malloc(sizeof(int));
	
	for(int i = start; i<=end; i++){
		if(array[i] == target){

			*res = i;
			pthread_exit((void*)res);
		}
	}
	
	*res = -1;
	pthread_exit((void*)res);
}



