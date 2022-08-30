#include <stddef.h>
#include <stdlib.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

epStack*
epStack__create (
  void
) {

  epStack* stack = (epStack *) malloc(sizeof(epStack));
  stack->head = NULL;

  return stack;
}