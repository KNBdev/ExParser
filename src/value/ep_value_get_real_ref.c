#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

double*
epValue__get_real_ref (
  const epValue *value
) {

  return value->value.rRef;
}