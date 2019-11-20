// implements both multiprocess and multithread searches based on how it is built
#include<stdio.h>
#include<stdlib.h>
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
  
  struct timeval start, end;
  unsigned long time = 0;
  //unsigned long time2 = 0;
  int numRuns = 100;
  FILE *fp = fopen("resulttest.txt", "w");

  for(int i = 1; i<=numRuns; i++){
    gettimeofday(&start, 0);
    int targetFound = (int)search(arr, size, target);
    printf("Target %d found at index %d\n", target, targetFound);
    gettimeofday(&end, 0);
    time += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
    fprintf(fp,"Size of array: %d Time: %lu\n" , i*size, time);
    rescramble(targetFound, arr, size);
  } 
  
  unsigned long avgTime = time/numRuns;	
  fprintf(fp, "Average Time %lu\n", avgTime);
  fclose(fp); 
  printf("Total run time: %lu microseconds.\nAverage time per search: %lu microseconds.\n", time, avgTime);

  return 0;
}
