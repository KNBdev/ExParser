#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__push_real (
  epStack *stack,
  double r
) {

  epStack__push(stack);
  epStack__init_value(stack);

  stack->head->type = VALUE;
  epValue__set_real(stack->head->content.value, r);
}