/*
 *  Pocris Sabin - 312CB
 */

#include "ThreadPoolExecutor.h"

#include <stdio.h>

#include "Queue.h"
#include "Stack.h"
#include "SystemConfiguration.h"
#include "Task.h"

void initializeThreadPool(ThreadPool *threadPool, int numberOfThreads) {
  for (signed int i = numberOfThreads - 1; i >= 0; i--) {
    // initialize a new thread too
    Thread *temp = newThread((int)i);

    StackPush(threadPool, temp);
  }
}

Thread *newThread(int id) {
  Thread *temp = malloc(sizeof(Thread));
  temp->id = id;

  return temp;
}

Task *searchThreadInQue(Queue *queue, int threadNumber) {
  // we will keep the elements here
  Queue finalQ = NULL;
  Task *temp = NULL;   // storing the element from Dequeue();
  Task *found = NULL;  // the task we need

  if (!queue) return NULL;

  if (isQueueEmpty(*queue)) return NULL;

  while (!isQueueEmpty(*queue)) {
    temp = Dequeue(queue);

    if (!temp) continue;

    if (temp->runningThread == threadNumber) {
      found = temp;
    }

    Enqueue(&finalQ, temp);
  }

  // replace the initial queue with the new one
  *queue = finalQ;

  return found;
}

void getThread(Queue *runningQ, SysConfig *sys, IO *io) {
  int threadNumber = 0;
  Task *temp = NULL;

  fscanf(io->fileInput, "%d", &threadNumber);

  if ((temp = searchThreadInQue(runningQ, threadNumber))) {
    fprintf(io->fileOutput,
            "Thread %d is running task %d (remaining_time = %d).\n",
            temp->runningThread, temp->id, temp->leftTime);
    return;
  }

  if (threadNumber < sys->numberOfThreads) {
    fprintf(io->fileOutput, "Thread %d is idle.\n", threadNumber);
  }
}

void run(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ,
         Queue *finishedQ, IO *io, SysConfig *sysConfig, CPU *cpu,
         char *assignedIDs) {
  int time = 0;

  fscanf(io->fileInput, "%d", &time);
  cpu->toExecuteTime = time;
  cpu->ranTime = 0;  // reset it
  fprintf(io->fileOutput, "Running tasks for %d ms...\n", time);

  // prepare the runningQ
  loadRunningQ(threadPool, waitingQ, runningQ);

  // compute the running
  executeRunningQ(runningQ, waitingQ, finishedQ, cpu, sysConfig, threadPool,
                  assignedIDs);

  // check if there are tasks finished
  checkFinished(runningQ, finishedQ, threadPool, assignedIDs);
}

void loadRunningQ(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ) {
  Thread *tempThread = NULL;
  Task *tempTask = NULL;

  while (!isStackEmpty(*threadPool) && !isQueueEmpty(*waitingQ)) {
    tempThread = StackPop(threadPool);
    if (!tempThread) continue;

    tempTask = Dequeue(waitingQ);
    if (!tempTask) {
      StackPush(threadPool, tempThread);
      continue;
    }

    tempTask->runningThread = tempThread->id;
    addTaskRunningQ(runningQ, tempTask);

    free(tempThread);
  }
}

void runInParalel(Queue *runningQ, int time) {
  if (!runningQ) return;

  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item

  if (isQueueEmpty(*runningQ)) {
    return;
  }

  while (!isQueueEmpty(*runningQ)) {
    temp = Dequeue(runningQ);
    if (temp) {
      temp->leftTime = temp->leftTime - time;
      Enqueue(&tempQ, temp);
    }
  }

  *runningQ = tempQ;
}

void checkFinished(Queue *runningQ, Queue *finishedQ, ThreadPool *threadpool,
                   char *assignedIDs) {
  if (!runningQ) return;
  if (!finishedQ) return;
  if (!threadpool) return;

  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item

  if (isQueueEmpty(*runningQ)) {
    return;
  }

  while (!isQueueEmpty(*runningQ)) {
    temp = Dequeue(runningQ);
    if (temp) {
      if (temp->leftTime <= 0) {
        Thread *tempThread = newThread(temp->runningThread);
        assignedIDs[temp->id - 1] = 0;
        StackPush(threadpool, tempThread);

        Enqueue(finishedQ, temp);
        continue;
      }

      Enqueue(&tempQ, temp);
    }
  }

  *runningQ = tempQ;
}

void executeRunningQ(Queue *runningQ, Queue *waitingQ, Queue *finishedQ,
                     CPU *cpu, SysConfig *sysConfig, ThreadPool *threadPool,
                     char *assignedIDs) {
  if (!runningQ) return;
  if (!finishedQ) return;
  if (!cpu) return;
  if (!sysConfig) return;

  while ((cpu->toExecuteTime - cpu->ranTime) > 0 && !isQueueEmpty(*runningQ)) {
    int leftTime = cpu->toExecuteTime - cpu->ranTime;

    int maxTimeRunningQ = getMaxRunningTime(runningQ);
    if (maxTimeRunningQ > sysConfig->quantum) {
      maxTimeRunningQ = sysConfig->quantum;
    }

    int timeToRun = leftTime - maxTimeRunningQ > 0 ? maxTimeRunningQ : leftTime;

    runInParalel(runningQ, timeToRun);
    cpu->ranTime = cpu->ranTime + timeToRun;
    cpu->totalTime = cpu->totalTime + timeToRun;

    checkFinished(runningQ, finishedQ, threadPool, assignedIDs);
    loadRunningQ(threadPool, waitingQ, runningQ);
  }
}

int getMaxRunningTime(Queue *runningQ) {
  if (!runningQ) return 0;
  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item
  int maxTime = -1;

  if (isQueueEmpty(*runningQ)) {
    return 0;
  }

  while (!isQueueEmpty(*runningQ)) {
    temp = Dequeue(runningQ);
    if (temp) {
      if (temp->leftTime > maxTime) {
        maxTime = temp->leftTime;
      }

      Enqueue(&tempQ, temp);
    }
  }

  *runningQ = tempQ;
  return maxTime;
}

void finish(ThreadPool *threadPool, Queue *waitingQ, Queue *runningQ,
            Queue *finishedQ, IO *io, SysConfig *sysConfig, CPU *cpu,
            char *assignedIDs) {
  if (isQueueEmpty(*runningQ) && isQueueEmpty(*waitingQ)) {
    fprintf(io->fileOutput, "Total time: %d", cpu->totalTime);
    return;
  }

  do {
    cpu->ranTime = 0;  // reset it

    // prepare the runningQ
    loadRunningQ(threadPool, waitingQ, runningQ);

    cpu->toExecuteTime = getMaxRunningTime(runningQ);

    // compute the running
    executeRunningQ(runningQ, waitingQ, finishedQ, cpu, sysConfig, threadPool,
                    assignedIDs);

    // check if there are tasks finished
    checkFinished(runningQ, finishedQ, threadPool, assignedIDs);
  } while (!isQueueEmpty(*waitingQ));

  fprintf(io->fileOutput, "Total time: %d", cpu->totalTime);
}