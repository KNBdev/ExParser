#include <stdlib.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__delete (
  epStack *stack
) {

  while (stack->head) {
    epStack__pop(stack);
  }

  free(stack);
}