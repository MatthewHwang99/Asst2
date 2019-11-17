//library with a multithread implementation of your search function

#include"multitest.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>

struct thread{
	pthread_t* th;
	int retval; //index that the target was found, -1 if target wasn't found
	int start; //starting index
	int end; //ending index
};

int search(int* arr, int size, int target){
	int numThreads;
	
	if(size % 250 == 0){
		numThreads = size / 250;
	}

	//struct thread* th = (struct thread*)malloc(sizeof(struct thread));
	//pthread_t thread_t = (pthread_t)malloc(sizeof(pthread_t));
	
	for(int i = 0; i<numThreads; i++){
		//th->start = i*250;
		//th->end = i*250+249;
		//pthread_create(&thread_t, NULL, (void*) th);
		printf("%d, %d\n", i*250, i*250+249);
	
	}
	
	/*for(int i = 0; i<size; i++){
		printf("%d, ", arr[i]);
	}*/
	 
	return 0;
}



