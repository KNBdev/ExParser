#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

epValue*
epStack__pop_head_value (
  epStack *stack
) {

  epValue *value = epValue__create();
  epValue__copy(value, stack->head->content.value);

  epStack__pop(stack);

  return value;
}