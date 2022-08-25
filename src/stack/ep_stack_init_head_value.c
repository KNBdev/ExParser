#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__init_head_value (
  epStack *stack
) {

  stack->head->content.value = epValue__create();
  stack->head->type = VALUE;
}