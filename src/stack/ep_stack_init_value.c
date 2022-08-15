#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__init_value (
  epStack* stack
) {

  epValue **value = &stack->head->content.value;

  if (!(*value)) {
    *value = epValue__create();
  }

  stack->head->type = VALUE;
}