#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

char
epStack__pop_head_brace (
  epStack *stack
) {

  char brace = stack->head->content.brace;
  epStack__pop(stack);

  return brace;
}