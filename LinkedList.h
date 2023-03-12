/*
 *  Pocris Sabin - 312CB
 */

#ifndef _LINLIST_
#define _LINLIST_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *data;
  struct node *nextNode;
} Node;

// returns 1 if list is not empty
// 0 otherwise
int isListEmpty(Node *node);

// it creates a new node with the given data
Node *newNode(void *data);

void addNodeAtBeginning(Node **node, Node *inputNode);
void addNodeAtEnd(Node **node, Node *inputNode);

// returns the data of that node
void *removeFirstNode(Node **node);
void *removeLastNode(Node **node);

void printList(Node *node);

int sizeOfList(Node *node);

#endif