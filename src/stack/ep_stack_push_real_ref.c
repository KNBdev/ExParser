#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__push_real_ref (
  epStack *stack,
  double *rRef
) {

  epStack__push(stack);
  epStack__init_head_value(stack);

  epValue__set_real_ref(stack->head->content.value, rRef);
}