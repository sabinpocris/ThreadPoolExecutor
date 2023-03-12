/*
 *  Pocris Sabin - 312CB
 */

#ifndef _TASK_
#define _TASK_

#include <stdio.h>

#include "Queue.h"
#include "ThreadPoolExecutor.h"

#define THREAD_NOT_DEFINED -1
#define MAX_NUMBER_OF_IDS 32767

typedef struct task {
  unsigned int id;
  int priority;
  int time;      // time it takes to be finished
  int leftTime;  // time left to be run
  int runningThread;
} Task;

// it reads the number of tasks, time, and their priority
// and adds them to the waiting queue
void addTasks(Queue *waitingQ, char *assignedIDs, IO *io);

// it creates a new task; it also assigns the id
Task *newTask(int time, int priority, char *assignedIDs);

// it adds the task in the waiting que, in the specified order
void addTaskWaitingQ(Queue *waitingQ, Task *task);
void addTaskRunningQ(Queue *runningQ, Task *tempTask);

// compare the tasks for insertion in waitingQ
// returns 1 if the task1 is before task2
// 0 otherwise
int compareTasksWaitingQ(Task *task1, Task *task2);

void printWaitingQ(Queue *waitingQ, IO *io);
void printRunningQ(Queue *runningQ, IO *io);
void printFinishedQ(Queue *finishedQ, IO *io);

void getTask(Queue *runningQ, Queue *waitingQ, Queue *finishedQ, IO *io);

// searchs for the task and returns it if it is there
Task *searchTaskInQue(Queue *queue, int id);

#endif