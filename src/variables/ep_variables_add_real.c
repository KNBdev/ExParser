#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

void
epVariables__add_real (
  epVariables *vars,
  const char *name,
  double *r
) {

  epVariable var = {name, R, {.r = r}};
  epVariables__add(vars, var);
}