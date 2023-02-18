#include <stdbool.h>
#include <stddef.h>

#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

bool
epStack__is_empty (
  const epStack *stack
) {

  return (stack->head == NULL);
}