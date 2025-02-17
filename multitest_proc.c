//library with a multiprocess implementation of your search function
#include "multitest.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int info = 0;

int linearSearch(int* arr, int size, int target){
  int j;
  for(j = 0; j < size; j++){
    if(target == arr[j]){
      return j;
    }
  }
  return -1;
}

int search(int *arr, int size, int target, int numProc){
  //size refers to the size of the initial array
  /*int i, result, numofProc = 1, leftover;
  while(size/numofProc > 250){
    numofProc++;
  }
  leftover = size - (numofProc * (size/numofProc));*/
  
  int i, result;
  
  int partitionSize = size/numProc;
  if(partitionSize>250){
  	printf("Error: Partition size is greater than 250. Need more processes.\n");
  	exit(0);
  }
  
  int leftover = 0;
  if(size%numProc!=0){
  	leftover = size%numProc;
  }
  
  if(info == 0){
  	printf("Breaking the array into partitions of %d, using %d processes.\n", partitionSize, numProc);
	info = 1;
	}
	
  for(i = 0; i < numProc; i++){
    if(fork() == 0){
      //child process; search a portion of the array
      if((numProc - i) == 1 && leftover > 0){
		exit(linearSearch(&arr[(size/numProc) * i], leftover, target));
      }
      //actual search function, returns the index; -1 if not found
     	exit(linearSearch(&arr[(size/numProc) * i], (size/numProc), target));
      //It will never return a value past 255 because of the 250 element array cap
    }/*else{
      //Don't have parent wait for each child, have the above loop run n times and then have another loop after having the parent wait n times for exits
      wait(&result);
    }
     */
    int j;
    int temp;
    for(j = 0; j < numProc; j++){
      wait(&result);
      
      if(WEXITSTATUS(result) != 255){
	//Found the target
	//printf("Found the target %d at index %d of iteration %d\n", target, WEXITSTATUS(result), i);
	//return ((i * (size/numProc)) + WEXITSTATUS(result));
	temp = ((i * (size/numProc)) + WEXITSTATUS(result));
      }
    }
    return temp;
    /*
    if(WEXITSTATUS(result) != 255){
      //Found the target
      //printf("Found the target %d at index %d of iteration %d\n", target, WEXITSTATUS(result), i);
      return ((i * (size/numofProc)) + WEXITSTATUS(result));
    }
    */
  }
  //target not found
  return -1;
}

  /* 
  int partitionSize = 0;
  int maxparts = 250;
  int tempSize = size;
  while((tempSize/2) > 250){
    partitionSize++;
    tempSize/= 2;
  }
  if(tempSize = 1){
    partitionSize++;
  }
  if(size < partitionSize){
    numofProc = 1;
  }else if((size % partitionSize) == 0){
    numofProc = size / partitionSize;
  }else{
    numofProc = size/partitionSize;
    numofProc++;
  }
*/
