#include "ep_functions.h"
#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

epFunctionListElement const*
epStack__pop_head_function (
  epStack *stack
) {

  const epFunctionListElement const *function = stack->head->content.function;
  epStack__pop(stack);

  return function;
}