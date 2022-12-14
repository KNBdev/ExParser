#include <complex.h>

#include "ep_stack.h"
#include "ep_stack_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epStack__push_complex_ref (
  epStack *stack,
  double complex *cRef
) {

  epStack__push(stack);
  epStack__init_head_value(stack);

  epValue__set_complex_ref(stack->head->content.value, cRef);
}