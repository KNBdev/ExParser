#include "exparser.h"

#include "ep_variables.h"
#include "ep_variables_def.h"

//-----------------------------------------------------------------------------

const char*
epVariables__get_name_by_index (
  const epVariables *vars,
  unsigned int index
) {

  if (!(0 <= index && index < vars->amount)) {
    return "";
  }

  return vars->vars[index].name;
}