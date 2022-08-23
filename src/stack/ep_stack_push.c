#include <stdlib.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__push (
  epStack *stack
) {

  epStackElement *element = malloc(sizeof(epStackElement));

  element->prev = stack->head;
  stack->head = element;

  stack->head->value = epValue__create();
}