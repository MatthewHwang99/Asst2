// implements both multiprocess and multithread searches based on how it is built
#include<stdio.h>
#include<stdlib.h>
#include"multitest.h"

void rescramble(int, int*, int);

void rescramble(int prevIndex, int* arr, int size){
<<<<<<< HEAD
	int r = rand()%size;
	while(r==prevIndex){
		r = rand() % size;
	}
	
	int temp = arr[r];
	arr[r] = arr[prevIndex];
	arr[prevIndex] = temp;
	
	return;
}

int main(int argc, char** argv){
	int size = 20000; //supposed to test different ranges of sizes along with different step sizes
	int* arr = (int*)malloc(size*sizeof(int));
	int target = 2500;
	
	//generate list in sequence
=======
  srand(time(0));
  int r = rand() % size;
  int temp = arr[r];
  arr[r] = arr[prevIndex];
  arr[prevIndex] = temp;
  return;
}

int main(int argc, char** argv){
  int size = 20000; //supposed to test different ranges of sizes along with different step sizes
  int* arr = (int*)malloc(size*sizeof(int));
  int target = 25;
  srand(time(0));
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
  /*	
>>>>>>> f9a5b6268714cde49aa52a754000bd257f7bdf15
	for(int i = 0; i<size; i++){
	printf("%d, ", arr[i]);
	}
<<<<<<< HEAD
	
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
	unsigned long time = 0;
	//unsigned long time2 = 0;
	
	//running the test 3 times to see if rescramble works
	for(int i = 0; i<10; i++){
		gettimeofday(&start, 0);
		int targetFound = search(arr, size, target);
		printf("Target %d found at index %d\n", target, targetFound);
		gettimeofday(&end, 0);
		
		time += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
		
		rescramble(targetFound, arr, size);
	}
	
	time = time/10;
	
	/*for(int i = 0; i<10; i++){
		gettimeofday(&start, 0);
		for(int i = 0; i<size; i++){
			if(arr[i] == target){
				break;
				rescramble(i, arr, size);
			}
		}
		gettimeofday(&end, 0);
		time2 += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
	}*/
	
	
	printf("Total run time: %lu microseconds.\n", time);
	//printf("Total run time: %lu microseconds.\n", time2);
	
	return 0;
=======
  */
  //running the test 3 times to see if rescramble works
  for(int i = 0; i<5; i++){
    int targetFound = search(arr, size, target);
    printf("Found target %d at index %d\n", target, targetFound);
    rescramble(targetFound, arr, size);
  }
  
  return 0;
>>>>>>> f9a5b6268714cde49aa52a754000bd257f7bdf15
}
