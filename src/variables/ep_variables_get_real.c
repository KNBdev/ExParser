#include <stddef.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

double*
epVariables__get_real (
  const epVariables *vars,
  const char *name
) {

  int nameExistsAt = epVariables__exists_at(vars, name);

  if (nameExistsAt == -1) {
    return NULL;
  }

  return vars->vars[nameExistsAt].p.r;
}