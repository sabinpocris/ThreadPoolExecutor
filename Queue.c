/*
 *  Pocris Sabin - 312CB
 */

#include "Queue.h"

#include "LinkedList.h"

// adds the data to the queue
void Enqueue(Queue *queue, void *data) {
  if (!queue) {
    return;
  }

  if (!data) {
    return;
  }

  Node *temp = newNode(data);
  if (!temp) {
    return;
  }

  addNodeAtEnd(queue, temp);
}

// it dequeues and returns the data
void *Dequeue(Queue *queue) {
  if (!queue) {
    return NULL;
  }

  return removeFirstNode(queue);
}

void printQueue(Queue queue) {
  if (!queue) {
    printf("Empty queue!\n");
    return;
  }

  printf("==== Queue ====\n");
  printf("[");
  for (int i = sizeOfList(queue); i > 0; i--) {
    printf("%d, ", *((int *)(queue->data)));
    queue = queue->nextNode;
  }
  printf("]\n");
  printf("====  End  ====\n");
}

int isQueueEmpty(Queue queue) { return isListEmpty(queue); }

void deleteQue(Queue *queue) {
  while (!isQueueEmpty(*queue)) {
    void *temp = Dequeue(queue);
    free(temp);
  }
}