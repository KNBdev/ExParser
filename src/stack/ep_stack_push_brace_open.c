#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__push_brace_open (
  epStack *stack,
  char brace
) {

  epStack__push(stack);

  stack->head->type = BRACEOPEN;
  stack->head->content.brace = brace;
}