#include <stdbool.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

bool
epVariables__exists (
  epVariables *vars,
  const char *name
) {

  return (epVariables__exists_at(vars, name) != -1);
}