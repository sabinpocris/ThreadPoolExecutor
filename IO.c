/*
 *  Pocris Sabin - 312CB
 */

#include "IO.h"

#include <stdio.h>
#include <string.h>

int getCommand(IO *io) {
  // here we will read the input
  char lineInput[128];

  if (fscanf(io->fileInput, "%s", lineInput) == EOF) {
    return END;
  }

  if (strcmp(lineInput, "add_tasks") == 0) {
    return ADD_TASKS;
  }

  if (strcmp(lineInput, "get_task") == 0) {
    return GET_TASK;
  }

  if (strcmp(lineInput, "get_thread") == 0) {
    return GET_THREAD;
  }

  if (strcmp(lineInput, "print") == 0) {
    fscanf(io->fileInput, "%s", lineInput);

    if (strcmp(lineInput, "waiting") == 0) return PRINT_WAITING;

    if (strcmp(lineInput, "running") == 0) return PRINT_RUNNING;

    if (strcmp(lineInput, "finished") == 0) return PRINT_FINISHED;
  }

  if (strcmp(lineInput, "run") == 0) {
    return RUN;
  }

  if (strcmp(lineInput, "finish") == 0) {
    return FINISH;
  }

  return -1;
}

int initializeIO(IO *io, char *inputFile, char *outputFile) {
  io->fileInput = fopen(inputFile, "r");
  if (!(io->fileInput)) return 0;

  io->fileOutput = fopen(outputFile, "w+");
  if (!(io->fileOutput)) {
    fclose(io->fileInput);
    return 0;
  }

  return 1;
}

void closeIO(IO *io) {
  fclose(io->fileInput);
  fclose(io->fileOutput);
}