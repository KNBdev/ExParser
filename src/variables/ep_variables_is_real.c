#include <stdbool.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

bool
epVariables__is_real (
  epVariables *vars,
  const char *name
) {

  int nameExistsAt = epVariables__exists_at(vars, name);

  if (nameExistsAt == -1) {
    return false;
  }

  return (vars->vars[nameExistsAt].type == R);
}