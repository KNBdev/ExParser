#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

#ifndef M_PI
#define M_PI (acos(-1.0))
#endif

#ifndef M_E
#define M_E (exp(1))
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
  double *e = (double *) malloc(sizeof(double));

  *pi = M_PI;
  *e = M_E;

  epVariables__add_real(vars, "pi", pi);
  epVariables__add_real(vars, "e", e);

  return vars;
}