/*
 *  Pocris Sabin - 312CB
 */

#ifndef _IO_
#define _IO_

#include <stdio.h>
#include <string.h>

#define ADD_TASKS 1
#define GET_TASK 2
#define GET_THREAD 3
#define PRINT 4
#define PRINT_WAITING 5
#define PRINT_RUNNING 6
#define PRINT_FINISHED 7
#define RUN 8
#define FINISH 9
#define END 10

struct io {
  FILE *fileInput;
  FILE *fileOutput;
};

typedef struct io IO;

// reads from file and returns what command is it
int getCommand(IO *io);

// initalize the input
// return 1 if it is succesfull
// 0 otherwise
int initializeIO(IO *io, char *inputFile, char *outputFile);

// does what it says
void closeIO(IO *io);

#endif