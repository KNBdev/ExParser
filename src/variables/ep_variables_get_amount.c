#include "exparser.h"

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

unsigned int
epVariables__get_amount (
  const epVariables *vars
) {

  return vars->amount;
}