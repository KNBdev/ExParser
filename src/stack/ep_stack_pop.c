#include <stddef.h>
#include <stdlib.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__pop (
  epStack *stack
) {

  epStackElement *element = stack->head;
  stack->head = element->prev;

  element->content.function = NULL;

  free(element);
}