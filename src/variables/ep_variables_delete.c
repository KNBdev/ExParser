#include <stdlib.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

void
epVariables__delete (
  epVariables *vars
) {

  free(epVariables__get_real(vars, "pi"));
  free(epVariables__get_real(vars, "e"));

  free(vars->vars);
  free(vars);
}