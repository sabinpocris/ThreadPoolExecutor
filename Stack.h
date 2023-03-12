/*
 *  Pocris Sabin - 312CB
 */

#ifndef _STACK_
#define _STACK_

#include "LinkedList.h"

typedef Node* Stack;

// it adds a new item on the stack
void StackPush(Stack* stack, void* data);

// it pops an item from the stacks and returns it
void* StackPop(Stack* stack);

// it creates a new empty stack
Stack newStack();

// prints the stack
void printStack(Stack stack);

// returns 1 if is empty 0 otherwise
int isStackEmpty(Stack stack);

void deleteStack(Stack* stack);

#endif