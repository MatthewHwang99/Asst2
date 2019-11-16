//library with a multithread implementation of your search function

#include "multitest.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

int search(int* arr, int size){
	/*struct thread* th = (struct thread*)malloc(sizeof(struct thread));
	pthread_t thread = (pthread_t)malloc(sizeof(pthread_t));
	
	for(int i = 0; i<6; i++){
		pthread_create()
	
	}*/
	
	for(int i = 0; i<size; i++){
		printf("%d\n", arr[i]);
	}
	 
	return 0;
}

