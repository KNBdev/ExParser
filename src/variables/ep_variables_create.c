#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

#ifndef M_PI
#define M_PI (acos(-1.0))
#endif

//-----------------------------------------------------------------------------

epVariables*
epVariables__create (
  void
) {

  epVariables *vars = (epVariables *) malloc(sizeof(epVariables));

  vars->vars = NULL;
  vars->amount = 0;

  double *pi = (double *) malloc(sizeof(double));
  *pi = M_PI;

  epVariables__add_real(vars, "pi", pi);

  return vars;
}