#include <complex.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

void
epVariables__add_complex (
  epVariables *vars,
  const char *name,
  double complex *c
) {

  epVariable var = {name, C, {.c = c}};
  epVariables__add(vars, var);
}