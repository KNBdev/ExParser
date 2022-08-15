#include "ep_functions.h"
#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__push_function_by_ref (
  epStack *stack,
  epFunctionListElement const *function
) {

  epStack__push(stack);

  stack->head->type = FUNCTION;
  stack->head->content.function = function;
}