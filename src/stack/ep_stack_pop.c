#include <stddef.h>
#include <stdlib.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__pop (
  epStack *stack
) {

  if (epStack__is_head_value(stack)) {
    epValue__delete(stack->head->content.value);
  }

  epStackElement *element = stack->head;
  stack->head = element->prev;

  free(element);
}