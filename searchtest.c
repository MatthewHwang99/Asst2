// implements both multiprocess and multithread searches based on how it is built
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"multitest.h"

void rescramble(int, int*, int);

void rescramble(int prevIndex, int* arr, int size){
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
	if(argc!=3){
		printf("Error: Please an input array size followed by the number of threads/processes.\n");
		return 0;
	}
	
  int size = atoi(argv[1]); //supposed to test different ranges of sizes along with different step sizes
  int num = atoi(argv[2]); //number of threads/processes
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
  
  struct timeval start, end;
  unsigned long time = 0;

  int numRuns = 100;
  unsigned long min = 0, max = 0;
  unsigned long sum = 0;
  
  FILE *fp = fopen("resulttest.txt", "w");
  
  unsigned long timearr[numRuns];

  for(int i = 1; i<=numRuns; i++){
    gettimeofday(&start, 0);
    int targetFound = (int)search(arr, size, target, num);
    //printf("Target %d found at index %d\n", target, targetFound);
    //fprintf(fp, "Target %d found at index %d\n", target, targetFound);  
    gettimeofday(&end, 0);
    time = (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
    timearr[(i-1)] = time;
    
    /*Calculate min and max*/
    if(min == 0 && max == 0){
      min = time;
      max = time;
    }
    if(time < min){
      min = time;
    }else if(time > max){
      max = time;
    }
    /*********************/
    sum += time;
    //fprintf(fp,"Size of array: %d Time it took: %lu\n", size, time);
    rescramble(targetFound, arr, size);
  } 
  
  unsigned long avgTime = sum/numRuns;
  
  /**Calculate Std. Dev**/
  unsigned long runningsum = 0;
  for(int i = 0; i < numRuns; i++){
    runningsum += ((timearr[i] - avgTime) * (timearr[i] - avgTime));
  }
  runningsum /= (numRuns-1);
  runningsum = sqrt((double)runningsum);
  /**********************/
  fprintf(fp, "Average Time %lu\n", avgTime);
  fprintf(fp, "Min: %lu\nMax: %lu\n", min, max);
  fprintf(fp, "Std. Dev: %lu\n", runningsum); 
  printf("Total run time: %lu microseconds.\nAverage time per search: %lu microseconds.\n", sum, avgTime);
  printf("Minimum time: %lu\nMaximum time: %lu\n", min, max);
  printf("Standard Deviation: %lu\n", runningsum);
  //  free(arr);
  //  free(timearr);
  fclose(fp);
  return 0;
}
