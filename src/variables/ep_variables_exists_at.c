#include <string.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

int
epVariables__exists_at (
  epVariables *vars,
  const char *name
) {

  for (int i = 0; i < vars->amount; i++) {
    if (strcmp(vars->vars[i].name, name) == 0) {
      return i;
    }
  }

  return -1;
}