// Implement a stack that runs in O(1) time for the operations Push(),
// Pop() and FindMin(). You are allowed to use an additional stack as you
// see fit.

// Solution: Use the additional stack to store a chain of minimum items.
// Insert the first item as-is. Every time there's a new Push() operation,
// check if the new item to be inserted is less than the item on the MinStack.
// If yes, then insert. Similarly, if we're popping out the minimum item, then
// pop it out from the MinStack as well, so that MinStack now points to the next
// minimum item, thereby giving us the ability to look up the minimum item at any
// given point in constant time.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack {
  int data;
  struct stack *next;
} Stack;

Stack *MinStack;

void Push (Stack **stack, int data) {
  Stack *newnode;
  
  assert (stack);
  
  newnode = (Stack*) malloc (sizeof(Stack));
  newnode->data = data;
  newnode->next = *stack;
  *stack = newnode;
  
  if (MinStack == NULL || data < MinStack->data) {
    Stack *minnode;
    
    minnode = (Stack*) malloc (sizeof(Stack));
    minnode->data = data;
    minnode->next = MinStack;
    MinStack = minnode;
  }
  
  printf("Pushed %d\n", data);
}

int Pop (Stack **stack) {
  Stack *delnode;
  int data;
  
  assert (stack);
  
  delnode = *stack;
  data = delnode->data;
  *stack = (*stack)->next;
  
  if (MinStack && delnode->data == MinStack->data) {
    Stack *minstackdelnode;
    
    minstackdelnode = MinStack;
    MinStack = MinStack->next;
    
    free (minstackdelnode);
  }
  
  free (delnode);
  
  return data;
}

int FindMin () {
  if (MinStack) {
    return MinStack->data;
  }
  
  return 0xdeadbeef;
}

int main () {
  Stack *stack = NULL;
  
  Push (&stack, 6);
  Push (&stack, 15);
  Push (&stack, 18);
  printf("Minimum is %d\n", FindMin()); // 6
  Push (&stack, 5);
  Push (&stack, 7); // 7 - 5 - 18 - 15 - 6
  printf("Minimum is %d\n", FindMin()); // 5
  printf("Popped %d\n", Pop(&stack)); // Popped 7. 5 - 18 - 15 - 6
  printf("Popped %d\n", Pop(&stack)); // Popped 5. 18 - 15 - 6
  printf("Minimum is %d\n", FindMin()); // 6
  Push (&stack, 9);
  Push (&stack, 4);
  Push (&stack, 12); // 12 - 4 - 9 - 18 - 15 - 6
  printf("Minimum is %d\n", FindMin()); // 4
  printf("Popped %d\n", Pop(&stack)); // Popped 12. 4 - 9 - 18 - 15 - 6
  printf("Minimum is %d\n", FindMin()); // 4.
  printf("Popped %d\n", Pop(&stack)); // Popped 4. 9 - 18 - 15 - 6
  printf("Minimum is %d\n", FindMin()); // 6
  
  return 0;
}