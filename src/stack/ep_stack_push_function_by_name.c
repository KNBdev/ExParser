#include <stddef.h>
#include <string.h>

#include "ep_functions.h"
#include "ep_stack.h"
#include "ep_stack_def.h"

//-----------------------------------------------------------------------------

void
epStack__push_function_by_name (
  epStack *stack,
  const char *name
) {

  epStack__push(stack);

  epFunctionListElement const *function = NULL;

  unsigned int size = sizeof(epFunctionList) / sizeof(epFunctionListElement);
  for (int i = 0; i < size; i++) {
    if (strcmp(epFunctionList[i].name, name) == 0) {
      function = &epFunctionList[i];
    }
  }

  if (!function) {
    epStack__pop(stack);
    return;
  }

  stack->head->type = FUNCTION;
  stack->head->content.function = function;
}