// implements both multiprocess and multithread searches based on how it is built
#include<stdio.h>
#include<stdlib.h>
#include"multitest.h"

void rescramble(int, int*, int);
int mysearch(int, int, int);

void rescramble(int prevIndex, int* arr, int size){
	int r = rand() % size;
	
	int temp = arr[r];
	arr[r] = arr[prevIndex];
	arr[prevIndex] = temp;
	
	return;
}


int mysearch(int start, int end, int target){ //returns the index where the target was found
	for(int i = 0; i<size; i++){
		if(array[i] == target){
			return i;
		}
	}
	
	return -1; //if target not found in that range
}

int main(int argc, char** argv){
	int size = 1000; //supposed to test different ranges of sizes along with different step sizes
	int* arr = (int*)malloc(size*sizeof(int));
		
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
		printf("%d\n", arr[i]);
	}*/
	
	search(arr, size);
	
	return 0;
}
