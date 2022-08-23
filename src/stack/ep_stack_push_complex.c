#include <complex.h>

#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__push_complex (
  epStack *stack,
  double complex c
) {

  epStack__push(stack);
  epValue__set_complex(stack->head->value, c);

  stack->head->type = VALUE;
}