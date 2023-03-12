/*
 *  Pocris Sabin - 312CB
 */

#ifndef _QUEUE_
#define _QUEUE_

#include "LinkedList.h"

typedef Node *Queue;

void Enqueue(Queue *queue, void *data);

// it deques and returns the data
void *Dequeue(Queue *queue);

void printQueue(Queue queue);

// returns 1 if is empty 0 otherwise
int isQueueEmpty(Queue queue);

void deleteQue(Queue *queue);

#endif