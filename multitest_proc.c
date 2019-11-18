//library with a multiprocess implementation of your search function
#include "multitest.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int linearSearch(int* arr, int size, int target){
  int j;
  for(j = 0; j < size; j++){
    if(target == arr[j]){
      return j;
    }
  }
  return -1;
}

int search(int *arr, int size, int target){
  //size refers to the size of the initial array
  int i, result, numofProc;
  int partitionSize = 5;
  if(size < partitionSize){
    numofProc = 1;
  }else if((size % partitionSize) == 0){
    numofProc = size / partitionSize;
  }else{
    numofProc = size/partitionSize;
    numofProc++;
  }
  for(i = 0; i < numofProc; i++){
    if(fork() == 0){
      //child process; search a portion of the array
      exit(linearSearch(&arr[(size/numofProc) * i], (size/numofProc), target));//actual search function, returns the index; -1 if not found
      //It will never return a value past 255 because of the 250 element array cap
    }else{
      wait(&result);
    }

    if(WEXITSTATUS(result) != 255){
      //Found the target
      //printf("Found the target %d at index %d of iteration %d\n", target, WEXITSTATUS(result), i);
      return ((i * (size/numofProc)) + WEXITSTATUS(result));
    }
  }
  //target not found
  return -1;
}
