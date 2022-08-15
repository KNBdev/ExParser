#include <stddef.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__reverse (
  epStack *stack
) {

  epStackElement *prev = NULL;
  epStackElement *current = stack->head;
  epStackElement *next = NULL;

  while (current) {

    next = current->prev;
    current->prev = prev;
    prev = current;
    current = next;
  }

  stack->head = prev;
}