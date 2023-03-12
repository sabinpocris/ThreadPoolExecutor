/*
 *  Pocris Sabin - 312CB
 */

#include "Stack.h"

#include "LinkedList.h"

// it adds a new item on the stack
void StackPush(Stack *stack, void *data) {
  if (!stack) {
    return;
  }

  if (!data) {
    return;
  }

  Node *temp = newNode(data);

  addNodeAtBeginning(stack, temp);
}

// it pops an item from the stacks and returns it
void *StackPop(Stack *stack) {
  if (!stack) {
    return NULL;
  }

  return removeFirstNode(stack);
}

// it creates a new empty stack
Stack newStack() {
  Stack temp = malloc(sizeof(Node));

  if (!temp) return NULL;

  return temp;
}

// prints the stack
void printStack(Stack stack) {
  Node *temp = stack;

  printf("==== STACK ====\n");

  for (int i = sizeOfList(stack); i > 0; i--) {
    printf("\t%d: '%d'\n", i, *((int *)(stack->data)));
    stack = stack->nextNode;
  }

  printf("====  End  ====\n");
}

int isStackEmpty(Stack stack) { return isListEmpty(stack); }

void deleteStack(Stack *stack) {
  while (!isStackEmpty(*stack)) {
    void *temp = StackPop(stack);
    free(temp);
  }
}