#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__push_value (
  epStack *stack,
  epValue *value
) {

  epStack__push(stack);

  stack->head->type = VALUE;
  stack->head->content.value = value;
}