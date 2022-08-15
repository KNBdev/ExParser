#include <stdlib.h>

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

void
epVariables__add (
  epVariables *vars,
  epVariable var
) {

  int nameExists = epVariables__exists_at(vars, var.name);

  if (nameExists == -1) {

    vars->amount++;
    vars->vars = realloc(vars->vars, sizeof(epVariable) * vars->amount);
    vars->vars[vars->amount - 1] = var;

  } else {

    vars->vars[nameExists] = var;
  }
}