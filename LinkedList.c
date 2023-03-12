/*
 *  Pocris Sabin - 312CB
 */

#include "LinkedList.h"

// returns 1 if list is not empty
// 0 otherwise
int isListEmpty(Node *node) {
  if (!node) return 1;

  return 0;
}

// it creates a new node with the given data
Node *newNode(void *data) {
  Node *tempNode = malloc(sizeof(Node));

  if (!tempNode) return NULL;

  tempNode->nextNode = NULL;
  tempNode->data = data;

  return tempNode;
}

void addNodeAtBeginning(Node **node, Node *inputNode) {
  if (!inputNode) return;

  if (!node) return;

  // list is empty?
  if (isListEmpty(*node)) {
    *node = inputNode;
    return;
  }

  // add at beginning
  inputNode->nextNode = *node;
  *node = inputNode;

  return;
}

void addNodeAtEnd(Node **node, Node *inputNode) {
  if (!node) return;

  if (!inputNode) return;

  if (isListEmpty(*node)) {
    *node = inputNode;
    return;
  }

  // iterate over list
  // go at the last node
  Node *tempNode = *node;
  Node *lastNode = NULL;

  while (tempNode) {
    lastNode = tempNode;
    tempNode = tempNode->nextNode;
  }

  lastNode->nextNode = inputNode;

  return;
}

// deletes the first and returns it's data
void *removeFirstNode(Node **node) {
  if (!node) {
    return NULL;
  }

  if (!(*node)) {
    return NULL;
  }

  if (isListEmpty((*node))) {
    return NULL;
  }

  void *data = (*node)->data;
  Node *tempNode = (*node);

  // is there more than 1 node in the list?
  if ((*node)->nextNode) {
    *node = (*node)->nextNode;
  } else {
    *node = NULL;
  }

  free(tempNode);

  return data;
}

// deletes the last node and returns it's data
void *removeLastNode(Node **node) {
  if (!node) {
    return NULL;
  }

  if (!(*node)) {
    return NULL;
  }

  if (isListEmpty((*node))) {
    return NULL;
  }

  void *data = NULL;
  Node *tempNode = (*node);
  Node *lastNode = NULL;

  // going to the last node
  while (tempNode->nextNode) {
    lastNode = tempNode;
    tempNode = tempNode->nextNode;
  }

  data = tempNode->data;

  if (lastNode) {
    lastNode->nextNode = NULL;
  } else {
    *node = NULL;  // the list has only 1 node
  }

  free(tempNode);

  return data;
}

void printList(Node *node) {
  if (isListEmpty(node)) {
    printf("====   LIST   ====\n");
    printf("\t(empty)\n");
    printf("==== END_LIST ====\n");

    return;
  }

  Node *tempNode = node;

  printf("==== LIST ====\n");
  for (int i = 0; tempNode; i++) {
    printf("\t%d: |%d|\n", i, *((int *)(tempNode->data)));

    tempNode = tempNode->nextNode;
  }
  printf("==== END_LIST ====\n");
}

// returns the number of nodes
int sizeOfList(Node *node) {
  int size = 0;

  if (!node) return size;

  while (node) {
    size++;
    node = node->nextNode;
  }

  return size;
}