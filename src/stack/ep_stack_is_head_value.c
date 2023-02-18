#include <stdbool.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

bool
epStack__is_head_value (
  const epStack *stack
) {

  return (stack->head->type == VALUE);
}