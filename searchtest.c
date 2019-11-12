// implements both multiprocess and multithread searches based on how it is built

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int size = 100; //supposed to test different ranges of sizes along with different step sizes
	
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
	
	return 0;
}
