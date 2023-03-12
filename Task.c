/*
 *  Pocris Sabin - 312CB
 */

#include "Task.h"

#include <stdio.h>

#include "Queue.h"

Task *newTask(int time, int priority, char *assignedIDs) {
  Task *temp = NULL;

  temp = malloc(sizeof(Task));
  if (!temp) return NULL;

  // setting the right data
  temp->time = time;
  temp->leftTime = time;
  // NOT INITIALISED YET
  temp->runningThread = THREAD_NOT_DEFINED;
  temp->priority = priority;

  // id time
  for (int i = 0; i < MAX_NUMBER_OF_IDS; i++) {
    if (assignedIDs[i] == 0) {
      assignedIDs[i] = 1;
      temp->id = (unsigned int)(i + 1);
      break;
    }
  }

  return temp;
}

void addTasks(Queue *waitingQ, char *assignedIDs, IO *io) {
  int numberOfTasks = 0;
  int taskTime = 0;
  int taskPriority = 0;
  Task *temp = NULL;

  // getting the data
  fscanf(io->fileInput, "%d", &numberOfTasks);
  fscanf(io->fileInput, "%d", &taskTime);
  fscanf(io->fileInput, "%d", &taskPriority);

  // creating the tasks and adding them
  while (numberOfTasks--) {
    temp = newTask(taskTime, taskPriority, assignedIDs);
    if (temp) {
      // Enqueue(waitingQ, temp);
      addTaskWaitingQ(waitingQ, temp);
      fprintf(io->fileOutput, "Task created successfully : ID %d.\n", temp->id);
    }
  }
}

void addTaskWaitingQ(Queue *waitingQ, Task *task) {
  // we will add the elements from the wQ less than our task
  // then we will add the task and after we just add the rest
  Queue finalQ = NULL;
  Task *temp = NULL;  // storing the element from Dequeue();

  if (!waitingQ) return;

  if (!task) return;

  if (isQueueEmpty(*waitingQ)) {
    Enqueue(waitingQ, task);
    return;
  }

  while (!isQueueEmpty(*waitingQ)) {
    temp = Dequeue(waitingQ);

    if (!temp) continue;

    if (task && !compareTasksWaitingQ(temp, task)) {
      Enqueue(&finalQ, task);
      task = NULL;
    }

    Enqueue(&finalQ, temp);
  }
  // check if the element still has not be inserted
  if (task) {
    Enqueue(&finalQ, task);
  }

  // replace the initial queue with the new one
  *waitingQ = finalQ;
}

int compareTasksWaitingQ(Task *task1, Task *task2) {
  if (!task1) return 0;
  if (!task2) return 0;

  if (task1->priority < task2->priority) return 0;

  if (task1->priority > task2->priority) return 1;

  // if they have the same priority
  if (task2->leftTime < task1->leftTime) return 0;

  if (task1->leftTime < task2->leftTime) return 1;

  // if they have the same leftTime
  if (task1->id > task2->id) return 0;

  return 1;
}

void printWaitingQ(Queue *waitingQ, IO *io) {
  if (!waitingQ) return;
  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item

  fprintf(io->fileOutput, "====== Waiting queue =======\n[");
  if (isQueueEmpty(*waitingQ)) {
    fprintf(io->fileOutput, "]\n");
    return;
  }

  while (!isQueueEmpty(*waitingQ)) {
    temp = Dequeue(waitingQ);
    if (temp) {
      fprintf(io->fileOutput,
              "(%d: priority = %d, "
              "remaining_time = %d),\n",
              temp->id, temp->priority, temp->leftTime);

      Enqueue(&tempQ, temp);
    }
  }

  fseek(io->fileOutput, -2, SEEK_CUR);
  fprintf(io->fileOutput, "]\n");
  // move the cursor back in other
  // to delete the '\n' and ','

  *waitingQ = tempQ;
}

Task *searchTaskInQue(Queue *queue, int id) {
  // we will keep the elements here
  Queue finalQ = NULL;
  Task *temp = NULL;   // storing the element from Dequeue();
  Task *found = NULL;  // the task we need

  if (!queue) return NULL;

  if (isQueueEmpty(*queue)) return NULL;

  while (!isQueueEmpty(*queue)) {
    temp = Dequeue(queue);

    if (!temp) continue;

    if (temp->id == id && !found) {
      found = temp;
    }

    Enqueue(&finalQ, temp);
  }

  // replace the initial queue with the new one
  *queue = finalQ;

  return found;
}

void getTask(Queue *runningQ, Queue *waitingQ, Queue *finishedQ, IO *io) {
  unsigned int id = 0;
  Task *temp = NULL;

  fscanf(io->fileInput, "%d", &id);

  if ((temp = searchTaskInQue(runningQ, id))) {
    fprintf(io->fileOutput, "Task %d is running (remaining_time = %d).\n", id,
            temp->leftTime);
    return;
  }

  if ((temp = searchTaskInQue(waitingQ, id))) {
    fprintf(io->fileOutput, "Task %d is waiting (remaining_time = %d).\n", id,
            temp->leftTime);
    return;
  }

  if ((temp = searchTaskInQue(finishedQ, id))) {
    fprintf(io->fileOutput, "Task %d is finished (executed_time = %d).\n", id,
            temp->time);
    return;
  }

  fprintf(io->fileOutput, "Task %d not found.\n", id);
}

void printRunningQ(Queue *runningQ, IO *io) {
  if (!runningQ) return;
  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item

  fprintf(io->fileOutput, "====== Running in parallel =======\n[");
  if (isQueueEmpty(*runningQ)) {
    fprintf(io->fileOutput, "]\n");
    return;
  }

  while (!isQueueEmpty(*runningQ)) {
    temp = Dequeue(runningQ);
    if (temp) {
      fprintf(io->fileOutput,
              "(%d: priority = %d, "
              "remaining_time = %d, "
              "running_thread = %d),\n",
              temp->id, temp->priority, temp->leftTime, temp->runningThread);

      Enqueue(&tempQ, temp);
    }
  }

  fseek(io->fileOutput, -2, SEEK_CUR);
  fprintf(io->fileOutput, "]\n");
  // move the cursor back in other
  // to delete the '\n' and ','

  *runningQ = tempQ;
}

void printFinishedQ(Queue *finishedQ, IO *io) {
  if (!finishedQ) return;
  Queue tempQ = NULL;  // here we will put back the items
  Task *temp = NULL;   // storing the item

  fprintf(io->fileOutput, "====== Finished queue =======\n[");
  if (isQueueEmpty(*finishedQ)) {
    fprintf(io->fileOutput, "]\n");
    return;
  }

  while (!isQueueEmpty(*finishedQ)) {
    temp = Dequeue(finishedQ);
    if (temp) {
      fprintf(io->fileOutput,
              "(%d: priority = %d, "
              "executed_time = %d),\n",
              temp->id, temp->priority, temp->time);

      Enqueue(&tempQ, temp);
    }
  }

  fseek(io->fileOutput, -2, SEEK_CUR);
  fprintf(io->fileOutput, "]\n");
  // move the cursor back in other
  // to delete the '\n' and ','

  *finishedQ = tempQ;
}

void addTaskRunningQ(Queue *runningQ, Task *tempTask) {
  addTaskWaitingQ(runningQ, tempTask);
}