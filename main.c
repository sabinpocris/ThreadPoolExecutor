/*
 *  Pocris Sabin - 312CB
 */

#include <stdio.h>

#include "IO.h"
#include "Queue.h"
#include "Stack.h"
#include "SystemConfiguration.h"
#include "Task.h"
#include "ThreadPoolExecutor.h"

int main(int argc, char** argv) {
  ThreadPool threadPool = NULL;
  SysConfig sysConfig;
  Queue waitingQ = NULL, runningQ = NULL, finishedQ = NULL;
  IO io;  // we will use this to read/write the data
  CPU cpu;
  cpu.totalTime = 0;

  // we will keep the ids here
  char assignedIDs[MAX_NUMBER_OF_IDS] = {0};

  // IO stuff
  if (argc < 3) return 1;

  if (!initializeIO(&io, argv[1], argv[2])) {
    return 1;
  }

  readSystemConfiguration(&sysConfig, &io);

  initializeThreadPool(&threadPool, sysConfig.numberOfThreads);

  for (;;) {
    switch (getCommand(&io)) {
      case ADD_TASKS:
        addTasks(&waitingQ, assignedIDs, &io);
        break;
      case GET_TASK:
        getTask(&runningQ, &waitingQ, &finishedQ, &io);
        break;
      case GET_THREAD:
        getThread(&runningQ, &sysConfig, &io);
        break;
      case PRINT_WAITING:
        printWaitingQ(&waitingQ, &io);
        break;
      case PRINT_RUNNING:
        printRunningQ(&runningQ, &io);
        break;
      case PRINT_FINISHED:
        printFinishedQ(&finishedQ, &io);
        break;
      case RUN:
        run(&threadPool, &waitingQ, &runningQ, &finishedQ, &io, &sysConfig,
            &cpu, assignedIDs);
        break;
      case FINISH:
        finish(&threadPool, &waitingQ, &runningQ, &finishedQ, &io, &sysConfig,
               &cpu, assignedIDs);
      case END:
        closeIO(&io);

        deleteQue(&waitingQ);
        deleteQue(&runningQ);
        deleteQue(&finishedQ);

        deleteStack(&threadPool);
        return 0;
        break;
      default:
        printf("not a command!\n");
        break;
    }
  }

  return 0;
}