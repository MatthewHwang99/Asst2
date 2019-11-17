//library with a multiprocess implementation of your search function
#include "multitest.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int search(int *arr, int size, int numofProc, int index){
  //size refers to the size of the broken down initial array
  int i, result;
  for(i = 0; i < numofProc; i++){
    if(fork() == 0){
      //child process; search a portion of the array
      exit(search());//actual search function, returns the index; -1 if not found
      //It will never return a value past 255 because of the 250 element array cap
    }else{
      wait(&result);
    }

    if(WEXITSTATUS(result) != 255){
      //Found the target
      return WEXITSTATUS(result);
    }
  }
  //target not found
  return -1;
}
