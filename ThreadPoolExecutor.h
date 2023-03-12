/*
 *  Pocris Sabin - 312CB
 */

#ifndef _THRD_P_EXEC_
#define _THRD_P_EXEC_

#include "Queue.h"
#include "Stack.h"
#include "SystemConfiguration.h"

typedef Stack ThreadPool;

typedef struct thread {
  int id;
} Thread;

typedef struct cpu {
  int ranTime;        // the time it actually ran
  int toExecuteTime;  // how long it has to run
  int totalTime;      // time it ran
} CPU;

void initializeThreadPool(ThreadPool *threadPool, int numberOfThreads);

Thread *newThread(int);

void getThread(Queue *runningQ, SysConfig *sys, IO *io);

void run(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ,
         Queue *finishedQ, IO *io, SysConfig *sysConfig, CPU *cpu,
         char *assignedIDs);

void finish(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ,
            Queue *finishedQ, IO *io, SysConfig *sysConfig, CPU *cpu,
            char *assignedIDs);

void loadRunningQ(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ);

void executeRunningQ(Queue *runningQ, Queue *waitingQ, Queue *finishedQ,
                     CPU *cpu, SysConfig *sysConfig, ThreadPool *threadPool,
                     char *assignedIDs);

void runInParalel(Queue *runningQ, int time);

void checkFinished(Queue *runningQ, Queue *finishedQ, ThreadPool *threadpool,
                   char *assignedIDs);

// returns the biggest running time from the queue
int getMaxRunningTime(Queue *runningQ);

#endif