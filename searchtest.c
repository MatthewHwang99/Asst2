// implements both multiprocess and multithread searches based on how it is built
#include<stdio.h>
#include<stdlib.h>
#include"multitest.h"

void rescramble(int, int*, int);

void rescramble(int prevIndex, int* arr, int size){
	int r = rand() % size;
	
	int temp = arr[r];
	arr[r] = arr[prevIndex];
	arr[prevIndex] = temp;
	
	return;
}

int main(int argc, char** argv){
	int size = 50000; //supposed to test different ranges of sizes along with different step sizes
	int* arr = (int*)malloc(size*sizeof(int));
	int target = 14242;
	
	//generate list in sequence
	for(int i = 0; i<size; i++){
		arr[i] = i;
	}
	
	int r; int temp;
	//scramble list
	for(int i = 0; i<size; i++){
		r = rand() % size;
		temp = arr[i];
		arr[i] = arr[r];
		arr[r] = temp;
	}
	
	/*for(int i = 0; i<size; i++){
		printf("%d, ", arr[i]);
	}*/
	
	struct timeval start, end;
	unsigned long timeA = 0;
	
	//running the test 3 times to see if rescramble works
	for(int i = 0; i<1; i++){
		gettimeofday(&start, 0);
		int targetFound = search(arr, size, target);
		//rescramble(targetFound, arr, size);
		gettimeofday(&end, 0);
		
		time += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
	}
	
	/*gettimeofday(&start, 0);
	for(int i = 0; i<size; i++){
		if(arr[i] == target){
			break;
		}
	}
	gettimeofday(&end, 0);
	timeB += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;*/
	
	printf("Total run time: %lu microseconds.\n", timeA);
	
	return 0;
}
